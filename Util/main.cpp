#include "Game.h"
#include "SoundManager.h"
#include "EffekseerManager.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneDebug.h"
#include "Load.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���O������
	SetOutApplicationLogValidFlag(false);
	// ���E�B���h�E��I�����Ă��Ă�����
	SetAlwaysRunFlag(false);
	// �E�B���h�E���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�B���h�E���[�h�̃T�C�Y�ύX
	SetWindowSizeChangeEnableFlag(true);
	// �E�B���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	//Effekseer�̏�����
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(Game::kParticleNum) == -1)
	{
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// �Q�[�����̃}�E�X�|�C���^�`��ݒ�
	//SetMouseDispFlag(false);
	// �}�E�X�J�[�\���ʒu�ݒ�
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// �}�e���A���ݒ�
	MATERIALPARAM Material;
	Material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);

	// ���\�[�X�̓ǂݍ���
	LPCSTR font = Game::kFontFileName;	// �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�ǂݍ��݃G���[����
		MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
	}
	// �W���t�H���g�ݒ�
	ChangeFont(Game::kFontName);
	SetFontSize(Game::kFontSize);

	// �T�E���h�}�l�[�W���[�錾
	auto& soundManager = SoundManager::GetInstance();
	// �G�t�F�N�V�A�}�l�[�W���[�錾
	auto& effekseerManager = EffekseerManager::GetInstance();
	// �L�[���͏�ԃN���X�錾
	InputState input;
	// �V�[���}�l�[�W���[�錾
	SceneManager scene;

	//���[�h
	Load::GetInstance().AllLoadData();
	// �J�[�\���摜�ǂݍ���
	int hCursorImg = Load::GetInstance().GetHandle("cursor");

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʂ̃N���A
		ClearDrawScreen();

		// �T�E���h�}�l�[�W���[�̍X�V
		soundManager.GetInstance().UpdateBGM();

		// ���͏�Ԃ̍X�V
		input.Update();

		// ���݂̃V�[���̍X�V
		scene.Update(input);

		// ���݂̃V�[���̕`��
		scene.Draw();

		// �}�E�X�J�[�\���`��
		//DrawRotaGraph(input.GetMousePosX(), input.GetMousePosY(), 1.0, 0.0, hCursorImg, true, false, true);

		// ����ʂ�\��ʂƓ���ւ���
		ScreenFlip();

		if (scene.IsGameEnd()) break;

#ifdef _DEBUG
		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif
		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	// �}�E�X�J�[�\���`��
	SetMouseDispFlag(true);

	// �J�[�\���摜�폜
	hCursorImg = -1;
	//�f�[�^�폜
	Load::GetInstance().DeleteAllData();
	// Effekseer�̏I������
	Effkseer_End();
	// DX���C�u�����g�p�̏I������
	DxLib_End();

	// �����̏I��
	return 0; 
}