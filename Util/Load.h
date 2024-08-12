#pragma once
#include <unordered_map>
#include <string>

class Load
{
public:
	~Load();
	/// <summary>
	/// Load使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static Load& GetInstance()
	{
		// 唯一の実態
		static Load instance;

		// それの参照を返す
		return instance;
	}

	/// <summary>
	/// 全てのデータをロードする
	/// </summary>
	void AllLoadData();

	/// <summary>
	/// 全てのデータを削除する
	/// </summary>
	void DeleteAllData();

	/// <summary>
	/// ハンドルを取得する
	/// </summary>
	/// <param name="key">ロードデータのキー</param>
	/// <returns>ハンドル</returns>
	int GetImageHandle(std::string key)
	{
		return m_imageData[key];
	}

	/// <summary>
	/// 3Dモデルのハンドルを取得する
	/// </summary>
	/// <param name="key">ロードデータのキー</param>
	/// <returns>ハンドル</returns>
	int GetModelHandle(std::string key)
	{
		return m_modelData[key];
	}
private:
	//ロードデータをunordered_mapで管理
	std::unordered_map<std::string, int> m_imageData;
	std::unordered_map<std::string, int> m_modelData;

	// シングルトンパターンなのでコンストラクタはprivateに置く
	Load() {};

	// コピーも代入も禁止する
	Load(const Load&) = delete;			// コピーコンストラクタ
	void operator = (const Load&) = delete;		// 代入も禁止
};

