#pragma once
#include "EnemyBase.h"

class EnemyNeffy :
    public EnemyBase
{
public:
    // �R���X�g���N�^
    EnemyNeffy(VECTOR);
    // �f�X�g���N�^
    ~EnemyNeffy();

    // �X�V
    void Update() override;
private:
};

