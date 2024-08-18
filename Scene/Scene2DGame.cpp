#include "Scene2DGame.h"
#include "SceneManager.h"
#include "ScenePauseMenu.h"
#include "SceneTitleMenu.h"
#include "Load.h"
#include "SoundManager.h"
#include <string>

namespace
{
	// チップサイズ
	constexpr float kChipSize = 48.0f;
	// 当たり判定半径
	constexpr float kHitRadius = 32.0f;
	// ステージ限界
	constexpr float kStageLimit = Game::kScreenHeight - 150.0f;
	// ゲームカウント
	constexpr int kGameCount = 60 * 30;
}

namespace PlayerState
{
	// 移動速度
	constexpr float kMoveSpeed = 6.0f;
	// ショット遅延
	constexpr int kShotDelay = 16;
	// 拡大率
	constexpr float kScale = 2.0f;
}

namespace EnemyState
{
	// 移動速度
	constexpr float kMoveSpeed = 2.0f;
	// 出現間隔
	constexpr int kAppearInterval = 120;
	// 出現数
	constexpr int kAppearCount = 10;
}

Scene2DGame::Scene2DGame(SceneManager& manager) : Scene(manager),
m_hPlayerImg(-1),
m_playerPos(VGet(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 0.0f)),
m_shots(),
m_hShotImg(-1),
m_shotDelay(0),
m_enemies(),
m_hEnemyImg(-1),
m_enemyCount(0),
m_hBackImg(-1),
m_gameCount(0),
m_killCount(0),
m_hCursorImg(-1),
m_cursorPos(VGet(0.0f, 0.0f, 0.0f)),
m_hBoardImg(-1),
m_isGameEnd(false)
{
	m_hPlayerImg = LoadGraph("Data/ImageData/Legacy/rara.png");
	m_hShotImg = Load::GetInstance().GetImageHandle("shot");
	m_hEnemyImg = LoadGraph("Data/ImageData/Legacy/neffy.png");
	m_hBackImg = LoadGraph("Data/ImageData/Legacy/GameBg.jpg");
	m_hBoardImg = LoadGraph("Data/ImageData/Legacy/Board.png");
	m_hCursorImg = Load::GetInstance().GetImageHandle("cursor");

	// カーソル削除
	SetMouseDispFlag(false);
}

Scene2DGame::~Scene2DGame()
{
	DeleteGraph(m_hPlayerImg);
	DeleteGraph(m_hEnemyImg);
	DeleteGraph(m_hBackImg);
	m_hShotImg = -1;
	m_hCursorImg = -1;
	// カーソル削除
	SetMouseDispFlag(true);
}

void Scene2DGame::Init()
{
	// プレイヤー座標初期化
	m_playerPos = VGet(Game::kScreenWidthHalf, kStageLimit, 0.0f);
	// ショット初期化
	m_shots.clear();
	// エネミー初期化
	m_enemies.clear();
	// カーソル座標
	m_cursorPos = VGet(0.0f, 0.0f, 0.0f);
	// カーソル削除
	SetMouseDispFlag(false);
	// ショット遅延
	m_shotDelay = 0;
	// エネミー出現カウント
	m_enemyCount = 0;
	// ゲームカウント
	m_gameCount = kGameCount;
}

void Scene2DGame::Update(const InputState& input)
{
	// ゲームカウント
	m_gameCount--;
	if (m_gameCount <= 0)
	{
		m_isGameEnd = true;
	}

	// ポーズメニュー
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// カーソル座標
	m_cursorPos.x = input.GetMousePosX();
	m_cursorPos.y = input.GetMousePosY();

	if (!m_isGameEnd)
	{
		// プレイヤー更新
		UpdatePlayer(input);
		// ショット更新
		UpdateShot();
		// エネミー更新
		UpdateEnemy();
	}
	else
	{
		if (input.IsTriggered(InputType::select))
		{
			m_Manager.ChangeScene(new SceneTitleMenu(m_Manager));
		}
	}
}

void Scene2DGame::Draw()
{
	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// プレイヤー描画
	DrawPlayer();
	// ショット描画
	DrawShot();
	// エネミー描画
	DrawEnemy();

	// ステージ限界描画
	DrawLine(0, kStageLimit, Game::kScreenWidth, kStageLimit, 0xffffff);

	if (m_isGameEnd)
	{
		DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0, 0, m_hBoardImg, true);
		// ゲームカウント描画
		std::string drawText = "倒したネフィさん:" + std::to_string(m_killCount);
		auto textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - 60.0f, 0xffffff, "%s", drawText.c_str());
		drawText = "タイトルへ戻ります";
		textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf + 30.0f, 0xffffff, "%s", drawText.c_str());
		return;
	}
	else
	{
		// ゲームカウント描画
		std::string drawText = std::to_string(m_gameCount / 60);
		SetFontSize(60);
		auto textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), kStageLimit + 40, 0xffffff, "%s", drawText.c_str());
		SetFontSize(Game::kFontSize);
	}

	// カーソル描画
	DrawRotaGraphF(m_cursorPos.x, m_cursorPos.y, 1.0, 0, m_hCursorImg, true);
}

void Scene2DGame::End()
{
}

void Scene2DGame::UpdatePlayer(const InputState& input)
{
	// ショット遅延
	if (m_shotDelay > 0) m_shotDelay--;

	if (input.IsPressed(InputType::left))
	{
		m_playerPos.x -= PlayerState::kMoveSpeed;
	}
	if (input.IsPressed(InputType::right))
	{
		m_playerPos.x += PlayerState::kMoveSpeed;
	}

	// 画面外処理
	if (m_playerPos.x < 0) m_playerPos.x = 0;
	if (m_playerPos.x > Game::kScreenWidth) m_playerPos.x = Game::kScreenWidth;
	if (m_playerPos.y < 0) m_playerPos.y = 0;
	if (m_playerPos.y > Game::kScreenHeight) m_playerPos.y = Game::kScreenHeight;

	// ショット発射
	if (input.IsPressed(InputType::shot))
	{
		if (m_shotDelay > 0) return;

		m_shotDelay = PlayerState::kShotDelay;
		m_shots.push_back(Shot());
		m_shots.back().shotPos = m_playerPos;
		m_shots.back().shotDir = VSub(m_cursorPos, m_playerPos);
		// 正規化
		if (VSize(m_shots.back().shotDir) > 0) m_shots.back().shotDir = VNorm(m_shots.back().shotDir);
		m_shots.back().shotDir = VScale(m_shots.back().shotDir, m_shots.back().shotSpeed);
		// ショットサウンド
		SoundManager::GetInstance().PlaySE(SoundType::shot);
	}
}

void Scene2DGame::DrawPlayer()
{
	DrawRotaGraphF(m_playerPos.x, m_playerPos.y, PlayerState::kScale, 0, m_hPlayerImg, true);
}

void Scene2DGame::UpdateShot()
{
	// ショット更新
	for (auto& shot : m_shots)
	{
		shot.shotPos = VAdd(shot.shotPos, shot.shotDir);
	}

	// ショット当たり判定
	m_shots.remove_if([this](const Shot& shot)
	{
		for (auto& enemy : m_enemies)
		{
			if (VSize(VSub(enemy.enemyPos, shot.shotPos)) < kHitRadius)
			{
				// エネミー削除
				enemy.isDelete = true;
				// キルカウント
				m_killCount++;
				// エネミーサウンド
				SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
				return true;
			}
		}
		return false;
	});

	// 画面外処理
	m_shots.remove_if([](const Shot& shot)
	{
		if (shot.shotPos.x < 0 || shot.shotPos.x > Game::kScreenWidth ||
			shot.shotPos.y < 0 || shot.shotPos.y > Game::kScreenHeight)
		{
			return true;
		}
		return false;
	});
}

void Scene2DGame::DrawShot()
{
	for (auto& shot : m_shots)
	{
		DrawRotaGraphF(shot.shotPos.x, shot.shotPos.y, 1.0, 0, m_hShotImg, true);
	}
}

void Scene2DGame::UpdateEnemy()
{
	if (m_enemyCount > 0) m_enemyCount--;

	if (m_enemyCount <= 0)
	{
		if (m_enemies.size() < EnemyState::kAppearCount)
		{
			m_enemyCount = GetRand(EnemyState::kAppearInterval);
			m_enemies.push_back(Enemy());
			// ランダムな生成座標
			float posX = GetRand(Game::kScreenWidth);
			m_enemies.back().enemyPos = VGet(posX, 0.0f, 0.0f);
			m_enemies.back().enemyDir = VGet(0.0f, 1.0f, 0.0f);
			// 正規化
			if (VSize(m_enemies.back().enemyDir) > 0) m_enemies.back().enemyDir = VNorm(m_enemies.back().enemyDir);
			m_enemies.back().enemyDir = VScale(m_enemies.back().enemyDir, EnemyState::kMoveSpeed);
		}
	}

	for (auto& enemy : m_enemies)
	{
		enemy.enemyPos = VAdd(enemy.enemyPos, enemy.enemyDir);
	}

	// エネミー削除
	m_enemies.remove_if([](const Enemy& enemy)
		{
			if (enemy.enemyPos.y > kStageLimit || enemy.isDelete)
			{
				return true;
			}
			return false;
		});
}

void Scene2DGame::DrawEnemy()
{
	for (auto& enemy : m_enemies)
	{
		DrawRotaGraphF(enemy.enemyPos.x, enemy.enemyPos.y, 1.0, 0, m_hEnemyImg, true);
	}
}
