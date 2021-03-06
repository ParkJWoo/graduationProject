#include "stdafx.h"
#include "BackLight.h"


CBackLight::CBackLight()
{
}


CBackLight::~CBackLight()
{
	Release();
}

HRESULT CBackLight::Initialize()
{

	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Light/Light.png", L"Light",
		TEX_SINGLE, L"Prop", 2)))
	{
		ERR_MSG(L"Second Layer Props Insert Failed!!!");
		return E_FAIL;
	}*/

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Light/Light.png", L"Light", TEX_SINGLE)))
	{
		ERR_MSG(L"Light Image Insert Failed!!!");
		return E_FAIL;
	}

	return S_OK;
}

int CBackLight::Update()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CBackLight::LateUpdate()
{

}

void CBackLight::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Light");

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX + 760.f, (float)iCenterY + 250.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(85, 255, 255, 255));
}

void CBackLight::Release()
{
}
