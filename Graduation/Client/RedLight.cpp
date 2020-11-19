#include "stdafx.h"
#include "RedLight.h"


CRedLight::CRedLight()
{
}


CRedLight::~CRedLight()
{
	Release();
}

HRESULT CRedLight::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/RedLight2.png", L"RedLight", TEX_SINGLE)))
	{
		ERR_MSG(L"Light Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CRedLight::Update()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CRedLight::LateUpdate()
{
}

void CRedLight::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"RedLight");

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX - 65.f, (float)iCenterY - 300.f, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(200, 255, 255, 255));
}

void CRedLight::Release()
{
}
