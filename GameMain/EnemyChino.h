#pragma once
#include "EnemyBase.h"
class EnemyChino :
    public EnemyBase
{
public:
    // �R���X�g���N�^
    EnemyChino(VECTOR);
    // �f�X�g���N�^
    ~EnemyChino();

    // �X�V
    void Update() override;
private:
};

