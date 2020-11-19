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

void CMpBarRight::Release()
{
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
