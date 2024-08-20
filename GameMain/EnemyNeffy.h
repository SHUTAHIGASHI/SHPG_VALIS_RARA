#pragma once
#include "EnemyBase.h"

class EnemyNeffy :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyNeffy(class ObjectBase*, VECTOR);
    // デストラクタ
    ~EnemyNeffy();

    // 更新
    void Update() override;

private:
    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (EnemyNeffy::*)();
    m_tUpdateFunc m_updateFunc = nullptr;
    void NormalUpdate();     // 通常の更新処理
    void AttackUpdate();     // 攻撃時の更新処理

private:
    // プレイヤー
    class ObjectBase* m_pTarget;
};

