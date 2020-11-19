#include "stdafx.h"
#include "Dia_MatikaLayer.h"


CDia_MatikaLayer::CDia_MatikaLayer()
{
}


CDia_MatikaLayer::~CDia_MatikaLayer()
{
	Release();
}

HRESULT CDia_MatikaLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Matika_Layer.png", L"Matika", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Matika Image Insert Failed!!!");
		return E_FAIL;
	}


	return S_OK;
}

int CDia_MatikaLayer::Update()
{
	return 0;
}

void CDia_MatikaLayer::LateUpdate()
{
}

void CDia_MatikaLayer::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Matika");

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

void CDia_MatikaLayer::Release()
{
}
