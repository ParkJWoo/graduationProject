#include "stdafx.h"
#include "CutToon.h"

CCutToon::CCutToon()
	:fSpeed(0.f), fTime(0.f)
{
}

CCutToon::~CCutToon()
{
	Release();
}

HRESULT CCutToon::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroToon.png", L"Toon", TEX_SINGLE)))
	{
		ERR_MSG(L"Start Button Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = { -400.f,0.f,0.f };

	fSpeed = 0.04f;

	m_iDrawID = 0;

	return S_OK;
}

int CCutToon::Update()
{
	m_tInfo.vPos += D3DXVECTOR3(0.f, fSpeed, 0.f);

	/*if (m_tInfo.vPos.y >= 550.f)
	{
		fSpeed = 0.f;

		fTime += 0.05f;

		if (fTime >= 50.f)
		{
			m_iDrawID += 1;

			m_tInfo.vPos = D3DXVECTOR3(-400.f, 0.f, 0.f);

			fSpeed += 0.05f;

			fTime = 0.f;
		}
	}*/


	return 0;
}

void CCutToon::LateUpdate()
{
}

void CCutToon::Render()
{
	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Intro",L"Intro",m_iDrawID);

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Toon");

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)m_tInfo.vPos.x, (float)m_tInfo.vPos.y, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCutToon::Release()
{
}

