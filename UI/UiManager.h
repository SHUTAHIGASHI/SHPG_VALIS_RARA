#pragma once
#include "Game.h"
#include <list>
#include "StageManager.h"

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
	// 初期化
	void Init();
	// 更新
	void Update();
	// 描画
	void Draw();
	// 終了
	void End();

	// 敵のHPバー追加
	void AddEnemyHpBar(class ObjectBase* obj);
	// 敵のHPバー削除
	void DeleteEnemyHpBar(class ObjectBase* obj);

	// 全UIの削除
	void DeleteAllUI();

	// ラウンド状態のポインタ設定
	void SetRoundState(RoundState state) { m_roundState = state; }
	// ラウンドカウントの設定
	void SetRoundCount(int count) { m_roundCount = count; }

	// プレイヤーHPバーの設定
	void SetPlayerHPBar(class ObjectBase* obj);

	// プレイヤー座標を設定
	void SetPlayerPos(const VECTOR pos) { m_playerPos = pos; }

private:
	// ラウンド状態の描画
	void DrawRoundState();

private:
	// プレイヤー座標
	VECTOR m_playerPos = Game::kVecZero;
	
	// 武器UI画像ハンドル
	int m_weaponUiHandle = -1;
	// プレイヤーHPバーの画像ハンドル
	int m_playerHPBarHandle = -1;

private:
	// UIバーのリスト
	std::list<class UiBar*> m_pEnemyHpBar;

	// プレイヤーのHPバー
	class UiBar* m_pPlayerHpBar = nullptr;
	// ラウンド状態管理
	RoundState m_roundState;
	int m_roundCount = 0;
};
