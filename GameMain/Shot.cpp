#include "Shot.h"
#include "Load.h"

using namespace ShotParam;

Shot::Shot(VECTOR pos, VECTOR target):
	ObjectBase(),
	m_shotTime(),
	m_targetObject(nullptr)
{
	// ショットの初期化
	Init(pos);
	m_status.dir = VSub(target, m_status.pos);
	if (VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
	m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
}

Shot::Shot(VECTOR pos, ObjectBase* targetObj):
	ObjectBase(),
	m_shotTime(),
	m_targetObject(targetObj)
{
	// ショットの初期化
	Init(pos);
	// ショット追尾先更新
	UpdateShotAndTarget();
}

Shot::~Shot()
{
	// 画像削除
	m_status.hImg = -1;
}

void Shot::Update()
{
	// ショットの更新
	UpdateShotAndTarget();

	// 弾の有効時間
	m_shotTime--;
	if (m_shotTime <= 0)
	{
		// 有効時間が終了したら削除
		m_status.isEnabled = false;
	}
}

void Shot::Draw()
{
	// 画像描画
	DrawBillboard3D(m_status.pos, 0.5f, 0.5f, m_status.scale, 0.0f, m_status.hImg, true);
}

void Shot::OnHit()
{
	// 当たった時の処理
	m_status.isEnabled = false;
}

void Shot::SetScale(float scale)
{
	// 弾の拡大率を変更
	if (scale > 0)
	{
		m_status.radius = kShotRadius * scale;
	}
	else
	{
		m_status.radius = kShotRadius;
	}
}

void Shot::Init(VECTOR pos)
{
	// 画像読み込み
	m_status.hImg = Load::GetInstance().GetHandle("shot");
	// ショットの初期化
	m_status.moveSpeed = kShotSpeed;
	m_status.radius = kShotRadius;
	m_status.scale = Game::kBaseScale;
	// 有効時間
	m_shotTime = kShotTime;
	// ショットの位置と方向
	m_status.pos = pos;
}

void Shot::UpdateShotAndTarget()
{
	// ショット追尾先更新
	if (m_targetObject != nullptr)
	{
		if (m_targetObject->IsEnabled())
		{
			m_status.dir = VSub(m_targetObject->GetPos(), m_status.pos);
			if(VSize(m_status.dir) > 0) m_status.dir = VNorm(m_status.dir);
			m_status.dir = VScale(m_status.dir, m_status.moveSpeed);
		}
	}
	
	// 弾の移動
	m_status.pos = VAdd(m_status.pos, m_status.dir);
}
