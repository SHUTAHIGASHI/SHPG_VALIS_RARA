#include "Model.h"

Model::Model(int handle):
	m_hModel(handle),
	m_AnimNo(-1),
	m_AnimIndex(0),
	m_AnimTotalTime(0.0f),
	m_AnimPlayTime(0.0f),
	m_localPos(Game::kVecZero),
	m_pos(Game::kVecZero),
	m_rotation(Game::kVecZero)
{
}

Model::~Model()
{
	// ���f���n���h���폜
	MV1DeleteModel(m_hModel);
}

void Model::Update()
{
	// �Đ����Ԃ�i�߂�
	m_AnimPlayTime += 1.0f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (m_AnimPlayTime > m_AnimTotalTime)
	{
		m_AnimPlayTime = 0.0f;
	}

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(m_hModel, m_AnimIndex, m_AnimPlayTime);
}

void Model::Draw()
{
	// ���f���̍��W��ݒ�
	MV1SetPosition(m_hModel, VAdd(m_pos, m_localPos));
	// ���f���`��
	MV1DrawModel(m_hModel);
}

void Model::SetModelLocalPos(VECTOR pos)
{
	// ���f���̃��[�J�����W��ݒ�
	m_localPos = pos;
}

void Model::SetPosition(VECTOR pos)
{
	// ���W�ݒ�
	m_pos = pos;
	MV1SetPosition(m_hModel, VAdd(m_pos, m_localPos));
}

void Model::SetScale(float size)
{
	// �g�嗦�ݒ�
	MV1SetScale(m_hModel, VGet(size, size, size));
	m_localPos = VScale(m_localPos, size);
}

void Model::SetMotionType(int motionType)
{
	// ���s���郂�[�V�����ݒ�
	if (m_AnimNo == motionType) return;
	m_AnimNo = motionType;
	m_AnimIndex = MV1AttachAnim(m_hModel, motionType, -1);
	m_AnimTotalTime = MV1GetAttachAnimTotalTime(m_hModel, m_AnimIndex);
	m_AnimPlayTime = 0.0f;
}

void Model::SetDirectionAxisY(VECTOR lookPos, float rota)
{
	// �����ݒ�
	lookPos.y -= 500.0f;
	MV1SetRotationZYAxis(m_hModel, VGet(0.0f, 0.0f, 1.0f), VSub(m_pos, lookPos), rota);
}

void Model::SetDirectionAxisZ(VECTOR lookPos, float rota)
{
	// �㉺�͌Œ�
	lookPos.y = m_pos.y;
	// �����ݒ�
	MV1SetRotationZYAxis(m_hModel, VSub(m_pos, lookPos), VGet(0.0f, 1.0f, 0.0f), rota);
}

void Model::SetRotation(VECTOR rota)
{
	// ��]�����ݒ�
	m_rotation = rota;
	MV1SetRotationXYZ(m_hModel, m_rotation);
}

void Model::SetOutline(int materialIndex, float width, float r, float g, float b, float a)
{
	// 3D�I�u�W�F�N�g�̃A�E�g���C����`��
	MV1SetMaterialOutLineWidth(m_hModel, materialIndex, width);
	MV1SetMaterialOutLineColor(m_hModel, materialIndex, GetColorF(r, g, b, a));
}
