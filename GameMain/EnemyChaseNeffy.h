#pragma once
#include "EnemyBase.h"

class EnemyChaseNeffy :
    public EnemyBase
{
public:
    // �R���X�g���N�^
    EnemyChaseNeffy(class ObjectBase*, VECTOR);
    // �f�X�g���N�^
    ~EnemyChaseNeffy();

    // �X�V
    void Update() override;
private:
    // �v���C���[
    class ObjectBase* m_pTarget;
};

