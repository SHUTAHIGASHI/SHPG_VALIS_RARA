#pragma once

class UiBar
{
public:
    // �R���X�g���N�^
    UiBar(class ObjectBase* obj);
    // �f�X�g���N�^
    virtual ~UiBar();
    // ������
    void Init();
    // �X�V
    void Update();
    // �`��
    void Draw();

    // �`��ʒu�ݒ�
    void SetDrawPos(int x, int y);

    // �폜�t���O�ݒ�
    void SetDelete(bool flg) { m_isDelete = flg; }

    // �폜�t���O��Ԃ�
    bool IsDelete() const { return m_isDelete; }

    // �^�[�Q�b�g�I�u�W�F�N�g�擾
    class ObjectBase* GetObj() const { return m_targetObj; }

private:
    // �`����W
    int m_drawX, m_drawY;

private:
    // �폜�t���O
    bool m_isDelete;

    // ���l
    int* m_num;
    // ���l�̍ő�l
    int m_maxNum;
    // ���݂̗�
    float m_currentNumRate;
    float m_maxNumRate;
	// �o�[�̐F
	int m_color;

    // �^�[�Q�b�g�I�u�W�F�N�g
    class ObjectBase* m_targetObj;
};

