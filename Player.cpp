#include "Player.h"
#include "Game.h"
#include "Shot.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Load.h"

namespace
{
	// 画像拡大率
	constexpr float kScale = 100.0f;
	// ロックオン範囲
	constexpr float kLockRange = 50.0f;
}

Player::Player():
	ObjectBase(),
	m_hCursorImg(-1),
	m_hLockCursorImg(-1),
	m_isLockOn(false),
	m_cursorPos(Game::kVecZero),
	m_lockObjPos(Game::kVecZero),
	m_pShots(),
	m_pTargetObj(nullptr),
	m_pEnemyManager(nullptr)
{
	// 画像読み込み
	m_status.hImg = Load::GetInstance().GetHandle("player");
	m_hCursorImg = Load::GetInstance().GetHandle("cursor");
	m_hLockCursorImg = Load::GetInstance().GetHandle("lockCursor");
	// 画像拡大率設定
	m_status.scale = kScale;
}

Player::~Player()
{
	// 画像削除
	m_status.hImg = -1;
	m_hCursorImg = -1;
	m_hLockCursorImg = -1;
}

void Player::Init()
{
}

void Player::Update(const InputState& input)
{
	// カーソル更新
	UpdateCursor(input);

	// 射撃ボタンが押されたら
	if (input.IsTriggered(InputType::shot))
	{
		if (m_isLockOn)
		{
			// ショット生成
			CreateShot();
		}
	}

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

void Player::CreateShot()
{
	// ショット生成
	m_pShots.push_back(new Shot(m_status.pos, m_pTargetObj));
}

void Player::UpdateShot()
{
	// ショット更新
	for (auto& shot : m_pShots)
	{
		shot->Update();
		for (auto& obj : m_pEnemyManager->GetEnemies())
		{
			if (obj->IsEnabled())
			{
				if (shot->CheckCollision(obj))
				{
					// ショット削除
					shot->OnHit();
					// 敵ヒット処理
					obj->OnHit();
					break;
				}
			}
		}
	}

	// ショット削除
	m_pShots.remove_if([](Shot* shot) {return !shot->IsEnabled(); });
}

void Player::UpdateCursor(const InputState& input)
{
	// カーソル座標取得
	m_cursorPos.x = input.GetMousePosX();
	m_cursorPos.y = input.GetMousePosY();

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
			float distance = VSize(VSub(screenPos, m_cursorPos));

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
	// 画像描画
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
	// ロックオンカーソル描画
	if (m_isLockOn)
	{
		VECTOR lockCursorPos = ConvWorldPosToScreenPos(m_lockObjPos);
		DrawRotaGraphF(lockCursorPos.x, lockCursorPos.y, 1.0f, 0.0f, m_hLockCursorImg, true);
	}
	// カーソル描画
	DrawRotaGraphF(m_cursorPos.x, m_cursorPos.y, 1.0f, 0.0f, m_hCursorImg, true);
}
