#include "SceneManager.h"
#include "Scene.h"
#include "SceneFade.h"
#include "SoundManager.h"

namespace
{
	//説明用処理バーの文字の座標
	constexpr int kUpdateBarStringPosX = 0;
	constexpr int kUpdateBarStringPosY = Game::kScreenHeight - 188;
	constexpr int kDrawBarPosStringPosX = 0;
	constexpr int kDrawBarPosStringPosY = Game::kScreenHeight - 172;

	//説明用処理バーの座標
	constexpr int kExplainUpdateBarPosX1 = 34;
	constexpr int kExplainUpdateBarPosY1 = Game::kScreenHeight - 186;
	constexpr int kExplainUpdateBarPosX2 = 62;
	constexpr int kExplainUpdateBarPosY2 = Game::kScreenHeight - 174;
	constexpr int kExplainDrawBarPosX1 = 34;
	constexpr int kExplainDrawBarPosY1 = Game::kScreenHeight - 170;
	constexpr int kExplainDrawBarPosX2 = 62;
	constexpr int kExplainDrawBarPosY2 = Game::kScreenHeight - 158;


	//処理バーの色
	constexpr int kUpdateBarColor = 0x0000ff;
	constexpr int kDrawBarColor = 0xff0000;

	//処理バーの座標
	constexpr int kBarPosX = 0;
	constexpr int kBarPosY = Game::kScreenHeight - 100;
}

void SceneManager::ChangeScene(Scene* scene)
{
	m_isAllUpdate = false;
	m_updateFunc = &SceneManager::FadeCloseUpdate;
	m_NextScene = scene;
	m_Fade = new SceneFade(*this);
}

void SceneManager::PushSceneAllUpdate(Scene* scene)
{
	m_Scene.push_front(scene);			//1個増える
	m_Scene.front()->Init();
	m_isAllUpdate = true;
}

void SceneManager::PushScene(Scene* scene)
{
	m_Scene.push_front(scene);			//1個増える
	m_Scene.front()->Init();
	m_isAllUpdate = false;
}

void SceneManager::PopScene()
{
	m_isAllUpdate = false;
	//ポップの結果、シーンが0にならないようにする
	if (m_Scene.size() > 1)
	{
		delete m_Scene.front();
		m_Scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	//更新前のローディング時間取得
	LONGLONG start = GetNowHiPerformanceCount();

	(this->*m_updateFunc)(input);

	//更新後のローディング時間から更新前のローディング時間を引いた値を取得
	m_updateTime = static_cast<float>(GetNowHiPerformanceCount() - start);
}

void SceneManager::Draw()
{
	//描画前のローディング時間取得
	LONGLONG start = GetNowHiPerformanceCount();

	for (int i = static_cast<int>(m_Scene.size() - 1); i >= 0; --i)
	{
		m_Scene[i]->Draw();
	}

	if (m_Fade != nullptr)
	{
		m_Fade->Draw();
	}

	//デバッグ時は更新、描画時の処理速度を測る
#ifdef _DEBUG
	m_drawTime = static_cast<float>(GetNowHiPerformanceCount() - start);

	//処理バーの表示　
	//説明
	DrawString(kUpdateBarStringPosX, kUpdateBarStringPosY, "処理", 0xffffff, 0x000000);
	DrawBox(kExplainUpdateBarPosX1, kExplainUpdateBarPosY1, kExplainUpdateBarPosX2, kExplainUpdateBarPosY2, kUpdateBarColor, true);
	DrawString(kDrawBarPosStringPosX, kDrawBarPosStringPosY, "描画", 0xffffff, 0x000000);
	DrawBox(kExplainDrawBarPosX1, kExplainDrawBarPosY1, kExplainDrawBarPosX2, kExplainDrawBarPosY2, kDrawBarColor, true);

	float rate = static_cast<float>(m_updateTime + m_drawTime) / 16666.6f;
	float width = static_cast<float>(Game::kScreenWidth * rate);
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kDrawBarColor, true);

	rate = static_cast<float>(m_updateTime) / 16666.6f;
	width = static_cast<float>(Game::kScreenWidth * rate);
	DrawBox(kBarPosX, kBarPosY, static_cast<int>(width), Game::kScreenHeight, kUpdateBarColor, true);
#endif
}

void SceneManager::GameEnd()
{
	ClearAllScene();

	m_isAllUpdate = false;
	m_isEnd = true;
}

void SceneManager::ClearAllScene()
{
	//シーンスタックが空ではなかったら...
	if (!m_Scene.empty())
	{
		// 現在実行中のシーンをすべて削除
		for (auto& scenes : m_Scene)
		{
			scenes->End();
			delete scenes;
		}
		m_Scene.clear();
	}
}

// シーンの通常更新処理
void SceneManager::SceneNormalUpdate(const InputState& input)
{
	if (m_isAllUpdate)
	{
		// 全ての更新処理を実行
		for (auto scene : m_Scene)
		{
			scene->Update(input);
		}
	}
	else 
	{
		// シーン配列の先頭だけ更新
		m_Scene.front()->Update(input);
	}
}

// シーン変更時の更新処理
void SceneManager::FadeOpenUpdate(const InputState& input)
{
	// フェードシーンの更新
	m_Fade->Update(input);

	if (m_Fade->IsFadeOpen())
	{
		m_updateFunc = &SceneManager::SceneNormalUpdate;
		delete m_Fade;
		m_Fade = nullptr;
	}	
}

void SceneManager::FadeCloseUpdate(const InputState& input)
{
	// フェードシーンの更新
	m_Fade->Update(input);

	if (m_Fade->IsFadeClose())
	{
		// フェード処理を開くほうに変更
		m_updateFunc = &SceneManager::FadeOpenUpdate;
		// 既存シーンを削除
		ClearAllScene();
		// 新しくシーン作成
		m_Scene.push_front(m_NextScene);
		// 新規シーンの初期化処理
		m_Scene.front()->Init();
		// 次のシーンとして保存していた中身を削除
		m_NextScene = nullptr;
	}
}
