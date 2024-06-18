#include "ObjectBase.h"

bool ObjectBase::CheckCollision(ObjectBase* obj)
{
	// 2つのオブジェクトの中心間のベクトル
	VECTOR n = VSub(m_status.pos, obj->GetPos());
	// 2つのオブジェクトの中心間の距離
	float tR = obj->m_status.radius + m_status.radius;
	// 2つのオブジェクトの中心間の距離が半径の和より小さい場合
	if (VSize(n) < tR)
	{
		// 衝突している
		return true;
	}

	// 1つ前の座標取得
	VECTOR prevPos = VSub(m_status.pos, m_status.dir);
	auto prevN = VSub(m_status.pos, prevPos);
	auto tSize = VSize(prevN);
	while (tSize >= m_status.radius)
	{
		// 1つ前の座標から現在の座標までのベクトル
		auto prevDir = VSub(m_status.pos, prevPos);
		// ベクトルの正規化
		if (VSize(prevDir) > 0) prevDir = VNorm(prevDir);
		// ベクトルのスケーリング
		prevDir = VScale(prevDir, m_status.radius);
		// 2つのオブジェクトの中心間のベクトル
		VECTOR n = VSub(prevPos, obj->GetPos());
		// 2つのオブジェクトの中心間の距離が半径の和より小さい場合
		if (VSize(n) < tR)
		{
			// 衝突している
			return true;
		}

		prevPos = VAdd(prevPos, prevDir);
		prevN = VSub(m_status.pos, prevPos);
		tSize = VSize(prevN);
	}

	// 衝突していない
	return false;
}
