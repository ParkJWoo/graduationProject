#include "stdafx.h"
#include "Mob1_RightLeg.h"

#include "Mob1_Body.h"

CMob1_RightLeg::CMob1_RightLeg()
	:pTexInfo(nullptr)
{
}


CMob1_RightLeg::~CMob1_RightLeg()
{
	Release();
}

HRESULT CMob1_RightLeg::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/ENEMY/Stage1_Boss/Right_Leg/Right_Leg.png", L"Stage1_Boss_RightLeg", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage 1 Boss Right Leg Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = D3DXVECTOR3(-95.f, 138.f, 0.f);

	return S_OK;
}

int CMob1_RightLeg::Update()
{
	CObj* pBody = new CMob1_Body;

	D3DXMATRIX matTrans, matParent;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	matParent = dynamic_cast<CObj*>(pBody)->GetInfo().matWorld;

	m_tInfo.matWorld = matTrans * matParent;

	return NO_EVENT;
}

void CMob1_RightLeg::LateUpdate()
{
}

void CMob1_RightLeg::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(m_pImageKey);

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
		&D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f) /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMob1_RightLeg::Release()
{
}
