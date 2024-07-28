#pragma once
#include "Scene.h"
#include "Game.h"
#include <vector>

class SceneFade :
    public Scene
{
public:
    // コンストラクタ
    SceneFade(SceneManager& manager);
    // デストラクタ
    virtual ~SceneFade();

    // 初期化
    void Init() {}
    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();
    // 終了
    void End() {}

    // フェード処理の判定を返す //
    bool IsFadeClose() { return m_isFadeClose; } // 閉じ切ったかどうか
    bool IsFadeOpen() { return m_isFadeOpen; }  // 開き切ったかどうか

private:
    //メンバ関数ポインタ
    using m_tUpdateFunc = void (SceneFade::*) ();
    m_tUpdateFunc m_updateFunc = nullptr;
    void CloseUpdate();  // シーン開始時の描画処理
    void OpenUpdate();    // シーン終了時の描画処理

private:
    // フェード処理が完了したかどうか
    bool m_isFadeClose;
    bool m_isFadeOpen;
    // フェード画像
    int m_hFadeImg;
    // グラフサイズ
    int m_graphSizeX;
    int m_graphSizeY;
    // 拡大率
    double m_imgScale;
};

