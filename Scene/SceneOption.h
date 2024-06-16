#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>

enum class volume
{
    SE,
    BGM
};

class SceneOption :
    public Scene
{
public:
    SceneOption(SceneManager& manager);
    virtual ~SceneOption();

    // 初期化
    void Init() override;
    // 更新
    void Update(const InputState& input) override;
    // 描画
    void Draw() override;
    // 終了
    void End() override {}

private: // プライベート関数
    // 音量の設定
    void ChangeVolume(const InputState& input);
    // 音量の操作
    void ControllVolume(const InputState& input, int& volume);
    // 変更した音量情報を反映させる
    void SetVolumeInfo();
    // 変更前の音量情報を反映させる
    void ResetVolumeInfo();
    // テキスト描画位置
    void DrawSoundBar(float drawX, float drawY, int volume);
    // テキスト情報の描画
    void DrawMenuText();
    // 項目選択時
    void CursorUpdate(const InputState& input);
    // 選択時の処理
    void OnSelect();

    // 選択中の文字列を返す
    std::string GetCurrentText(int textNum);
private:
    // 毎フレームカウント
    int m_countFrame;
    // 前の音量
    int m_exVolumeBGM;
    int m_exVolumeSE;
    // 音量
    int m_volumeBGM;
    int m_volumeSE;
    // 選択位置
    int m_selectedPos;
	// 選択項目
    std::string m_selectedItemName;
    // 画像
    int m_hBgImg;
    int m_hMusicVolImg;
    // カーソルが枠内にあるかどうか
    bool m_isCursorRanged;
    // 音量調整モード
    bool m_isVolumeChangeMode;
	// 保存したウィンドウモード
    bool m_isSavedWindowMode;
};
