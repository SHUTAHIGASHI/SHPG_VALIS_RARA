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
    void Init();
    // 更新処理
    void Update(const InputState& input);
    // 描画処理
    void Draw();
    // 終了
    void End();

private:

    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate(const InputState& input);     // 通常の更新処理
    void StartUpdate(const InputState& input);      // ゲームスタート時の更新処理
    void EndUpdate(const InputState& input);        // ゲームオーバー時の更新処理

    // メンバ関数ポインタ(描画)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void NormalDraw();      // 通常の描画処理
    void StartDraw();       // シーン開始時の描画処理
    void EndDraw();         // シーン終了時の描画処理

private:
    std::shared_ptr<class CameraController> m_pCamera;     // カメラ
	std::shared_ptr<class Player> m_pPlayer;               // プレイヤー
};

