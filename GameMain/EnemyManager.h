#pragma once
#include <list>
#include <DxLib.h>

/// <summary>
/// ステージの敵管理クラス
/// </summary>
class EnemyManager
{
public:
	// コンストラクタ
	EnemyManager();
	// デストラクタ
	~EnemyManager();

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// 敵取得
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// 敵生成
	void CreateEnemy();
	// 生成座標ランダム取得
	VECTOR GetRandomPos();
	// ランダムで敵種取得
	class EnemyBase* GetRandomEnemy();

private:
	// 敵配列
	std::list<class EnemyBase*> m_pEnemies;
};

