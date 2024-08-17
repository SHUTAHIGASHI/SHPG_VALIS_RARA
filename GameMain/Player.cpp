#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "Stage.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"
#include "CameraManager.h"
#include "SoundManager.h"
#include "UiManager.h"

namespace
{
	// 画像拡大率
	constexpr float kScale = 100.0f;

	// 移動速度
	constexpr float kPlayerMoveSpeed = 8.0f;
	// 移動加速度
	constexpr float kPlayerMoveAccel = 1.6f;
	// ダッシュ速度
	constexpr float kPlayerDashSpeed = kPlayerMoveSpeed * 2.0f;
	// スライディング速度率
	constexpr float kSlideRate = 1.5f;
	// 重力
	constexpr float kGravity = 0.5f;
	// 慣性
	constexpr float kInertia = 0.9f;
	// ジャンプ力
	constexpr float kJumpPower = 12.0f;

	// 姿勢ごとの速度
	constexpr float kCrouchSpeed = 8.0f;
	constexpr float kSlideCrouchSpeed = 10.0f;
	// 姿勢ごとの高さ
	constexpr float kStandHeight = 0.0f;
	constexpr float kCrouchHeight = -70.0f;
	constexpr float kDeadHeight = -140.0f;

	// スライディング時間
	constexpr int kSlideTime = 20;
	// スライディングクールダウン
	constexpr int kSlideCoolTime = 60;

	// マウス感度
	constexpr float kMouseSensitivity = 0.09f;
	// プレイヤー視点移動速度
	constexpr float kPovMoveSpeed = 4.0f;
	// プレイヤーからカメラまでの距離
	constexpr float kLookPosDistance = 120.0f;

	// ロックオン範囲
	constexpr float kLockRange = 50.0f;

	// ショット遅延
	constexpr int kShotDelay = 3;
	// ショットのダメージ
	constexpr int kShotDamage = 10;

	// 体力
	constexpr int kMaxHp = 50;
	// 無敵時間
	constexpr int kDamageInvTime = 60;
	// 体力回復までの時間
	constexpr int kRecoveryTime = 120;

	// ステージの範囲外ダメージ
	constexpr int kStageOutDamage = 10;

	// ヒットマーク描画フレーム
	constexpr int kHitMarkFrame = 10;

	// 描画FPSハンド拡大率
	constexpr double kFpsHandScale = 10.0;
}

Player::Player():
	ObjectBase(),
	m_posture(PostureType::stand),
	m_handState(HandState::Normal),
	m_hFpsHand(-1),
	m_hCursorImg(-1),
	m_hLockCursorImg(-1),
	m_hHitCursorImg(-1),
	m_HandSizeX(0),
	m_HandSizeY(0),
	m_frameCount(0),
	m_handFrame(0),
	m_handFrameMax(0),
	m_shotFrame(0),
	m_slideTime(0),
	m_invTime(0),
	m_recoveryTime(0),
	m_hitMarkFrame(0),
	m_tileX(0),
	m_tileZ(0),
	m_isMove(false),
	m_isDash(false),
	m_isLockOn(false),
	m_isShot(false),
	m_eyeHeight(kStandHeight),
	m_playerAngleY(0.0f),
	m_playerAngleX(0.0f),
	m_slideVec(Game::kVecZero),
	m_lockObjPos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pStage(nullptr),
	m_pEnemyManager(nullptr),
	m_pCamera(nullptr)
{
}

Player::~Player()
{
	// 画像削除
	m_status.hImg = -1;
	m_hCursorImg = -1;
	m_hLockCursorImg = -1;
	m_hHitCursorImg = -1;
}

void Player::Init()
{
	// 画像読み込み
	m_hFpsHand = Load::GetInstance().GetImageHandle("fpsHand");
	m_hCursorImg = Load::GetInstance().GetImageHandle("cursor");
	m_hLockCursorImg = Load::GetInstance().GetImageHandle("lockCursor");
	m_hHitCursorImg = Load::GetInstance().GetImageHandle("hitCursor");
	// 画像サイズ取得
	GetGraphSize(m_hFpsHand, &m_HandSizeX, &m_HandSizeY);
	m_handFrameMax = (m_HandSizeX / Game::k2DChipSize) - 1;
	// 画像拡大率設定
	m_status.scale = kScale;
	// 移動速度設定
	m_status.moveSpeed = kPlayerMoveSpeed;
	// 体力設定
	m_status.hp = kMaxHp;
	// 視点更新
	UpdateView();
}

void Player::Update(const InputState& input)
{
	// 毎フレームカウント
	m_frameCount++;
	if (m_frameCount >= 60) m_frameCount = 0;

	// 無敵時間減少
	if (m_invTime > 0) m_invTime--;

	// 体力回復時間減少
	if (m_recoveryTime > 0) m_recoveryTime--;

	// 現在のタイル番号
	m_pStage->GetTile(m_status.pos, m_tileX, m_tileZ);

	// 移動処理
	ControllMove(input);
	// 姿勢更新
	UpdatePosture(input);
	// ステージの範囲内にプレイヤーを制限
	CheckStageRange();

	// ギミック処理
	ControllGimmick(input);

	// 視点処理
	ControllView(input);
	// 視点更新
	UpdateView();

	// 移動時の画面揺れ処理
	if (m_isMove)
	{
		m_pCamera->OnMoveQuake();
	}

	// カーソル更新
	UpdateCursor(input);
	// ショット管理
	ControllShot(input);
	// ショット更新
	UpdateShot();

	// 体力更新
	UpdateHp();
	// 手の状態更新
	UpdateHandState();

	// UIにプレイヤー座標を送信
	UiManager::GetInstance().SetPlayerPos(m_status.pos);
}

void Player::UpdateGameover()
{
	// 姿勢更新
	m_eyeHeight -= kCrouchSpeed;
	if (m_eyeHeight < kDeadHeight)
	{
		m_eyeHeight = kDeadHeight;
	}
	// 高さ反映
	m_status.pos.y = m_eyeHeight;

	// 視点更新
	UpdateView();
	// ショット更新
	UpdateShot();
}

void Player::Draw()
{
	// ショット描画
	for (auto& shot : m_pShots)
	{
		shot->Draw();
	}
	// 2D描画
	Draw2D();
}

void Player::OnDamage(int damage)
{
	// 無敵時間中なら
	if (m_invTime > 0) return;

	// 体力回復時間が0なら
	m_recoveryTime = kRecoveryTime;

	// 体力減少
	m_status.hp -= damage;
	// 体力が0以下なら
	if (m_status.hp <= 0)
	{
		// 体力を0に設定
		m_status.hp = 0;
		// ゲームオーバー
		m_status.isDead = true;
	}
	// カメラ揺れ処理
	m_pCamera->OnDamageQuake();
	// 無敵時間設定
	m_invTime = kDamageInvTime;
}

void Player::CheckStageRange()
{
	// ステージの上下の範囲外に出た場合ダメージ
	if (m_status.pos.y < -Game::kStageSizeY)
	{
		OnDamage(kStageOutDamage);
	}
}

void Player::ControllView(const InputState& input)
{
	// マウス感度による視点移動
	m_playerAngleX += input.GetMouseMoveX() * kMouseSensitivity;
	m_playerAngleY -= input.GetMouseMoveY() * kMouseSensitivity;

	// 右視点移動
	if (input.IsPressed(InputType::lookRight))
	{
		m_playerAngleX += kPovMoveSpeed;
	}
	// 左視点移動
	else if (input.IsPressed(InputType::lookLeft))
	{
		m_playerAngleX += -kPovMoveSpeed;
	}
	// 上視点移動
	if (input.IsPressed(InputType::lookUp))
	{
		m_playerAngleY += kPovMoveSpeed;
	}
	// 下視点移動
	else if (input.IsPressed(InputType::lookDown))
	{
		m_playerAngleY += -kPovMoveSpeed;
	}
}

void Player::UpdateView()
{
	// 注視点横方向の処理
	{
		// 注視点の角度の限界を指定
		if (m_playerAngleX > 360.0f)
		{
			m_playerAngleX = 0;
		}
		if (m_playerAngleX < 0)
		{
			m_playerAngleX = 360.0f;
		}

		// 角度をラジアンに変換
		float rad = m_playerAngleX * (DX_PI_F / 180.0f);

		// 中心位置から半径をもとに軌道を計算
		m_status.lookDir.x = sin(rad);
		m_status.lookDir.z = cos(rad);
	}

	// 注視点縦方向の処理
	{
		// 注視点の角度の限界を指定
		if (m_playerAngleY > 89.0f)
		{
			m_playerAngleY = 89.0f;
		}
		if (m_playerAngleY < -89.0f)
		{
			m_playerAngleY = -89.0f;
		}

		// 角度をラジアンに変換
		float rad = m_playerAngleY * (DX_PI_F / 180.0f);

		// 中心位置から半径をもとに軌道を計算
		m_status.lookDir.y = tan(rad);
	}

	// 正規化
	if (VSize(m_status.lookDir) > 0) m_status.lookDir = VNorm(m_status.lookDir);
	m_status.lookDir = VScale(m_status.lookDir, kLookPosDistance);
	// 中心位置の代入
	m_status.lookPos = m_status.pos;
	// ベクトルを位置に加算
	m_status.lookPos = VAdd(m_status.lookPos, m_status.lookDir);

	// カメラ位置設定
	m_pCamera->SetPosAndTarget(m_status.pos, m_status.lookPos);
}

void Player::ControllGimmick(const InputState& input)
{
	// ギミック操作
	if (m_currentStageData[m_tileZ][m_tileX] == StageTile::SW)
	{
		// インタラクトキー
		if (input.IsTriggered(InputType::Interract))
		{
			// ギミック処理
			m_pStage->SwitchOn(m_tileX, m_tileZ);
		}
	}
}

void Player::ControllMove(const InputState& input)
{
	// 移動中フラグ
	m_isMove = false;
	// ダッシュ中フラグ
	m_isDash = false;

	// 地面判定チェック
	CheckGround();

	// 地面にいるときのみ移動入力
	if (m_status.isGround)
	{
		// 慣性処理
		m_status.moveSpeed -= kInertia;
		if (m_status.moveSpeed < 0.0f) m_status.moveSpeed = 0.0f;

		// 前方移動入力
		if (input.IsPressed(InputType::moveForward))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			m_status.dir = VAdd(m_status.dir, tempDir);
			// 移動中フラグON
			m_isMove = true;

			// ダッシュ入力
			if (input.IsPressed(InputType::dash))
			{
				// ダッシュ判定
				m_isDash = true;
			}
		}
		// 後方移動入力
		if (input.IsPressed(InputType::moveBehind))
		{
			VECTOR tempDir = VSub(m_status.pos, m_status.lookPos);
			tempDir.y = 0.0f;
			m_status.dir = VAdd(m_status.dir, tempDir);
			// 移動中フラグON
			m_isMove = true;
		}
		// 右移動入力
		if (input.IsPressed(InputType::moveRight))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			// 進行方向右へ90度回転
			MATRIX mtx = MGetRotY(DX_PI_F / 2);
			tempDir = VTransform(tempDir, mtx);
			m_status.dir = VAdd(m_status.dir, tempDir);
			// 移動中フラグON
			m_isMove = true;
		}
		// 左移動入力
		if (input.IsPressed(InputType::moveLeft))
		{
			VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
			tempDir.y = 0.0f;
			// 進行方向左へ90度回転
			MATRIX mtx = MGetRotY(-DX_PI_F / 2);
			tempDir = VTransform(tempDir, mtx);
			m_status.dir = VAdd(m_status.dir, tempDir);
			// 移動中フラグON
			m_isMove = true;
		}
	}

	if (m_isMove)
	{
		// ダッシュ入力
		if (m_isDash && !m_isShot)
		{
			// しゃがみ姿勢なら
			if (m_posture == PostureType::crouch)
			{
				m_posture = PostureType::stand;
			}

			// ダッシュ中は速度２倍
			if (m_status.moveSpeed < kPlayerDashSpeed)
			{
				m_status.moveSpeed += kPlayerMoveAccel;
			}
			// 最高速度
			else
			{
				m_status.moveSpeed = kPlayerDashSpeed;
			}
		}
		else
		{
			// 通常速度
			if (m_status.moveSpeed < kPlayerMoveSpeed)
			{
				m_status.moveSpeed += kPlayerMoveAccel;
			}
			// 最高速度
			else
			{
				m_status.moveSpeed = kPlayerMoveSpeed;
			}
		}
	}

	// 通常の移動処理
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
	auto nextPos = VAdd(m_status.pos, m_status.dir);
	// 移動が可能かの判定
	if (CheckCanMove(nextPos))
	{
		// 移動処理
		m_status.pos = nextPos;
	}


	// ジャンプ処理
	if (m_status.isGround)
	{
		// ジャンプ力初期化
		m_status.jumpPower = 0.0f;
		if (input.IsTriggered(InputType::jump))
		{
			if (m_posture == PostureType::stand)
			{
				// ジャンプ処理
				m_status.jumpPower += kJumpPower;
				// 空中判定
				m_status.isGround = false;
			}
			else if (m_posture == PostureType::crouch)
			{
				// 立ち姿勢
				m_posture = PostureType::stand;
			}
		}
	}
	else
	{
		// 重力加算
		m_status.jumpPower -= kGravity;
	}
	// ジャンプ処理を座標に加算
	m_status.pos.y += m_status.jumpPower;
}

void Player::CheckGround()
{
	// 現在のタイルが地面の場合
	if (m_currentStageData[m_tileZ][m_tileX] != StageTile::EN)
	{
		VECTOR tilePos = MV1GetPosition(m_pStage->GetTileHandle(m_tileX, m_tileZ));
		// 地面判定
		if (m_status.pos.y <= 0.0f &&
			tilePos.y + (Game::k3DChipSize / 2) < m_status.pos.y)
		{
			// 地面判定
			m_status.isGround = true;
		}
		else
		{
			// 空中判定
			m_status.isGround = false;
		}
	}
	else
	{
		// 空中判定
		m_status.isGround = false;
	}
}

bool Player::CheckCanMove(VECTOR nextPos)
{
	// 移動先のタイル番号を取得
	int tileX = NULL;
	int tileZ = NULL;
	m_pStage->GetTile(nextPos, tileX, tileZ);

	// 移動先のタイルが壁じゃない場合
	if (m_currentStageData[tileZ][tileX] == StageTile::WL)
	{
		// 移動不可能
		return false;
	}
	else if (m_currentStageData[tileZ][tileX] == StageTile::F1)
	{
		// 移動不可能
		return false;
	}
	else if (m_currentStageData[tileZ][tileX] == StageTile::F2)
	{
		// 移動不可能
		return false;
	}

	return true;
}

void Player::UpdatePosture(const InputState& input)
{
	// スライディング処理
	if (m_posture == PostureType::slide)
	{
		UpdateSlide();
		return;
	}

	// しゃがみ判定
	if (input.IsTriggered(InputType::crouch))
	{
		// ダッシュの最高速の場合
		if (m_status.moveSpeed >= kPlayerDashSpeed)
		{
			// 地面にいるときのみスライディング
			if (m_status.isGround)
			{
				// スライディング処理
				OnSlide();

				return;
			}
		}

		// 立ち姿勢なら
		if(m_posture == PostureType::stand)
		{
			// しゃがみ姿勢
			m_posture = PostureType::crouch;
		}
		// しゃがみ姿勢なら
		else if(m_posture == PostureType::crouch)
		{
			// 立ち姿勢
			m_posture = PostureType::stand;
		}
	}

	// しゃがみ姿勢
	if (m_posture == PostureType::stand)
	{
		m_eyeHeight += kCrouchSpeed;
		if (m_eyeHeight > kStandHeight)
		{
			m_eyeHeight = kStandHeight;
		}
	}
	// 伏せ姿勢
	else if (m_posture == PostureType::crouch)
	{
		m_eyeHeight -= kCrouchSpeed;
		if (m_eyeHeight < kCrouchHeight)
		{
			m_eyeHeight = kCrouchHeight;
		}
	}

	// 姿勢による座標調整
	if (m_status.isGround)
	{
		m_status.pos.y = m_eyeHeight;
	}
}

void Player::UpdateSlide()
{
	// スライディング処理
	if(m_slideTime > 0)
	{
		// スライディング時間減少
		m_slideTime--;
		// スライディング座標加算
		m_status.pos = VAdd(m_status.pos, m_slideVec);
	}
	else
	{
		// 立ち姿勢
		m_posture = PostureType::stand;
		// スライディング速度初期化
		m_slideVec = Game::kVecZero;
	}

	// スライディング姿勢変更
	m_eyeHeight -= kSlideCrouchSpeed;
	if (m_eyeHeight < kCrouchHeight)
	{
		m_eyeHeight = kCrouchHeight;
	}

	// 高さ反映
	m_status.pos.y = m_eyeHeight;
}

void Player::OnSlide()
{
	// スライディング姿勢
	m_posture = PostureType::slide;
	// スライディング時間設定
	m_slideTime = kSlideTime;
	// スライディング中は無敵
	m_invTime = kSlideTime;

	// 進行方向ベクトル取得
	m_slideVec = VSub(m_status.lookPos, m_status.pos);
	m_slideVec.y = 0.0f;
	// 正規化
	if (VSize(m_slideVec) > 0) m_slideVec = VNorm(m_slideVec);
	// 速度設定
	m_slideVec = VScale(m_slideVec, m_status.moveSpeed * kSlideRate);
}

void Player::ControllShot(const InputState& input)
{
	// ターゲット位置
	VECTOR targetPos = m_status.lookPos;
	// 着弾地点の座標
	VECTOR targetDir = VSub(targetPos, m_pCamera->GetPos());
	if (VSize(targetDir) > 0) targetDir = VNorm(targetDir);
	targetDir = VScale(targetDir, ShotParam::kShotSpeed);
	m_targetPos = VAdd(m_pCamera->GetPos(), VScale(targetDir, ShotParam::kShotTime));

	// 射撃ボタンが押されたら
	if (input.IsPressed(InputType::shot))
	{
		// 射撃中フラグON
		m_isShot = true;
	}

	// スペシャルショットボタンが押されたら
	if (input.IsTriggered(InputType::sprShot))
	{
		// 射撃中フラグONだった場合
		if (m_isShot) return;

		// ロックオン中なら
		if (m_isLockOn)
		{
			// スペシャルショット生成
			CreateSprShot();
		}
	}
}

void Player::CreateShot()
{
	// ショットサウンド再生
	SoundManager::GetInstance().PlaySE(SoundType::shot);
	// ショット生成
	m_pShots.push_back(new Shot(m_status.pos, m_targetPos));
}

void Player::CreateSprShot()
{
	// ショットサウンド再生
	SoundManager::GetInstance().PlaySE(SoundType::sprShot);

	// ショット生成
	m_pShots.push_back(new Shot(m_status.pos, m_pTargetObj));
}

void Player::UpdateShot()
{
	// 射撃中なら
	if (m_isShot)
	{
		// ショットフレーム更新
		m_shotFrame++;
		// ショット生成
		if (m_shotFrame >= m_handFrameMax * kShotDelay)
		{
			// ショット生成
			CreateShot();
			// ショットフレーム初期化
			m_shotFrame = 0;
			// 射撃中フラグOFF
			m_isShot = false;
			// 手の描画用フレーム初期化
			m_handFrame = 0;
		}
	}

	// ショット更新
	for (auto& shot : m_pShots)
	{
		shot->Update();
		// 敵との当たり判定
		for (auto& obj : m_pEnemyManager->GetEnemies())
		{
			if (shot->CheckCollision(obj))
			{
				// 敵ヒット処理
				obj->OnHit(kShotDamage);
				// ショットヒット処理
				this->OnHitShot(shot);
			}
		}
	}

	// ショット削除
	m_pShots.remove_if([](Shot* shot) {return !shot->IsEnabled(); });
}

void Player::OnHitShot(Shot* pShot)
{
	// ショット削除
	pShot->OnHit();
	// ヒットマーク表示
	m_hitMarkFrame = kHitMarkFrame;
	// ヒットサウンド再生
	SoundManager::GetInstance().PlaySE(SoundType::shotHit);
}

void Player::UpdateCursor(const InputState& input)
{
	// 座標と判定リセット
	m_lockObjPos = Game::kVecZero;
	m_isLockOn = false;
	// ロックオンカーソル座標取得
	for (auto& obj : m_pEnemyManager->GetEnemies())
	{
		if (obj->IsEnabled())
		{
			VECTOR objPos = obj->GetPos();
			VECTOR screenPos = ConvWorldPosToScreenPos(objPos);

			// カーソルとオブジェクトの距離を計算
			float distance = VSize(VSub(screenPos, Game::kScreenCenter));

			// カーソルとオブジェクトの距離が一定範囲内なら
			if (distance < kLockRange)
			{
				// ロックオンカーソル座標設定
				m_lockObjPos = objPos;
				// ロックオンフラグON
				m_isLockOn = true;
				// ロックオンオブジェクト設定
				m_pTargetObj = obj;
				break;
			}
		}
	}
}

void Player::UpdateHp()
{
	if(m_recoveryTime <= 0)
	{
		// 体力回復
		m_status.hp++;
		if (m_status.hp > kMaxHp)
		{
			m_status.hp = kMaxHp;
		}
	}
}

void Player::UpdateHandState()
{
	if (m_isShot)
	{
		m_handState = HandState::Shot;
	}
	else
	{
		m_handState = HandState::Normal;
	}

	if (m_handState == HandState::Normal)
	{
		// 手の状態更新
		if(m_frameCount % 30 == 0) m_handFrame++;
		// 手の描画用フレーム初期化
		if (m_handFrame > m_handFrameMax)
		{
			m_handFrame = 0;
		}
	}
	else if (m_handState == HandState::Shot)
	{
		// 手の描画用フレーム更新
		if (m_shotFrame % kShotDelay == 0) m_handFrame++;
		// 手の描画用フレーム初期化
		if (m_handFrame > m_handFrameMax)
		{
			m_handFrame = 0;
		}
	}
}

void Player::Draw2D()
{
	// クロスヘア描画
	DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0f, 0.0f, m_hCursorImg, true);
	// ロックオンカーソル描画
	if (m_isLockOn)
	{
		VECTOR lockCursorPos = ConvWorldPosToScreenPos(m_lockObjPos);
		DrawRotaGraphF(lockCursorPos.x, lockCursorPos.y, 1.0f, 0.0f, m_hLockCursorImg, true);
	}
	// ヒットマーク描画
	if (m_hitMarkFrame > 0)
	{
		// 描画
		DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0f, 0.0f, m_hHitCursorImg, true);
		// フレーム減少
		m_hitMarkFrame--;
	}

	// FPSハンド描画
	DrawRectRotaGraphF(static_cast<float>(Game::kScreenWidth - (Game::k2DChipSize * kFpsHandScale) + 60.0f),
		static_cast<float>(Game::kScreenHeight - (Game::k2DChipSize * kFpsHandScale) / 2),
		static_cast<int>(Game::k2DChipSize * m_handFrame), static_cast<int>(m_handState) * Game::k2DChipSize,
		static_cast<int>(Game::k2DChipSize), static_cast<int>(Game::k2DChipSize),
		kFpsHandScale, 0.0f,
		m_hFpsHand,true);

	// 体力描画
	DrawFormatString(Game::kScreenWidth - 200, 10, 0xffffff, "HP:%d", m_status.hp);
}
