#pragma once
#include "Scene.h"
#include <memory>
#include <string>

class SceneResult :
    public Scene
{
public:
    // コンストラクタ
    SceneResult(SceneManager& manager);
    // デストラクタ
    virtual ~SceneResult();

    // 初期化
    void Init(){}
    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();
    // 終了
    void End() {}

private:
    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneResult::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void StartUpdate(const InputState& input);      // 開始時の更新処理
    void NormalUpdate(const InputState& input);     // 通常の更新処理
    void EndUpdate(const InputState& input);        // 終了時の更新処理

private: // 変数
    // 背景画像
    int m_hBgImg;
    // スコア描画用座標
    float m_scorePosY;
    // 選択メニュー
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};

