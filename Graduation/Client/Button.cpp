#include "stdafx.h"
#include "Button.h"


CButton::CButton()
	:fAlphaCnt(255.f)
{
}

CButton::~CButton()
{
	Release();
}

HRESULT CButton::Initialize()
{
	return S_OK;
}

int CButton::Update()
{
	return NO_EVENT;
}

void CButton::LateUpdate()
{
	POINT pt = {};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// PtInRect: 마우스 좌표가 임의의 렉트 범위 안에 놓여있으면 TRUE를 반환.
	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::GetInstance()->KeyDown(KEY_LBUTTON))
		{

			if (!lstrcmp(L"Start", m_pImageKey))
			{
				fAlphaCnt = 0.f;
				m_bIsClick = true;
			}

			else if (!lstrcmp(L"Stop", m_pImageKey))
			{
				m_bOnButton = true;
				DestroyWindow(g_hWnd);
			}


			return;
		}
	}
}

void CButton::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pImageKey);

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


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
		D3DCOLOR_ARGB((int)fAlphaCnt, 255, 255, 255));
}

void CButton::Release()
{
}