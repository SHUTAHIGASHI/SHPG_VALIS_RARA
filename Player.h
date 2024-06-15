#pragma once
#include "ObjectBase.h"
#include <list>

class Player :
	public ObjectBase
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	virtual ~Player();

	// エネミーマネージャーの設定
	void SetEnemyManager(class EnemyManager* pEnemyManager) { m_pEnemyManager = pEnemyManager; }

	// 初期化
	void Init() override;
	// 更新
	void Update(const InputState& input) override;
	// 描画
	void Draw() override;

private:
	// ショット生成
	void CreateShot();
	// ショット更新
	void UpdateShot();
	// カーソル更新
	void UpdateCursor(const InputState& input);
	// 2D描画
	void Draw2D();

private:
	// 画像ハンドル
	int m_hCursorImg;
	int m_hLockCursorImg;
	// カーソルロック判定
	bool m_isLockOn;
	// カーソル座標
	VECTOR m_cursorPos;
	// ロックオンカーソル座標
	VECTOR m_lockObjPos;
	// ショット配列
	std::list<class Shot*> m_pShots;
	

private:// 各種ポインタ
	// ショットターゲットポインタ
	ObjectBase* m_pTargetObj;
	// エネミーマネージャーのポインタ
	class EnemyManager* m_pEnemyManager;
};

