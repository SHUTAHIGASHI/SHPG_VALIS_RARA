#pragma once
#include <memory>

class StageManager
{
public:
	// コンストラクタ
	StageManager();
	// デストラクタ
	~StageManager();

	// プレイヤーポインタ設定
	void SetPlayer(class Player* Player) { m_pPlayer = Player; }

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();

	// 敵取得
	std::shared_ptr<class EnemyManager> GetEnemy() { return m_pEnemyManager; }

private:
	// ラウンド終了時の処理
	void OnRoundEnd();

	// メンバ関数ポインタ(ラウンド管理)
	using m_tUpdateFunc = void (StageManager::*) ();
	m_tUpdateFunc m_updateFunc = nullptr;
	void RoundOnUpdate();				// 通常の更新処理
	void RoundStartIntervalUpdate();	// ゲームスタート時の更新処理
	void RoundEndIntervalUpdate();		// ゲームオーバー時の更新処理

private:
	// ラウンド数カウント
	int m_roundCount;
	// ラウンドの遅延時間
	int m_roundInterval;

	// 敵管理
	std::shared_ptr<class EnemyManager> m_pEnemyManager;
	// プレイヤーポインタ
	class Player* m_pPlayer;
};

