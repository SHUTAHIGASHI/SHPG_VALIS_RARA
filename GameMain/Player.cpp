#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"
#include "CameraManager.h"
#include "SoundManager.h"

namespace
{
	// 画像拡大率
	constexpr float kScale = 100.0f;

	// 移動速度
	constexpr float kPlayerMoveSpeed = 12.0f;
	// ダッシュ率
	constexpr float kDashRate = 2.0f;
	// 重力
	constexpr float kGravity = 0.5f;
	// ジャンプ力
	constexpr float kJumpPower = 12.0f;

	// マウス感度
	constexpr float kMouseSensitivity = 0.09f;
	// プレイヤー視点移動速度
	constexpr float kPovMoveSpeed = 4.0f;
	// プレイヤーからカメラまでの距離
	constexpr float kLookPosDistance = 120.0f;

	// ロックオン範囲
	constexpr float kLockRange = 50.0f;
	// ショット連射速度
	constexpr int kShotRate = 10;
}

Player::Player():
	ObjectBase(),
	m_hCursorImg(-1),
	m_hLockCursorImg(-1),
	m_shotDelay(kShotRate),
	m_isLockOn(false),
	m_playerAngleY(0.0f),
	m_playerAngleX(0.0f),
	m_lockObjPos(Game::kVecZero),
	m_targetPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr),
	m_pCamera(nullptr)
{
	// 画像読み込み
	m_hFpsHand = Load::GetInstance().GetHandle("fpsHand");
	m_hCursorImg = Load::GetInstance().GetHandle("cursor");
	m_hLockCursorImg = Load::GetInstance().GetHandle("lockCursor");
	// 画像サイズ取得
	GetGraphSize(m_hFpsHand, &m_HandSizeX, &m_HandSizeY);
	// 画像拡大率設定
	m_status.scale = kScale;
	// 移動速度設定
	m_status.moveSpeed = kPlayerMoveSpeed;
}

Player::~Player()
{
	// 画像削除
	m_status.hImg = -1;
	m_hLockCursorImg = -1;
}

void Player::Init()
{
}

void Player::Update(const InputState& input)
{
	// 移動処理
	ControllMove(input);
	// 視点処理
	ControllView(input);
	// 視点更新
	UpdateView();

	// カーソル更新
	UpdateCursor(input);
	// ショット管理
	ControllShot(input);
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

void Player::OnHit()
{
	// カメラ揺れ処理
	m_pCamera->OnScreenQuake();
}

void Player::ControllView(const InputState& input)
{
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

void Player::ControllMove(const InputState& input)
{
	// 地面判定チェック
	if (m_status.pos.y <= 0.0f)
	{
		// 地面判定
		m_status.isGround = true;
	}
	else
	{
		// 空中判定
		m_status.isGround = false;
	}

	// 移動ベクトル
	VECTOR moveDir = Game::kVecZero;

	// ダッシュ入力
	if (input.IsPressed(InputType::dash))
	{
		m_status.moveSpeed = kPlayerMoveSpeed * kDashRate;
	}
	else
	{
		m_status.moveSpeed = kPlayerMoveSpeed;
	}

	// 前方移動入力
	if (input.IsPressed(InputType::moveForward))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		moveDir = VAdd(moveDir, tempDir);
	}
	// 後方移動入力
	if (input.IsPressed(InputType::moveBehind))
	{
		VECTOR tempDir = VSub(m_status.pos, m_status.lookPos);
		tempDir.y = 0.0f;
		moveDir = VAdd(moveDir, tempDir);
	}
	// 右移動入力
	if (input.IsPressed(InputType::moveRight))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		// 進行方向右へ90度回転
		MATRIX mtx = MGetRotY(DX_PI_F / 2);
		tempDir = VTransform(tempDir, mtx);
		moveDir = VAdd(moveDir, tempDir);
	}
	// 左移動入力
	if (input.IsPressed(InputType::moveLeft))
	{
		VECTOR tempDir = VSub(m_status.lookPos, m_status.pos);
		tempDir.y = 0.0f;
		// 進行方向左へ90度回転
		MATRIX mtx = MGetRotY(-DX_PI_F / 2);
		tempDir = VTransform(tempDir, mtx);
		moveDir = VAdd(moveDir, tempDir);
	}
	// 通常の移動処理
	if (VSize(moveDir) > 0) moveDir = VNorm(moveDir);
	moveDir = VScale(moveDir, m_status.moveSpeed);
	m_status.pos = VAdd(m_status.pos, moveDir);

	// ジャンプ処理
	if (m_status.isGround)
	{
		// ジャンプ力初期化
		m_status.jumpPower = 0.0f;
		if (input.IsTriggered(InputType::jump))
		{
			// ジャンプ処理
			m_status.jumpPower += kJumpPower;
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

void Player::ControllShot(const InputState& input)
{
	// ターゲット位置
	VECTOR targetPos = m_status.lookPos;
	// 着弾地点の座標
	VECTOR targetDir = VSub(targetPos, m_pCamera->GetPos());
	if (VSize(targetDir) > 0) targetDir = VNorm(targetDir);
	targetDir = VScale(targetDir, ShotParam::kShotSpeed);
	m_targetPos = VAdd(m_pCamera->GetPos(), VScale(targetDir, ShotParam::kShotTime));

	// ショット連射速度
	m_shotDelay--;
	if (m_shotDelay < 0)
	{
		m_shotDelay = 0;
	}

	// 射撃ボタンが押されたら
	if (input.IsPressed(InputType::shot))
	{
		if (m_shotDelay <= 0)
		{
			// ショット生成
			CreateShot();
		}
	}

	// スペシャルショットボタンが押されたら
	if (input.IsTriggered(InputType::sprShot))
	{
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

	// ショット連射速度初期化
	if (m_shotDelay <= 0)
	{
		m_shotDelay = kShotRate;
	}
}

void Player::CreateSprShot()
{
	// ショットサウンド再生
	SoundManager::GetInstance().PlaySE(SoundType::sprShot);

	// ショット生成
	m_pShots.push_back(new Shot(m_status.pos, m_pTargetObj));

	// ショット連射速度初期化
	if (m_shotDelay <= 0)
	{
		m_shotDelay = kShotRate;
	}
}

void Player::UpdateShot()
{
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
				obj->OnHit();
				// ショット削除
				shot->OnHit();
			}
		}
	}

	// ショット削除
	m_pShots.remove_if([](Shot* shot) {return !shot->IsEnabled(); });
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
	// FPSハンド描画
	DrawRotaGraphF(static_cast<float>(Game::kScreenWidth - (m_HandSizeX * 10.0f)),
		static_cast<float>(Game::kScreenHeight - (m_HandSizeY * 10.0f) / 2),
		10.0f, 0.0f, m_hFpsHand, true);
}
