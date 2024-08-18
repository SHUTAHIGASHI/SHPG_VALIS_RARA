#include "Scene2DGame.h"
#include "SceneManager.h"
#include "ScenePauseMenu.h"
#include "SceneTitleMenu.h"
#include "Load.h"
#include "SoundManager.h"
#include <string>

namespace
{
	// �`�b�v�T�C�Y
	constexpr float kChipSize = 48.0f;
	// �����蔻�蔼�a
	constexpr float kHitRadius = 32.0f;
	// �X�e�[�W���E
	constexpr float kStageLimit = Game::kScreenHeight - 150.0f;
	// �Q�[���J�E���g
	constexpr int kGameCount = 60 * 30;
}

namespace PlayerState
{
	// �ړ����x
	constexpr float kMoveSpeed = 6.0f;
	// �V���b�g�x��
	constexpr int kShotDelay = 16;
	// �g�嗦
	constexpr float kScale = 2.0f;
}

namespace EnemyState
{
	// �ړ����x
	constexpr float kMoveSpeed = 2.0f;
	// �o���Ԋu
	constexpr int kAppearInterval = 120;
	// �o����
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

	// �J�[�\���폜
	SetMouseDispFlag(false);
}

Scene2DGame::~Scene2DGame()
{
	DeleteGraph(m_hPlayerImg);
	DeleteGraph(m_hEnemyImg);
	DeleteGraph(m_hBackImg);
	m_hShotImg = -1;
	m_hCursorImg = -1;
	// �J�[�\���폜
	SetMouseDispFlag(true);
}

void Scene2DGame::Init()
{
	// �v���C���[���W������
	m_playerPos = VGet(Game::kScreenWidthHalf, kStageLimit, 0.0f);
	// �V���b�g������
	m_shots.clear();
	// �G�l�~�[������
	m_enemies.clear();
	// �J�[�\�����W
	m_cursorPos = VGet(0.0f, 0.0f, 0.0f);
	// �J�[�\���폜
	SetMouseDispFlag(false);
	// �V���b�g�x��
	m_shotDelay = 0;
	// �G�l�~�[�o���J�E���g
	m_enemyCount = 0;
	// �Q�[���J�E���g
	m_gameCount = kGameCount;
}

void Scene2DGame::Update(const InputState& input)
{
	// �Q�[���J�E���g
	m_gameCount--;
	if (m_gameCount <= 0)
	{
		m_isGameEnd = true;
	}

	// �|�[�Y���j���[
	if (input.IsTriggered(InputType::pause))
	{
		m_Manager.PushScene(new ScenePauseMenu(m_Manager));
		return;
	}

	// �J�[�\�����W
	m_cursorPos.x = input.GetMousePosX();
	m_cursorPos.y = input.GetMousePosY();

	if (!m_isGameEnd)
	{
		// �v���C���[�X�V
		UpdatePlayer(input);
		// �V���b�g�X�V
		UpdateShot();
		// �G�l�~�[�X�V
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
	// �w�i�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_hBackImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �v���C���[�`��
	DrawPlayer();
	// �V���b�g�`��
	DrawShot();
	// �G�l�~�[�`��
	DrawEnemy();

	// �X�e�[�W���E�`��
	DrawLine(0, kStageLimit, Game::kScreenWidth, kStageLimit, 0xffffff);

	if (m_isGameEnd)
	{
		DrawRotaGraphF(Game::kScreenWidthHalf, Game::kScreenHeightHalf, 1.0, 0, m_hBoardImg, true);
		// �Q�[���J�E���g�`��
		std::string drawText = "�|�����l�t�B����:" + std::to_string(m_killCount);
		auto textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf - 60.0f, 0xffffff, "%s", drawText.c_str());
		drawText = "�^�C�g���֖߂�܂�";
		textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), Game::kScreenHeightHalf + 30.0f, 0xffffff, "%s", drawText.c_str());
		return;
	}
	else
	{
		// �Q�[���J�E���g�`��
		std::string drawText = std::to_string(m_gameCount / 60);
		SetFontSize(60);
		auto textLength = GetDrawFormatStringWidth(drawText.c_str());
		DrawFormatString(Game::kScreenWidthHalf - (textLength / 2), kStageLimit + 40, 0xffffff, "%s", drawText.c_str());
		SetFontSize(Game::kFontSize);
	}

	// �J�[�\���`��
	DrawRotaGraphF(m_cursorPos.x, m_cursorPos.y, 1.0, 0, m_hCursorImg, true);
}

void Scene2DGame::End()
{
}

void Scene2DGame::UpdatePlayer(const InputState& input)
{
	// �V���b�g�x��
	if (m_shotDelay > 0) m_shotDelay--;

	if (input.IsPressed(InputType::left))
	{
		m_playerPos.x -= PlayerState::kMoveSpeed;
	}
	if (input.IsPressed(InputType::right))
	{
		m_playerPos.x += PlayerState::kMoveSpeed;
	}

	// ��ʊO����
	if (m_playerPos.x < 0) m_playerPos.x = 0;
	if (m_playerPos.x > Game::kScreenWidth) m_playerPos.x = Game::kScreenWidth;
	if (m_playerPos.y < 0) m_playerPos.y = 0;
	if (m_playerPos.y > Game::kScreenHeight) m_playerPos.y = Game::kScreenHeight;

	// �V���b�g����
	if (input.IsPressed(InputType::shot))
	{
		if (m_shotDelay > 0) return;

		m_shotDelay = PlayerState::kShotDelay;
		m_shots.push_back(Shot());
		m_shots.back().shotPos = m_playerPos;
		m_shots.back().shotDir = VSub(m_cursorPos, m_playerPos);
		// ���K��
		if (VSize(m_shots.back().shotDir) > 0) m_shots.back().shotDir = VNorm(m_shots.back().shotDir);
		m_shots.back().shotDir = VScale(m_shots.back().shotDir, m_shots.back().shotSpeed);
		// �V���b�g�T�E���h
		SoundManager::GetInstance().PlaySE(SoundType::shot);
	}
}

void Scene2DGame::DrawPlayer()
{
	DrawRotaGraphF(m_playerPos.x, m_playerPos.y, PlayerState::kScale, 0, m_hPlayerImg, true);
}

void Scene2DGame::UpdateShot()
{
	// �V���b�g�X�V
	for (auto& shot : m_shots)
	{
		shot.shotPos = VAdd(shot.shotPos, shot.shotDir);
	}

	// �V���b�g�����蔻��
	m_shots.remove_if([this](const Shot& shot)
	{
		for (auto& enemy : m_enemies)
		{
			if (VSize(VSub(enemy.enemyPos, shot.shotPos)) < kHitRadius)
			{
				// �G�l�~�[�폜
				enemy.isDelete = true;
				// �L���J�E���g
				m_killCount++;
				// �G�l�~�[�T�E���h
				SoundManager::GetInstance().PlaySE(SoundType::enemyDamage);
				return true;
			}
		}
		return false;
	});

	// ��ʊO����
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
			// �����_���Ȑ������W
			float posX = GetRand(Game::kScreenWidth);
			m_enemies.back().enemyPos = VGet(posX, 0.0f, 0.0f);
			m_enemies.back().enemyDir = VGet(0.0f, 1.0f, 0.0f);
			// ���K��
			if (VSize(m_enemies.back().enemyDir) > 0) m_enemies.back().enemyDir = VNorm(m_enemies.back().enemyDir);
			m_enemies.back().enemyDir = VScale(m_enemies.back().enemyDir, EnemyState::kMoveSpeed);
		}
	}

	for (auto& enemy : m_enemies)
	{
		enemy.enemyPos = VAdd(enemy.enemyPos, enemy.enemyDir);
	}

	// �G�l�~�[�폜
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
