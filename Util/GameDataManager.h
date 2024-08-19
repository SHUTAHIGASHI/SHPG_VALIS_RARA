#pragma once

/// <summary>
/// ゲームデータの管理を行うシングルトンクラス
/// </summary>
class GameDataManager
{
public:
	~GameDataManager();
	/// <summary>
	/// GameDataManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static GameDataManager& GetInstance()
	{
		// 唯一の実態
		static GameDataManager instance;
		// それの参照を返す
		return instance;
	}

	// マウス感度の取得
	float GetMouseSensitivity() const { return m_mouseSensitivity; }
	// マウス感度の設定
	void SetMouseSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }

private:
	// 変更したサウンド情報をファイルに書き込む
	struct GameConfigInfo
	{
		char signature[5];			// "SET_"
		float version;				// 1.0
		float mouseSensitivity;		// マウス感度
	};

	// シングルトンパターンなのでコンストラクタはprivateに置く
	GameDataManager();
	// コピーも代入も禁止する
	GameDataManager(const GameDataManager&) = delete;		// コピーコンストラクタ
	void operator = (const GameDataManager&) = delete;		// 代入も禁止

	// ゲームデータ保存
	void SaveCharacterData();
	// ゲームデータ読み込み
	void LoadCharacterData();

private:
	// マウス感度
	float m_mouseSensitivity;
};