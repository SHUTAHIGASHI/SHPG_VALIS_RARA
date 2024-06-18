#pragma once
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "InputState.h"

namespace Game
{
	// �V�X�e����{�ݒ� //
#ifdef _DEBUG
	// �E�B���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
#else
	constexpr bool kWindowMode = false;
#endif
	// �E�B���h�E��
	const char* const kTitleText = "��񂲂��ԃ����l �`�����l�a�������߂łƂ��`";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// �Q�[���Ŏg���F�R�[�h
	constexpr int kColorOrange = 0xff7800;
	constexpr int kColorRed = 0xdc143c;
	constexpr int kColorGreen = 0x6cc569;
	constexpr int kColorBlue = 0x5c6398;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorBlown = 0x231815;
	constexpr int kColorWhite = 0xffffff;
	constexpr int kColorGray = 0xa9a9a9;

	// �O�̃x�N�g��
	static VECTOR kVecZero = VGet(0.0f, 0.0f, 0.0f);

	// �X�e�[�W�f�[�^�t�@�C��
	const char* const kStageDataFileName = "Data/StageData.csv";

	/* �t�H���g */
	// �t�H���g�t�@�C��
	const char* const kFontFileName = "Data/fontData/FK-Kaisei-DecolStd-W7.otf";
	// �t�H���g��
	const char* const kFontName = "FK-�𐯃f�R�[�� W7";
	// �t�H���g�T�C�Y
	constexpr int kFontSize = 40;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// �Q�[���̊�{�ݒ� //
	// �v���C���[�̊�{�ݒ�
	constexpr float kBaseScale = 100.0f;
	// �X�e�[�W��{�T�C�Y
	constexpr float kStageSizeX = 1000.0f;
	constexpr float kStageSizeY = 500.0f;
	constexpr float kStageSizeZ = 2000.0f;
	// �p�[�e�B�N���p
	constexpr int kParticleNum = 8000;
}