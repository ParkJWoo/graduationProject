#include "stdafx.h"
#include "AfterLaily.h"

CAfterLaily::CAfterLaily()
{
}

CAfterLaily::~CAfterLaily()
{
	Release();
}

HRESULT CAfterLaily::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Laily%d.png",
		L"Dia_Laily", TEX_MULTI, L"Dia_Laily", 2)))
	{
		ERR_MSG(L"Laily Texture Load Failed!");
		return E_FAIL;
	}

	return S_OK;
}

int CAfterLaily::Update()
{
	return 0;
}

void CAfterLaily::LateUpdate()
{
}

void CAfterLaily::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Dia_Laily", L"Dia_Laily", 1);

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CAfterLaily::Release()
{
}
