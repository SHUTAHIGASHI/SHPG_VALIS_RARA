#pragma once
#include "EnemyBase.h"

class EnemyChaseNeffy :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyChaseNeffy(class ObjectBase*, VECTOR);
    // デストラクタ
    ~EnemyChaseNeffy();

    // 更新
    void Update() override;
private:
    // プレイヤー
    class ObjectBase* m_pTarget;
};

