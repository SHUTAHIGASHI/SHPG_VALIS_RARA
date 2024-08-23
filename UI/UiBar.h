#pragma once

class UiBar
{
public:
    // �R���X�g���N�^
    UiBar(class ObjectBase* obj, bool is2D);
    // �f�X�g���N�^
    virtual ~UiBar();
    // ������
    void Init();
    // �X�V
    void Update();
    // �`��
    void Draw();

	// �摜�n���h���̐ݒ�
	void SetGaugeHandle(int handle) { m_gaugeHandle = handle; }

    // �`��ʒu�ݒ�
    void SetDrawPos(int x, int y);
	// �`��ʒu�̃��[�J�����W�ݒ�
	void SetDrawLocalPos(int x, int y);
    // �o�[�̃T�C�Y�ݒ�
	void SetGaugeSize(int w, int h);

    // �폜�t���O�ݒ�
    void SetDelete(bool flg) { m_isDelete = flg; }

    // �폜�t���O��Ԃ�
    bool IsDelete() const { return m_isDelete; }

    // �^�[�Q�b�g�I�u�W�F�N�g�擾
    class ObjectBase* GetObj() const { return m_targetObj; }

private:
    // �`����W
    int m_drawX, m_drawY;
	// ���[�J�����W
	int m_localX, m_localY;
	// �o�[�̃T�C�Y
	int m_gaugeW, m_gaugeH;

private:
    // �폜�t���O
    bool m_isDelete;
	// 2D�`�悩
	bool m_is2D;

    // ���l
    int* m_num;
    // ���l�̍ő�l
    int m_maxNum;
    // ���݂̗�
    float m_currentNumRate;
    float m_maxNumRate;
	// �o�[�̐F
	int m_color;

    // �摜�n���h��
	int m_gaugeHandle;

    // �^�[�Q�b�g�I�u�W�F�N�g
    class ObjectBase* m_targetObj;
};

