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

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// 敵取得
	std::list<class EnemyBase*> GetEnemies() { return m_pEnemies; }

private:
	// ラウンド終了時の処理
	void OnRoundEnd();
	// 敵生成
	void CreateEnemy();
	// 生成座標ランダム取得
	VECTOR GetRandomPos();
	// ランダムで敵種取得
	class EnemyBase* GetRandomEnemy();

	// メンバ関数ポインタ(ラウンド管理)
	using m_tUpdateFunc = void (EnemyManager::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void RoundOnUpdate();     // 通常の更新処理
	void RoundStartIntervalUpdate();      // ゲームスタート時の更新処理
	void RoundEndIntervalUpdate();        // ゲームオーバー時の更新処理

private:
	// ラウンド数カウント
	int m_roundCount;

	// 敵配列
	std::list<class EnemyBase*> m_pEnemies;
	// プレイヤーポインタ
	class Player* m_pPlayer;
};

