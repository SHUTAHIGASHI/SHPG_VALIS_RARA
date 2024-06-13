#pragma once
#include "Scene.h"
#include "Game.h"
#include <string>
#include <vector>

class SelectMenuBase
{
public:
    // �R���X�g���N�^
    SelectMenuBase();
    // �f�X�g���N�^
    virtual ~SelectMenuBase();
    // ������
    void Init(bool isMouse);
    // �X�V����
    void Update(const InputState& input);
    // �`��
    void Draw();
    
    // �I�����ڒǉ�
    void AddSelectItem(std::string itemName);

    // �I�𒆂̍��ڒl�擾
    int GetSelectedNum() { return m_selectedPos; }

    // ���j���[���ڕ`��ʒu�ݒ�
    void SetDrawPos(float x, float y) { m_drawPos.x = x; m_drawPos.y = y; }
    void SetTitleDrawPos(float x, float y) { m_titleDrawPos.x = x; m_titleDrawPos.y = y; }
    // �����J���[�̐ݒ�
    void SetItemColor(int color) { m_itemColor = color; }
    void SetSelectedItemColor(int color) { m_selectedItemColor = color; }
    // �V�[��������̐ݒ�
    void SetTitleTextAndPos(std::string sceneText, float x, float y) 
    { m_sceneText = std::make_shared<std::string>(sceneText); m_titleDrawPos.x = x; m_titleDrawPos.y = y; }

private: // �v���C�x�[�g�֐�
    // ������̍X�V
    void DrawMenuText();
    // �V�[���^�C�g���`��
    void DrawSceneText();

    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (SelectMenuBase::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    // �J�[�\���X�V����
    void CursorUpdate(const InputState& input);
    // �ʏ�I���X�V����
    void NormalUpdate(const InputState& input);

private:
    struct SelectItemState
    {
        std::string itemName = "EMPTY";
    };

private: // �V�[�������̊Ǘ��ϐ�
    // �I�𒆂̍���
    int m_selectedPos;
    // ���ڐ�
    std::vector<SelectItemState> m_selectItems;
    // �^�C�g������
    std::shared_ptr<std::string> m_sceneText;

    // �J�[�\���ʒu
    MouseInputState m_mouseState;
    // �J�[�\�����g���ɂ��邩�ǂ���
    bool m_isCursorRanged;

    // ���ڕ`��ʒu
    VECTOR m_drawPos;
    // �V�[��������`��ʒu
    VECTOR m_titleDrawPos;
    // �I�����ڂ̃J���[
    int m_itemColor;
    int m_selectedItemColor;
    // ���t���[���J�E���g
	int m_countFrame;
};
