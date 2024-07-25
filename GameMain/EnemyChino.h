#pragma once
#include "EnemyBase.h"
class EnemyChino :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyChino(VECTOR);
    // デストラクタ
    ~EnemyChino();

    // 更新
    void Update() override;
private:
};

