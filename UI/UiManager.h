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
	// ステージクラスの設定
	void SetStage(class StageManager* stage) { m_pStage = stage; }

	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void End();

	// UIの追加
	void AddUIBar(class ObjectBase* obj);
	// UIの削除
	void DeleteUIBar(class ObjectBase* obj);
	// 全UIの削除
	void DeleteAllUI();

	// プレイヤー座標を設定
	void SetPlayerPos(const VECTOR pos) { m_playerPos = pos; }
	// ステージのポインタ削除
	void DeleteStage() { m_pStage = nullptr; }

private:
	// ラウンド状態の描画
	void DrawRoundState();

private:
	// プレイヤー座標
	VECTOR m_playerPos = Game::kVecZero;
	
	// 残弾数UI画像ハンドル
	int m_bulletUiHandle = -1;

private:
	// UIのリスト
	std::list<class UiBar*> m_pUiBarList;

	// ステージクラス
	class StageManager* m_pStage = nullptr;
};
