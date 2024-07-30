#pragma once
#include "Game.h"
#include <list>

class UiManager
{
public:
	~UiManager();
	/// <summary>
	/// UiManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static UiManager& GetInstance()
	{
		// 唯一の実態
		static UiManager instance;

		// それの参照を返す
		return instance;
	}
private:
	// シングルトンパターンなのでコンストラクタはprivateに置く
	UiManager()
	{
	}
	// コピーも代入も禁止する
	UiManager(const UiManager&) = delete;			// コピーコンストラクタ
	void operator = (const UiManager&) = delete;	// 代入も禁止

public:
	// 更新
	void Update();
	// 描画
	void Draw();

	// UIの追加
	void AddUI(class ObjectBase* obj);
	// UIの削除
	void DeleteUI(class ObjectBase* obj);
	// 全UIの削除
	void DeleteAllUI();

	// プレイヤー座標を設定
	void SetPlayerPos(const VECTOR pos) { m_playerPos = pos; }

private:
	// プレイヤー座標
	VECTOR m_playerPos;

private:
	// UIのリスト
	std::list<class UiBar*> m_pUIList;
};
