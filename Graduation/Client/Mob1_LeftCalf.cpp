#include "stdafx.h"
#include "Mob1_LeftCalf.h"

#include "Mob1_LeftLeg.h"


CMob1_LeftCalf::CMob1_LeftCalf()
	:pTexInfo(nullptr)
{
}


CMob1_LeftCalf::~CMob1_LeftCalf()
{
	Release();
}

HRESULT CMob1_LeftCalf::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/ENEMY/Stage1_Boss/Left_calf/Left_Calf.png", L"Stage1_Boss_LeftCalf", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage1_Boss_LeftCalf Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = D3DXVECTOR3(188.f, 255.f, 0.f);

	return S_OK;
}

int CMob1_LeftCalf::Update()
{
	CObj* pBody = new CMob1_LeftLeg;

	D3DXMATRIX matScale, matTrans, matParent;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matParent = dynamic_cast<CObj*>(pBody)->GetInfo().matWorld;

	m_tInfo.matWorld = matScale * matTrans * matParent;

	return NO_EVENT;
}

void CMob1_LeftCalf::LateUpdate()
{
}

void CMob1_LeftCalf::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pImageKey);

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		&D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f) /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMob1_LeftCalf::Release()
{
}
