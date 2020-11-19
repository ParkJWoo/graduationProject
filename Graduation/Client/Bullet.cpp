#include "stdafx.h"
#include "Bullet.h"

#include "Player.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

HRESULT CBullet::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Stage/Bullet/Bullet.png", L"Bullet", TEX_SINGLE)))
	{
		ERR_MSG(L"Bullet Image Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vSize = { 50.f,50.f,0.f };

	m_tData.iDamage = 1;

	return S_OK;
}

int CBullet::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	D3DXMatrixIdentity(&matPos);

	m_tInfo.matWorld = matScale * matTrans * matPos;

	m_tInfo.vPos.x -= 0.4f;

	//m_tInfo.vPos.x -= 0.05f;

	return NO_EVENT;
}

void CBullet::LateUpdate()
{
	if (m_tInfo.vPos.x <= -700.f)
		m_bIsDead = true;
}

void CBullet::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Bullet");

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr/*&D3DXVECTOR3(m_tInfo.vPos.x - 400.f, m_tInfo.vPos.y - 450.f, 0.f)*/ /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBullet::Release()
{
}
