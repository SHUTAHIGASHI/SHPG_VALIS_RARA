#pragma once
#include "EnemyBase.h"

class EnemyNeffy :
    public EnemyBase
{
public:
    // コンストラクタ
    EnemyNeffy(class ObjectBase*, VECTOR, class Stage*);
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

    // 移動可能かの判定
    bool CheckCanMove(VECTOR nextPos);

private:
    // プレイヤー
    class ObjectBase* m_pTarget;
    // ステージクラス
	class Stage* m_pStage;
};

