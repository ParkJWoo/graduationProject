#include "stdafx.h"
#include "StreetLamp2.h"


CStreetLamp2::CStreetLamp2()
{
}


CStreetLamp2::~CStreetLamp2()
{
	Release();
}

HRESULT CStreetLamp2::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Stage2/StreetLamp3.png", L"StreetLamp2", TEX_SINGLE)))
	{
		ERR_MSG(L"Light Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CStreetLamp2::Update()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CStreetLamp2::LateUpdate()
{
}

void CStreetLamp2::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"StreetLamp2");

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY - 350.f, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CStreetLamp2::Release()
{
}
