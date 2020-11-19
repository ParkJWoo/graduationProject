#include "stdafx.h"
#include "AnimEffect.h"
#include "Obj.h"


CAnimEffect::CAnimEffect()
{
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CAnimEffect::~CAnimEffect()
{
	Release();
}

HRESULT CAnimEffect::Initialize()
{
	return S_OK;
}

void CAnimEffect::LateInit()
{
}

int CAnimEffect::Update()
{
	CEffectIMP::LateInit();

	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();
	
	// 애니메이션 이펙트는 애니메이션 재생이 끝나면 소멸.
	if (m_tFrame.fFrame > m_tFrame.fMax)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CAnimEffect::LateUpdate()
{
}

void CAnimEffect::Render()
{
	// 기존의 씬 렌더링을 마치고
	CDevice::GetInstance()->Render_End();

	// 새론운 씬 렌더링 시작.
	CDevice::GetInstance()->Render_Begin();
	
	// 알파 블렌딩

	// D3DBLENDOP_ADD: 덧셈 방식의 혼합을 사용한다. 결과 = 전송원(SRC) + 목적지(DST)
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	// D3DRS_SRCBLEND: 덮힐 이미지 (전송원), D3DBLEND_ONE: (전송원) *= 1
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);

	// D3DRS_SRCBLEND: 깔린 이미지 (목적지), D3DBLEND_ONE: (목적지) *= 1
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 최종 결과: 전송원(SRC) * 1 + 목적지(DST) * 1


	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_pObj->GetObjKey().c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo().matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->Render_Begin();
}

void CAnimEffect::Release()
{
}
