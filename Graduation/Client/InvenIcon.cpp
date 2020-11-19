#include "stdafx.h"
#include "InvenIcon.h"
#include "UIObserver.h"

CInvenIcon::CInvenIcon()
{
}

CInvenIcon::~CInvenIcon()
{
	Release();
}

HRESULT CInvenIcon::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Inventory_UI/Inventory_UI.png", L"InvenIcon", TEX_SINGLE)))
	{
		ERR_MSG(L"Inventory Icon Image Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = { 870.f, 60.f, 0.f };

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);	// 관찰자 등록.

	return S_OK;
}

void CInvenIcon::LateInit()
{
}

int CInvenIcon::Update()
{
	CObj::LateInit();

	D3DXMATRIX matScale, matTrans, matParent, matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	D3DXMatrixIdentity(&matPos);

	matParent = dynamic_cast<CUIObserver*>(m_pObserver)->GetMatrix();

	matPos._41 = matParent._41;

	m_tInfo.matWorld = matScale * matTrans * matPos;

	return NO_EVENT;
}

void CInvenIcon::LateUpdate()
{
	POINT pt = {};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// PtInRect: 마우스 좌표가 임의의 렉트 범위 안에 놓여있으면 TRUE를 반환.
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON))
		{
			DestroyWindow(g_hWnd);
		}
	}
}

void CInvenIcon::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"InvenIcon");

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)m_tInfo.vPos.x - iCenterX;
	m_tRect.right = (LONG)m_tInfo.vPos.x + iCenterX;
	m_tRect.top = (LONG)m_tInfo.vPos.y - iCenterY;
	m_tRect.bottom = (LONG)m_tInfo.vPos.y + iCenterY;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CInvenIcon::Release()
{
	//SafeDelete(m_pObserver);
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
