#pragma once
#include "ObjectBase.h"
#include <list>

enum class PostureType
{
	stand,
	crouch,
	slide
};

enum class HandState
{
	Normal,
	Shot,
	Grenade,
};

class Player :
	public ObjectBase
{
public:
	// コンストラクタ
	Player();
	// デストラクタ
	virtual ~Player();

	// ステージ管理クラスの設定
	void SetStage(class Stage* pStage) { m_pStage = pStage; }
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
	// ステージ範囲判定
	void CheckStageRange();

	// 視点の操作
	void ControllView(const InputState& input);
	// 視点の更新
	void UpdateView();

	// ギミック操作処理
	void ControllGimmick(const InputState& input);
	// 移動処理
	void ControllMove(const InputState& input);
	// 地面の判定
	void CheckGround();
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
	// 体力の更新	
	void UpdateHp();
	// 手の状態の更新
	void UpdateHandState();

	// 2D描画
	void Draw2D();

	// 移動可能かの判定
	bool CheckCanMove(VECTOR nextPos);

private:
	// プレイヤーの姿勢
	PostureType m_posture;
	// プレイヤーの手の状態
	HandState m_handState;

	// 画像ハンドル
	int m_hFpsHand;
	int m_hCursorImg;
	int m_hHitCursorImg;
	// 画像サイズ
	int m_HandSizeX;
	int m_HandSizeY;
	// 毎フレームカウント
	int m_frameCount;
	// 手の描画用フレーム
	int m_handFrame;
	int m_handFrameMax;
	// ショット用フレーム
	int m_shotFrame;
	// スライディング時間
	int m_slideTime;
	// 無敵時間
	int m_invTime;
	// 体力回復時間
	int m_recoveryTime;
	// ヒットマーク描画フレーム
	int m_hitMarkFrame;
	// ステージタイル番号
	int m_tileX;
	int m_tileZ;

	// 移動判定
	bool m_isMove;
	// ダッシュ判定
	bool m_isDash;
	// カーソルロック判定
	bool m_isLockOn;
	// 射撃中判定
	bool m_isShot;
	// インタラクト可能か
	bool m_isInteract;

	// マウス感度
	float m_mouseSensitivity;

	// 視線の高さ
	float m_eyeHeight;

	// 注視点の移動量
	float m_playerAngleY;
	float m_playerAngleX;

	// スライディングベクトル
	VECTOR m_slideVec;
	// 着弾地点
	VECTOR m_targetPos;

	// ショット配列
	std::list<class Shot*> m_pShots;	
private:// 各種ポインタ
	// ショットターゲットポインタ
	ObjectBase* m_pTargetObj;
	// ステージのポインタ
	class Stage* m_pStage;
	// エネミーマネージャーのポインタ
	class EnemyManager* m_pEnemyManager;
	// カメラのポインタ
	class CameraManager* m_pCamera;
};

