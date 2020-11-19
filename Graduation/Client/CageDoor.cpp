#include "stdafx.h"
#include "CageDoor.h"


CCageDoor::CCageDoor()
	:m_fTime(0.f)
{
}

CCageDoor::~CCageDoor()
{
	Release();
}

HRESULT CCageDoor::Initialize()
{
	//if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Door/CageDoor.png", L"CageDoor", TEX_SINGLE)))
	//{
	//	ERR_MSG(L"CageDoor Image Insert Failed!!!");
	//	return E_FAIL;
	//}

	m_wstrObjKey = L"Door";
	m_wstrStateKey = L"NotBroken";

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 5.f;


	//m_tInfo.vPos = { -770.f,440.f,0.f };
	m_tInfo.vSize = { 100.f,510.f,0.f };

	m_tData.iHp = 2;

	CTimeMgr::GetInstance()->InitTime();

	return S_OK;
}

int CCageDoor::Update()
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	m_fTime += CTimeMgr::GetInstance()->GetTime();

	if (m_bIsDead)
	{
		m_wstrStateKey = L"Broken";

		//m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 6.f;
		m_tFrame.fFrame += (float)(m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 1.5);

		if (m_tFrame.fFrame >= m_tFrame.fMax)
		{
			return DEAD_OBJ;
		}
	}

	return NO_EVENT;
}

void CCageDoor::LateUpdate()
{
	//CObj::MoveFrame();
}

void CCageDoor::Render()
{
	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"CageDoor");

	//D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	//D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScrollMgr::GetScroll().x, m_tInfo.vPos.y - CScrollMgr::GetScroll().y, 0.f);

	//matWorld = matScale * matTrans;

	////// SetTransform: ����� �ݿ��ϴ� �Լ�.
	//CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	//// �̹����� ���� ���ϱ�.
	//int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//int iCenterY = pTexInfo->tImgInfo.Height / 2;

	////// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//	nullptr /*����� �̹��� ������ RECT*/,
	//	&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
	//	nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr/*&D3DXVECTOR3(m_tInfo.vPos.x - 500.f, m_tInfo.vPos.y - 350.f,0.f)*/, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CCageDoor::Release()
{
}
