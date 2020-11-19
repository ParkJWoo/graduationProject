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

	// PtInRect: ���콺 ��ǥ�� ������ ��Ʈ ���� �ȿ� ���������� TRUE�� ��ȯ.
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

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);


	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)m_tInfo.vPos.x - iCenterX;
	m_tRect.right = (LONG)m_tInfo.vPos.x + iCenterX;
	m_tRect.top = (LONG)m_tInfo.vPos.y - iCenterY;
	m_tRect.bottom = (LONG)m_tInfo.vPos.y + iCenterY;


	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB((int)fAlphaCnt, 255, 255, 255));
}

void CButton::Release()
{
}