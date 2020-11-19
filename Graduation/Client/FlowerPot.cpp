#include "stdafx.h"
#include "FlowerPot.h"


CFlowerPot::CFlowerPot()
{
}


CFlowerPot::~CFlowerPot()
{
	Release();
}

HRESULT CFlowerPot::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Stage2/FlowerPot.png", L"FlowerPot", TEX_SINGLE)))
	{
		ERR_MSG(L"Light Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CFlowerPot::Update()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CFlowerPot::LateUpdate()
{
}

void CFlowerPot::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"FlowerPot");

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY - 350.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(155, 255, 255, 255));
}

void CFlowerPot::Release()
{
}
