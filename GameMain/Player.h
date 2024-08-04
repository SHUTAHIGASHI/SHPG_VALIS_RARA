#pragma once
#include "ObjectBase.h"
#include <list>

enum class PostureType
{
	stand,
	crouch,
	slide
};

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
	// カメラの設定
	void SetCamera(class CameraManager* pCamera) { m_pCamera = pCamera; }

	// 初期化
	void Init() override;
	// 更新
	void Update(const InputState& input) override;
	// ゲームオーバー時の更新
	void UpdateGameover();
	// 描画
	void Draw() override;

	// 被ダメージ処理
	void OnDamage(int damage);

private:
	// 視点の操作
	void ControllView(const InputState& input);
	// 視点の更新
	void UpdateView();

	// 移動処理
	void ControllMove(const InputState& input);
	// 姿勢の更新
	void UpdatePosture(const InputState& input);
	// スライディングの更新
	void UpdateSlide();
	// スライディング処理
	void OnSlide();

	// ショット管理
	void ControllShot(const InputState& input);
	// ショット生成
	void CreateShot();
	// スペシャルショット生成
	void CreateSprShot();
	// ショット更新
	void UpdateShot();
	// ショットヒット処理
	void OnHitShot(class Shot* pShot);

	// カーソル更新
	void UpdateCursor(const InputState& input);

	// 2D描画
	void Draw2D();

private:
	// プレイヤーの姿勢
	PostureType m_posture;

	// 画像ハンドル
	int m_hFpsHand;
	int m_hCursorImg;
	int m_hLockCursorImg;
	int m_hHitCursorImg;
	// 画像サイズ
	int m_HandSizeX;
	int m_HandSizeY;
	// 毎フレームカウント
	int m_frameCount;
	// 手の描画用フレーム
	int m_handFrame;
	// ショット連射速度
	int m_shotDelay;
	// スライディング時間
	int m_slideTime;
	// 無敵時間
	int m_invTime;
	// ヒットマーク描画フレーム
	int m_hitMarkFrame;

	// 移動判定
	bool m_isMove;
	// カーソルロック判定
	bool m_isLockOn;
	// 射撃中判定
	bool m_isShot;

	// 視線の高さ
	float m_eyeHeight;

	// 注視点の移動量
	float m_playerAngleY;
	float m_playerAngleX;

	// スライディングベクトル
	VECTOR m_slideVec;
	// ロックオンカーソル座標
	VECTOR m_lockObjPos;
	// 着弾地点
	VECTOR m_targetPos;

	// ショット配列
	std::list<class Shot*> m_pShots;	

private:// 各種ポインタ
	// ショットターゲットポインタ
	ObjectBase* m_pTargetObj;
	// エネミーマネージャーのポインタ
	class EnemyManager* m_pEnemyManager;
	// カメラのポインタ
	class CameraManager* m_pCamera;
};

