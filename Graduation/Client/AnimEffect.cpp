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
	
	// �ִϸ��̼� ����Ʈ�� �ִϸ��̼� ����� ������ �Ҹ�.
	if (m_tFrame.fFrame > m_tFrame.fMax)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CAnimEffect::LateUpdate()
{
}

void CAnimEffect::Render()
{
	// ������ �� �������� ��ġ��
	CDevice::GetInstance()->Render_End();

	// ���п� �� ������ ����.
	CDevice::GetInstance()->Render_Begin();
	
	// ���� ����

	// D3DBLENDOP_ADD: ���� ����� ȥ���� ����Ѵ�. ��� = ���ۿ�(SRC) + ������(DST)
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	// D3DRS_SRCBLEND: ���� �̹��� (���ۿ�), D3DBLEND_ONE: (���ۿ�) *= 1
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);

	// D3DRS_SRCBLEND: �� �̹��� (������), D3DBLEND_ONE: (������) *= 1
	CDevice::GetInstance()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���� ���: ���ۿ�(SRC) * 1 + ������(DST) * 1


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
