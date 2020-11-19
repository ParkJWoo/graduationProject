#include "stdafx.h"
#include "MpBarRight.h"
#include "UIObserver.h"

CMpBarRight::CMpBarRight()
{
}


CMpBarRight::~CMpBarRight()
{
	Release();
}

HRESULT CMpBarRight::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/MP/Half_Mp.png", L"MPBar", TEX_SINGLE)))
	{
		ERR_MSG(L"MP Bar Image Insert Failed!!!");
		return E_FAIL;
	}

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);

	return S_OK;
}

void CMpBarRight::LateInit()
{
}

int CMpBarRight::Update()
{
	CObj::LateInit();

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matParent = dynamic_cast<CUIObserver*>(m_pObserver)->GetMatrix();
	m_iMp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iMp;

	m_tInfo.matWorld = matTrans * matParent;

	if (m_iMp <= 1)
	{
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CMpBarRight::LateUpdate()
{
}

void CMpBarRight::Render()
{
	pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"MPBar");

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	/*m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - iCenterX);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + iCenterX);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - iCenterY);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + iCenterY);*/


	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMpBarRight::Release()
{
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
