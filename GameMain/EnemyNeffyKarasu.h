#pragma once
#include "EnemyBase.h"

class EnemyNeffyKarasu :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyNeffyKarasu(class ObjectBase*, VECTOR);
    // デストラクタ
    ~EnemyNeffyKarasu();

    // 更新
    void Update() override;

private:
	// メンバ関数ポインタ(更新)
	using m_tUpdateFunc = void (EnemyNeffyKarasu::*)();
	m_tUpdateFunc m_updateFunc = nullptr;
	void NormalUpdate();     // 通常の更新処理
	void AttackUpdate();     // 攻撃時の更新処理

private:
    // プレイヤー
    class ObjectBase* m_pTarget;
};

