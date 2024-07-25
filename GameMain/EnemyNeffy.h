#pragma once
#include "EnemyBase.h"

class EnemyNeffy :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyNeffy(VECTOR);
    // デストラクタ
    ~EnemyNeffy();

    // 更新
    void Update() override;
private:
};

