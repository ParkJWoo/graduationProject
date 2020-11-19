#include "stdafx.h"
#include "BossFrontLayer.h"


CBossFrontLayer::CBossFrontLayer()
{
}


CBossFrontLayer::~CBossFrontLayer()
{
	Release();
}

HRESULT CBossFrontLayer::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Front/StreetLamp.png", L"StreetLamp", TEX_SINGLE)))
	{
		ERR_MSG(L"Light Image Insert Failed!!!");
		return E_FAIL;
	}

	//m_tInfo.vPos = { 0.f,500.f,0.f };

	return S_OK;
}

int CBossFrontLayer::Update()
{
	return NO_EVENT;
}

void CBossFrontLayer::LateUpdate()
{
}

void CBossFrontLayer::Render()
{
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"StreetLamp");

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX + 200.f, fCenterY - 500.f, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossFrontLayer::Release()
{
}
