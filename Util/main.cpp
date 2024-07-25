#include "Game.h"
#include "SoundManager.h"
#include "EffekseerManager.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneDebug.h"
#include "Load.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ログ無効化
	SetOutApplicationLogValidFlag(false);
	// 他ウィンドウを選択していても動作
	SetAlwaysRunFlag(false);
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウモードのサイズ変更
	SetWindowSizeChangeEnableFlag(true);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	//Effekseerの初期化
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(Game::kParticleNum) == -1)
	{
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// ゲーム中のマウスポインタ描画設定
	//SetMouseDispFlag(false);
	// マウスカーソル位置設定
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// マテリアル設定
	MATERIALPARAM Material;
	Material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);

	// リソースの読み込み
	LPCSTR font = Game::kFontFileName;	// 読み込むフォントファイルのパス
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}
	// 標準フォント設定
	ChangeFont(Game::kFontName);
	SetFontSize(Game::kFontSize);

	// サウンドマネージャー宣言
	auto& soundManager = SoundManager::GetInstance();
	// エフェクシアマネージャー宣言
	auto& effekseerManager = EffekseerManager::GetInstance();
	// キー入力状態クラス宣言
	InputState input;
	// シーンマネージャー宣言
	SceneManager scene;

	//ロード
	Load::GetInstance().AllLoadData();
	// カーソル画像読み込み
	int hCursorImg = Load::GetInstance().GetHandle("cursor");

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面のクリア
		ClearDrawScreen();

		// サウンドマネージャーの更新
		soundManager.GetInstance().UpdateBGM();

		// 入力状態の更新
		input.Update();

		// 現在のシーンの更新
		scene.Update(input);

		// 現在のシーンの描画
		scene.Draw();

		// マウスカーソル描画
		//DrawRotaGraph(input.GetMousePosX(), input.GetMousePosY(), 1.0, 0.0, hCursorImg, true, false, true);

		// 裏画面を表画面と入れ替える
		ScreenFlip();

		if (scene.IsGameEnd()) break;

#ifdef _DEBUG
		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	// マウスカーソル描画
	SetMouseDispFlag(true);

	// カーソル画像削除
	hCursorImg = -1;
	//データ削除
	Load::GetInstance().DeleteAllData();
	// Effekseerの終了処理
	Effkseer_End();
	// DXライブラリ使用の終了処理
	DxLib_End();

	// 処理の終了
	return 0; 
}