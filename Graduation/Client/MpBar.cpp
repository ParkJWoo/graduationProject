#include "stdafx.h"
#include "MpBar.h"
#include "UIObserver.h"


CMpBar::CMpBar()
{
}


CMpBar::~CMpBar()
{
	Release();
}

HRESULT CMpBar::Initialize()
{
	//m_tInfo.vPos = { 0.f, -100.f, 0.f };

	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/MP/Mp_Case.png", L"MPCase", TEX_SINGLE)))
	{
		ERR_MSG(L"MP Case Image Insert Failed!!!");
		return E_FAIL;
	}*/

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/MP/Half_Mp.png", L"MPBar", TEX_SINGLE)))
	{
		ERR_MSG(L"MP Bar Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/MP/Mp_Case.png", L"MPCase", TEX_SINGLE)))
	{
		ERR_MSG(L"MP Case Image Insert Failed!!!");
		return E_FAIL;
	}

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);

	return S_OK;
}

void CMpBar::LateInit()
{
}

int CMpBar::Update()
{
	CObj::LateInit();

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matParent = dynamic_cast<CUIObserver*>(m_pObserver)->GetMatrix();
	m_iMp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iMp;

	m_tInfo.matWorld = matTrans * matParent;

	m_iMp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iMp;

	if (m_iMp < 0)
	{
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CMpBar::LateUpdate()
{
	/*if (CKeyMgr::GetInstance()->KeyPress(KEY_RIGHT))
	{
		m_tInfo.vPos.x += 0.1f;
	}

	if (CKeyMgr::GetInstance()->KeyPress(KEY_LEFT))
	{
		m_tInfo.vPos.x -= 0.2f;
	}*/
}

void CMpBar::Render()
{
	pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pImageKey);

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	/*m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - iCenterX);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + iCenterX);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - iCenterY);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + iCenterY);*/


	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMpBar::Release()
{
	//SafeDelete(m_pObserver);
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}