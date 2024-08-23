#pragma once
#include "Scene.h"
#include <string>
#include <memory>
#include "Game.h"

class SceneTitleMenu :
    public Scene
{
public:
    // コンストラクタ
    SceneTitleMenu(SceneManager& manager);
    // デストラクタ
    virtual ~SceneTitleMenu();
    // 初期化
    void Init();
    // 更新
    void Update(const InputState& input);
    // 描画
    void Draw();
    // 終了
    void End();

private: // プライベート関数
    // データ読み込み
    void LoadData();
    // タイトル終了時処理
    void OnSceneEnd();
    // キャラクター更新
    void UpdateChara();
    // 曲名ループ処理
    void MusicNameLoop();

    using m_tUpdateFunc = void (SceneTitleMenu::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // タイトル画面更新処理
    void NormalUpdate(const InputState& input);

private: // シーン全体の管理変数
    // 毎フレームカウント用
    int m_countFrame;

private: // シーン装飾の管理変数
    // 画像ハンドル
    int m_hTitleLogoImg;
    // 背景画像ハンドル
	int m_hBackGroundImg;
    // キャラハンドル
    int m_hCharaImg;
    // キャラクター座標
    VECTOR m_charaPos;
    VECTOR m_charaDir;
    // 曲名表示位置
    VECTOR m_musicNameDrawPos;

private:
    // セレクトメニューの管理変数
    std::shared_ptr<class SelectMenuBase> m_pSelectMenu;
};

