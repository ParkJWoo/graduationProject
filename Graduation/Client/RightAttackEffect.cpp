#include "stdafx.h"
#include "RightAttackEffect.h"
#include "Player.h"

CRightAttackEffect::CRightAttackEffect()
	:m_pPlayer(nullptr), m_fTime(0.f)
{
}


CRightAttackEffect::~CRightAttackEffect()
{
	Release();
}

HRESULT CRightAttackEffect::Initialize()
{
	m_wstrObjKey = L"AttackEffect";

	m_wstrStateKey = L"Right";

	m_tInfo.vSize = { 50.f,50.f,0.f };

	CTimeMgr::GetInstance()->InitTime();

	return S_OK;
}

int CRightAttackEffect::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	D3DXMatrixIdentity(&matPos);

	m_tInfo.matWorld = matScale * matTrans * matPos;

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 4.f;

	m_fTime += CTimeMgr::GetInstance()->GetTime();

	return NO_EVENT;
}

void CRightAttackEffect::LateUpdate()
{
}

void CRightAttackEffect::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	if (CSceneMgr::GetInstance()->GetID() == CSceneMgr::STAGE1_1)
		m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), &D3DXVECTOR3(0.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CRightAttackEffect::Release()
{
}
