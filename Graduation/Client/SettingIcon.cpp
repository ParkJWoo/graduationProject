#include "stdafx.h"
#include "SettingIcon.h"
#include "UIObserver.h"

CSettingIcon::CSettingIcon()
{
}

CSettingIcon::~CSettingIcon()
{
	Release();
}

HRESULT CSettingIcon::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Setting_UI/Setting_UI.png", L"Setting_UI", TEX_SINGLE)))
	{
		ERR_MSG(L"Setting UI Image Insert Failed!!!");
		return E_FAIL;
	}

	m_tInfo.vPos = { 870.f, -70.f, 0.f };

	m_pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);	// ������ ���.

	return S_OK;
}

void CSettingIcon::LateInit()
{
}

int CSettingIcon::Update()
{
	CObj::LateInit();

	D3DXMATRIX matScale, matTrans, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	D3DXMatrixIdentity(&matPos);

	matParent = dynamic_cast<CUIObserver*>(m_pObserver)->GetMatrix();

	matPos._41 = matParent._41;

	m_tInfo.matWorld = matScale * matTrans * matPos;

	return NO_EVENT;
}

void CSettingIcon::LateUpdate()
{
}

void CSettingIcon::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Setting_UI");

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CSettingIcon::Release()
{
	CDataSubject::GetInstance()->UnSubscribe(m_pObserver);
}
