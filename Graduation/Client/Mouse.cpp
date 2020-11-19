#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}

CMouse::~CMouse()
{
	Release();
}

D3DXVECTOR3 CMouse::GetMouse()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}

HRESULT CMouse::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Mouse/Cursor%d.png", L"Mouse",
		TEX_MULTI, L"Cursor", 3)))
	{
		ERR_MSG(L"Mouse Cursor Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CMouse::Update()
{
	return NO_EVENT;
}

void CMouse::LateUpdate()
{
	/*if (CKeyMgr::GetInstance()->KeyPress(KEY_RIGHT))
	{
		m_tInfo.vPos.x += 0.2f;
	}

	if (CKeyMgr::GetInstance()->KeyPress(KEY_LEFT))
	{
		m_tInfo.vPos.x -= 0.2f;
	}*/
}

void CMouse::Render()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rcWnd = {  };

	::GetClientRect(g_hWnd, &rcWnd);

	float fRatioX = WINCX / float(rcWnd.right - rcWnd.left);
	float fRatioY = WINCY / float(rcWnd.bottom - rcWnd.top);

	D3DXMATRIX matScale, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, fRatioX, fRatioY, 1.f);

	D3DXMatrixTranslation(&matTrans, pt.x - CScrollMgr::GetScroll().x, pt.y - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Mouse", L"Cursor", 0);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMouse::Release()
{
}

HRESULT CMouse::CursorChange(MOUSE_STANCE eCursor)
{
	m_eCursor = eCursor;

	switch (m_eCursor)
	{
	case CMouse::NORMAL:
		break;
	case CMouse::CLICK:
		break;
	case CMouse::ATTACK:
		break;
	case CMouse::MOUSE_END:
		break;
	default:
		break;
	}

	return E_NOTIMPL;
}
