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
	const char* const kTitleText = "�����l�̂�� ���� ��񂲁`";
	// �E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 1600;
	constexpr int kScreenHeight = 900;
	constexpr int kScreenWidthHalf = kScreenWidth / 2;
	constexpr int kScreenHeightHalf = kScreenHeight / 2;
	constexpr int kScreenWidthTriple = kScreenWidth * 3;
	constexpr int kScreenHeightTriple = kScreenHeight * 3;

	// �Q�[���Ŏg���F�R�[�h
	constexpr int kColorOrange = 0xff7800;
	constexpr int kColorRed = 0xdc143c;
	constexpr int kColorGreen = 0xadff2f;
	constexpr int kColorBlue = 0x4f7fee;
	constexpr int kColorBlack = 0x0a192c;
	constexpr int kColorWhite = 0xffffff;
	constexpr int kColorGray = 0xa9a9a9;

	// �O�̃x�N�g��
	static VECTOR kVecZero = VGet(0.0f, 0.0f, 0.0f);

	// �X�e�[�W�f�[�^�t�@�C��
	const char* const kStageDataFileName = "Data/StageData.csv";

	/* �t�H���g */
	// �t�H���g�t�@�C��
	const char* const kFontFileName = "Data/fontData/851Gkktt_005.ttf";
	// �t�H���g�T�C�Y
	constexpr int kFontSize = 40;

	// �J���[���[�h
	constexpr int kColorDepth = 32;
	
	// �Q�[���̊�{�ݒ� //
	constexpr int kBoostLevelMax = 3;
	// �v���C���[�̊�{�ݒ�
	constexpr float kChipSize = 32.0f;

	// ��{�ړ����x
	constexpr float kMoveSpeed = 12.0f;

	// �Q�[���̃X�e�[�W�T�C�Y
	constexpr int kStageWidth = 1400;
	constexpr int kStageHeight = 700;

	// �p�[�e�B�N���p
	constexpr int kParticleNum = 8000;
}