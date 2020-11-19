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

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX - 100.f, (float)iCenterY - 100.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(100, 255, 255, 255));
}

void CDustLayer::Release()
{
}
