#include "stdafx.h"
#include "EnemyHP.h"
#include "UIObserver.h"

#include "Monster1.h"

CEnemyHP::CEnemyHP()
	:m_iHp(0), pTexInfo(nullptr)
{
}

CEnemyHP::~CEnemyHP()
{
	Release();
}

HRESULT CEnemyHP::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Boss_UI/HP_Case.png", L"BossHPCase", TEX_SINGLE)))
	{
		ERR_MSG(L"Boss HP Case Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Boss_UI/Hp%d.png", L"BossHPBar",
		TEX_MULTI, L"BossHPBar", 5)))
	{
		ERR_MSG(L"Boss Hp Bar Insert Failed!!!");
		return E_FAIL;
	}

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);	// ������ ���.

	return S_OK;
}

void CEnemyHP::LateInit()
{
}

int CEnemyHP::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans, matParent;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matParent = dynamic_cast<CUIObserver*>(m_pObserver)->GetMatrix();
	m_iHp = dynamic_cast<CUIObserver*>(m_pObserver)->GetData().iHp;

	m_tInfo.matWorld = matScale * matTrans * matParent;

	return NO_EVENT;
}

void CEnemyHP::LateUpdate()
{
}

void CEnemyHP::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"BossHPCase");

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	/*m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - iCenterX);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + iCenterX);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - iCenterY);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + iCenterY);*/


	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX + 330.f, (float)iCenterY - 40.f, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,

		D3DCOLOR_ARGB(255, 255, 255, 255));
	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(
		L"BossHPBar", L"BossHPBar", m_iHp);

	/*const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(
		L"HPBar", L"HPBar", m_iHp);*/

		//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	m_tInfo.vSize = { (float)pTexInfo2->tImgInfo.Width, (float)pTexInfo2->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - iCenterX2);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + iCenterX2);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - iCenterY2);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + iCenterY2);


	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX2 + 295.f, (float)iCenterY2 - 23.f, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CEnemyHP::Release()
{
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
