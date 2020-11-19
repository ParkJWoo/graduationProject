#include "stdafx.h"
#include "Dia_LeoLayer.h"


CDia_LeoLayer::CDia_LeoLayer()
{
}


CDia_LeoLayer::~CDia_LeoLayer()
{
	Release();
}

HRESULT CDia_LeoLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Leo_Layer.png", L"Leo", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Leo Image Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = D3DXVECTOR3(790.f, 500.f, 0.f);

	m_iAppCnt = 0;

	return S_OK;
}

int CDia_LeoLayer::Update()
{
	//while (m_iAppCnt <= 255)
	//{
	//	if (m_iAppCnt >= 255)
	//		break;

	//	m_iAppCnt += 250;
	//}

	//if (CKeyMgr::GetInstance()->KeyDown(KEY_UP))
	//{
	//	m_iAppCnt = 1;

	//	m_tInfo.vPos.x += 100.f;
	/////*	if (m_iAppCnt >= 255)
	////	{
	////		m_iAppCnt = 255;
	////	}*/

	////	//m_iAppCnt += 100;


	////	while (m_iAppCnt <= 255)
	////	{
	////		m_iAppCnt += 100;

	////		if (m_iAppCnt >= 256)
	////			break;
	////	}

	//}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_UP))
	{
		m_iAppCnt = 1;

	}

	return NO_EVENT;
}

void CDia_LeoLayer::LateUpdate()
{
}

void CDia_LeoLayer::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Leo");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	if (m_iAppCnt == 1)
		//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr /*����� �̹��� ������ RECT*/,
			&D3DXVECTOR3((float)iCenterX - 100.f, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
			nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
			D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDia_LeoLayer::Release()
{
}