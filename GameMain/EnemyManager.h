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

	// プレイヤーポインタ設定
	void SetPlayer(class Player* Player) { m_pPlayer = Player; }
	// ステージポインタ設定
	void SetStage(class Stage* Stage) { m_pStage = Stage; }

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// 難易度アップ
	void DiffcultyUp();

	// 敵生成完了判定
	bool IsEnemyCreateEnd() { return m_isEnemyCreateEnd; }

	// 敵取得
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// 敵生成
	void CreateEnemy();
	// 生成座標を取得
	VECTOR GetSpawnPos();
	// ランダムで敵種取得
	class EnemyBase* GetRandomEnemy();

private:
	// 生成した敵数
	int m_createEnemyCount;
	// 敵最大生成数
	int m_enemyMaxOnRound;
	// 敵最大同時生成数
	int m_enemyMaxOnScreen;
	// 敵の生成完了判定
	bool m_isEnemyCreateEnd;

	// 敵配列
	std::list<class EnemyBase*> m_pEnemies;
	// プレイヤーポインタ
	class Player* m_pPlayer;
	// ステージのポインタ
	class Stage* m_pStage;
};

