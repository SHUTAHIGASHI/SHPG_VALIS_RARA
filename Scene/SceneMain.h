#pragma once
#include "Scene.h"
#include <memory>

class SceneMain :
    public Scene
{
public:
    // コンストラクタ
    SceneMain(SceneManager& manager);
    // デストラクタ
    virtual ~SceneMain();

    // シーン初期化
    void Init()override;
    // 更新処理
    void Update(const InputState& input)override;
    // 描画処理
    void Draw()override;
    // 終了
    void End()override;

private:
    // ゲームオーバー処理
    void OnGameOver();

    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);     // 通常の更新処理
    void StartUpdate(const InputState& input);      // ゲームスタート時の更新処理
    void EndUpdate(const InputState& input);        // ゲームオーバー時の更新処理

private:
    std::shared_ptr<class CameraManager> m_pCamera; // カメラ
	std::shared_ptr<class Player> m_pPlayer;        // プレイヤー 
	std::shared_ptr<class StageManager> m_pStage;   // 敵管理
	std::shared_ptr<class SkyDome> m_pSkyDome;      // スカイドーム
};

