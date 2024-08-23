#pragma once

class UiBar
{
public:
    // コンストラクタ
    UiBar(class ObjectBase* obj, bool is2D);
    // デストラクタ
    virtual ~UiBar();
    // 初期化
    void Init();
    // 更新
    void Update();
    // 描画
    void Draw();

	// 画像ハンドルの設定
	void SetGaugeHandle(int handle) { m_gaugeHandle = handle; }

    // 描画位置設定
    void SetDrawPos(int x, int y);
	// 描画位置のローカル座標設定
	void SetDrawLocalPos(int x, int y);
    // バーのサイズ設定
	void SetGaugeSize(int w, int h);

    // 削除フラグ設定
    void SetDelete(bool flg) { m_isDelete = flg; }

    // 削除フラグを返す
    bool IsDelete() const { return m_isDelete; }

    // ターゲットオブジェクト取得
    class ObjectBase* GetObj() const { return m_targetObj; }

private:
    // 描画座標
    int m_drawX, m_drawY;
	// ローカル座標
	int m_localX, m_localY;
	// バーのサイズ
	int m_gaugeW, m_gaugeH;

private:
    // 削除フラグ
    bool m_isDelete;
	// 2D描画か
	bool m_is2D;

    // 数値
    int* m_num;
    // 数値の最大値
    int m_maxNum;
    // 現在の率
    float m_currentNumRate;
    float m_maxNumRate;
	// バーの色
	int m_color;

    // 画像ハンドル
	int m_gaugeHandle;

    // ターゲットオブジェクト
    class ObjectBase* m_targetObj;
};

