#include "stdafx.h"
#include "FrontCage.h"


CFrontCage::CFrontCage()
{
}


CFrontCage::~CFrontCage()
{
	Release();
}

HRESULT CFrontCage::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Cage/Front_Cage.png", L"FrontCage", TEX_SINGLE)))
	{
		ERR_MSG(L"Cage Image Insert Failed!!!");
		return E_FAIL;
	}

	/*m_tInfo.vPos = { 0.f,450.f,0.f };*/

	return S_OK;
}

int CFrontCage::Update()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return NO_EVENT;
}

void CFrontCage::LateUpdate()
{
}

void CFrontCage::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"FrontCage");

	//D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScrollMgr::GetScroll().x, m_tInfo.vPos.y - CScrollMgr::GetScroll().y, 0.f);

	//matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CFrontCage::Release()
{
}
