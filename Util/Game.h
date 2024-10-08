#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "InputState.h"

namespace Game
{
	// システム基本設定 //
#ifdef _DEBUG
	// ウィンドウモード設定
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif
	// ウィンドウ名
	const char* const kTitleText = "りんごおぶラ王様 〜ララ様誕生日おめでとう〜";
	// ウィンドウサイズ
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// ゲームで使う色コード
	constexpr int kColorOrange = 0xff7800;
	constexpr int kColorRed = 0xdc143c;
	constexpr int kColorGreen = 0x6cc569;
	constexpr int kColorBlue = 0x5c6398;
	constexpr int kColorBlack = 0x140e0c;
	constexpr int kColorBlown = 0x231815;
	constexpr int kColorWhite = 0xffffff;
	constexpr int kColorGray = 0xa9a9a9;

	// ベクトル
	static VECTOR kVecZero = VGet(0.0f, 0.0f, 0.0f);
	static VECTOR kVecOne = VGet(1.0f, 1.0f, 1.0f);
	// 画面中心
	static VECTOR kScreenCenter = VGet(static_cast<float>(kScreenWidthHalf), static_cast<float>(kScreenHeightHalf), 0.0f);

	// ステージデータファイル
	const char* const kStageDataFileName = "Data/StageData.csv";

	/* フォント */
	// フォントファイル
	const char* const kFontFileName = "Data/fontData/FK-Kaisei-DecolStd-W7.otf";
	// フォント名
	const char* const kFontName = "FK-解星デコール W7";
	// フォントサイズ
	constexpr int kFontSize = 40;

	// カラーモード
	constexpr int kColorDepth = 32;
	
	// ゲームデータファイル
	const char* const kGameDataFileName = "Data/RaraGame_Setting.csv";

	// ゲームの基本設定 //
	// キャラクターの高さ
	constexpr float kCharaHeight = 156.0f;
	// チップサイズ
	constexpr float k2DChipSize = 64.0f;
	constexpr float k3DChipSize = 200.0f;
	// プレイヤーの基本設定
	constexpr float kBaseScale = 100.0f;
	// ステージ基本サイズ
	constexpr float kStageSizeX = 2000.0f;
	constexpr float kStageSizeY = 3000.0f;
	constexpr float kStageSizeZ = 2000.0f;
	// パーティクル用
	constexpr int kParticleNum = 8000;
}