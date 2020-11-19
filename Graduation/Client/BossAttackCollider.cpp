#include "stdafx.h"
#include "BossAttackCollider.h"
#include "StageBoss.h"

CBossAttackCollider::CBossAttackCollider()
	:m_pBoss(nullptr)
{
}


CBossAttackCollider::~CBossAttackCollider()
{
	Release();
}

HRESULT CBossAttackCollider::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Collider/Rectangle.png", L"Box", TEX_SINGLE)))
	{
		ERR_MSG(L"Collider Box Image Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vSize = { 166.f,280.f,0.f };

	m_tData.iDamage = 1;

	return S_OK;
}

int CBossAttackCollider::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	D3DXMatrixIdentity(&matPos);

	m_tInfo.matWorld = matScale * matTrans * matPos;

	float fTime = 0.f;
	fTime += 1000.f * CTimeMgr::GetInstance()->GetTime();

	if (fTime >= 1.f)
	{
		return DEAD_OBJ;
	}

	//m_tInfo.vPos.x += 0.02f;

	return NO_EVENT;
}

void CBossAttackCollider::LateUpdate()
{
}

void CBossAttackCollider::Render()
{
	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Box");

	//CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// �̹����� ���� ���ϱ�.
	//int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//int iCenterY = pTexInfo->tImgInfo.Height / 2;

	////// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//	nullptr /*����� �̹��� ������ RECT*/,
	//	&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
	//	nullptr/*&D3DXVECTOR3(m_tInfo.vPos.x - 400.f, m_tInfo.vPos.y - 450.f, 0.f)*/ /*����� ��ġ ��ǥ D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBossAttackCollider::Release()
{
}
