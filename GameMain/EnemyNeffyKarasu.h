#pragma once
#include "EnemyBase.h"

class EnemyNeffyKarasu :
    public EnemyBase
{
public:
    // �R���X�g���N�^
    EnemyNeffyKarasu(class ObjectBase*, VECTOR);
    // �f�X�g���N�^
    ~EnemyNeffyKarasu();

    // �X�V
    void Update() override;

private:
	// �����o�֐��|�C���^(�X�V)
	using m_tUpdateFunc = void (EnemyNeffyKarasu::*)();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate();     // �ʏ�̍X�V����
	void AttackUpdate();     // �U�����̍X�V����

private:
    // �v���C���[
    class ObjectBase* m_pTarget;
};

