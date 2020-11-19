#include "stdafx.h"
#include "NonAnimEffect.h"
#include "Obj.h"

CNonAnimEffect::CNonAnimEffect()
	: m_fLifeTime(0.f), m_fTime(0.f)
{
}


CNonAnimEffect::~CNonAnimEffect()
{
	Release();
}

HRESULT CNonAnimEffect::Initialize()
{
	return S_OK;
}

void CNonAnimEffect::LateInit()
{
}

int CNonAnimEffect::Update()
{
	CEffectIMP::LateInit();

	m_fTime += CTimeMgr::GetInstance()->GetTime() * 10;

	if (m_fLifeTime < m_fTime)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CNonAnimEffect::LateUpdate()
{
}

void CNonAnimEffect::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_pObj->GetObjKey().c_str(), m_wstrStateKey.c_str(), 3);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CNonAnimEffect::Release()
{
}
