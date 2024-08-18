#pragma once
#include <unordered_map>
#include <string>
#include <DxLib.h>

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

	// キャラクターデータの一時保存
	void SaveTempData(struct charaState data);
	// キャラクターデータの取得
	void SetData(struct charaState& data);

private:
	// キャラクターデータの保存
	void SaveCharacterData();
	// キャラクターデータの読み込み
	void LoadCharacterData();

	// シングルトンパターンなのでコンストラクタはprivateに置く
	GameDataManager();
	// コピーも代入も禁止する
	GameDataManager(const GameDataManager&) = delete;		// コピーコンストラクタ
	void operator = (const GameDataManager&) = delete;		// 代入も禁止

private:
};