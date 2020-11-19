#include "stdafx.h"
#include "Dia_IronWindow.h"


CDia_IronWindow::CDia_IronWindow()
{
}


CDia_IronWindow::~CDia_IronWindow()
{
	Release();
}

HRESULT CDia_IronWindow::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Iron_Layer.png", L"IronWindow", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Iron Window Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CDia_IronWindow::Update()
{
	return 0;
}

void CDia_IronWindow::LateUpdate()
{
}

void CDia_IronWindow::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"IronWindow");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// 이미지의 중점 구하기.
	/*int iCenterX2 = pTexInfo->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo->tImgInfo.Height / 2;*/

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)900.f, (float)550.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDia_IronWindow::Release()
{
}