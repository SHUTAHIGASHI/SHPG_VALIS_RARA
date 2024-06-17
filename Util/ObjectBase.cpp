#include "ObjectBase.h"

bool ObjectBase::CheckCollision(ObjectBase* obj)
{
	bool result = false;

	// 2つのオブジェクトの中心間のベクトル
	VECTOR n = VSub(m_status.pos, obj->GetPos());
	// 2つのオブジェクトの中心間の距離
	float tR = obj->m_status.radius + m_status.radius;
	// 2つのオブジェクトの中心間の距離が半径の和より小さい場合
	if (VSize(n) < tR)
	{
		// 衝突している
		result = true;
	}

	// 結果を返す
	return result;
}
