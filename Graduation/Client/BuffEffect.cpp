#include "stdafx.h"
#include "BuffEffect.h"
#include "EffectIMP.h"

CBuffEffect::CBuffEffect()
	: m_pTarget(nullptr), m_fRevAngle(0.f)
{
}


CBuffEffect::~CBuffEffect()
{
	Release();
}

HRESULT CBuffEffect::Initialize()
{
	// �θ�κ��� 300��ŭ ������ �д�.
	m_tInfo.vPos = { 300.f, 0.f, 0.f };

	return CEffect::Initialize();
}

void CBuffEffect::LateInit()
{
	CEffect::LateInit();
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();
}

int CBuffEffect::Update()
{
	CObj::LateInit();

	D3DXMATRIX matScale, matRot, matTrans, matRev;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fRevAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	D3DXMatrixRotationZ(&matRev, D3DXToRadian(-m_fRevAngle));

	// �����ϰ� ���� ���� ����.
	m_fRevAngle += 200.f * CTimeMgr::GetInstance()->GetTime();

	// �� * �� * �� * �� * ��
	m_tInfo.matWorld = matScale * matRot * matTrans * matRev * m_pTarget->GetInfo().matWorld;

	return m_pBridge->Update();
}

void CBuffEffect::LateUpdate()
{
	CEffect::LateUpdate();
}

void CBuffEffect::Render()
{
	CEffect::Render();
}

void CBuffEffect::Release()
{
}
