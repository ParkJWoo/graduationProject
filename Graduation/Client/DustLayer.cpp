#include "stdafx.h"
#include "DustLayer.h"


CDustLayer::CDustLayer()
{
}

CDustLayer::~CDustLayer()
{
	Release();
}

HRESULT CDustLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Partical_Layer.png", L"Dust", TEX_SINGLE)))
	{
		ERR_MSG(L"Dust Layer Image Insert Failed!!!");
		return E_FAIL;
	}

	//m_tInfo.vPos = D3DXVECTOR3(500.f, 500.f, 0.f);

	return S_OK;
}

int CDustLayer::Update()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y - CScrollMgr::GetScroll().y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_tInfo.vPos += D3DXVECTOR3(0.004f, 0.004f, 0.f);

	return NO_EVENT;
}

void CDustLayer::LateUpdate()
{
}

void CDustLayer::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Dust");

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX - 100.f, (float)iCenterY - 100.f, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(100, 255, 255, 255));
}

void CDustLayer::Release()
{
}
