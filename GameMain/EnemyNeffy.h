#pragma once
#include "EnemyBase.h"

class EnemyNeffy :
    public EnemyBase
{
public:
    // �R���X�g���N�^
    EnemyNeffy(class ObjectBase*, VECTOR);
    // �f�X�g���N�^
    ~EnemyNeffy();

    // �X�V
    void Update() override;

private:
    // �����o�֐��|�C���^(�X�V)
    using m_tUpdateFunc = void (EnemyNeffy::*)();
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate();     // �ʏ�̍X�V����
    void AttackUpdate();     // �U�����̍X�V����

private:
    // �v���C���[
    class ObjectBase* m_pTarget;
};

