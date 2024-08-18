#pragma once
#include "Scene.h"
#include "Game.h"
#include <list>

struct Shot
{
	// ショット画像
	int shotHandle = -1;
	// ショット座標
	VECTOR shotPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR shotDir = VGet(0.0f, 0.0f, 0.0f);
	// ショット速度
	float shotSpeed = 32.0f;
};

struct Enemy
{
	// エネミー画像
	int enemyHandle = -1;
	// エネミー座標
	VECTOR enemyPos = VGet(0.0f, 0.0f, 0.0f);
	VECTOR enemyDir = VGet(0.0f, 1.0f, 0.0f);
	// エネミー速度
	float enemySpeed = 12.0f;
	// 削除判定
	bool isDelete = false;
};

class Scene2DGame :
    public Scene
{
public:
    // コンストラクタ
    Scene2DGame(SceneManager& manager);
    // デストラクタ
    virtual ~Scene2DGame();

	// 初期化
	void Init() override;
	// 更新
	void Update(const InputState& input) override;
	// 描画
	void Draw() override;
	// 終了
	void End() override;

private: // プレイヤー関数
	// プレイヤー更新
	void UpdatePlayer(const InputState& input);
	// プレイヤー描画
	void DrawPlayer();

private: // ショット関数
	// ショット更新
	void UpdateShot();
	// ショット描画
	void DrawShot();

private: // エネミー関数
	// エネミー更新
	void UpdateEnemy();
	// エネミー描画
	void DrawEnemy();

private: // プレイヤー変数
	// プレイヤー画像
	int m_hPlayerImg;
	// プレイヤー座標
	VECTOR m_playerPos;

private: // ショット変数
	// ショット構造体配列
	std::list<Shot> m_shots;
	// ショット画像
	int m_hShotImg;
	// ショット遅延
	int m_shotDelay;

private: // エネミー変数
	// エネミー構造体配列
	std::list<Enemy> m_enemies;
	// エネミー画像
	int m_hEnemyImg;
	// 生成カウント
	int m_enemyCount;

private: // その他変数
	// 背景画像
	int m_hBackImg;
	// カーソル画像
	int m_hCursorImg;
	// カーソル座標
	VECTOR m_cursorPos;
};

