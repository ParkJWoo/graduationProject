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
	CDataSubject::GetInstance()->Subscribe(m_pObserver);	// ������ ���.

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

	// PtInRect: ���콺 ��ǥ�� ������ ��Ʈ ���� �ȿ� ���������� TRUE�� ��ȯ.
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

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

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
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CInvenIcon::Release()
{
	//SafeDelete(m_pObserver);
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
