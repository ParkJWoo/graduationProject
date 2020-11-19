#include "stdafx.h"
#include "Camera.h"

#include "Player.h"

#include "Device.h"
#include "InvenIcon.h"
#include "Inventory.h"
#include "SettingIcon.h"
#include "HpBar.h"
#include "TutorialDialog.h"
#include "MpBar.h"

#include "BackLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"
#include "FrontLayer.h"

IMPLEMENT_SINGLETON(CCamera)

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
	Release();
}

void CCamera::SetTransform()
{
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matOrthographic);
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_WORLD, &m_matIdentity);
	CDevice::GetInstance()->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);
}

HRESULT CCamera::Initialize(int iWidth, int iHeight, float fAngle, D3DXVECTOR3 vFaceFactors)
{
	this->iWidth = iWidth;
	this->iHeight = iHeight;
	this->m_fAngle = fAngle;
	this->m_vScaleFactors = vFaceFactors;

	D3DXMatrixOrthoLH(&m_matOrthographic, (float)iWidth, (float)-iHeight, 0.f, 1.f);
	D3DXMatrixIdentity(&m_matIdentity);

	/*CAbstractFactory<CHpBar>::CreateObj(pHpCase, D3DXVECTOR3(-370.f, -220.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpCase, OBJ_UI);*/

	CAbstractFactory<CHpBar>::CreateObj(pHpBar, D3DXVECTOR3(-310.f, -237.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpBar, OBJ_UI);

	/*CAbstractFactory<CMpBar>::CreateObj(pMpBar, D3DXVECTOR3(-10.f, -160.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpBar2, D3DXVECTOR3(23.5f, -160.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar2, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpCase, D3DXVECTOR3(13.f, -150.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpCase, OBJ_UI);*/

	//dynamic_cast<CHpBar*>(pHpCase)->SetImageKey(L"HPCase");
	dynamic_cast<CHpBar*>(pHpBar)->SetImageKey(L"HPBar");

	//dynamic_cast<CMpBar*>(pMpCase)->SetImageKey(L"MPCase");
	//dynamic_cast<CMpBar*>(pMpBar)->SetImageKey(L"MPBar");
	//dynamic_cast<CMpBar*>(pMpBar2)->SetImageKey(L"MPBar");

	/*pInvenIcon = nullptr;
	CAbstractFactory<CInvenIcon>::CreateObj(pInvenIcon);
	CObjMgr::GetInstance()->AddObject(pInvenIcon, OBJ_UI);

	CObj* pSettingIcon = nullptr;
	CAbstractFactory<CSettingIcon>::CreateObj(pSettingIcon);
	CObjMgr::GetInstance()->AddObject(pSettingIcon, OBJ_UI);*/

	pTutorial = nullptr;
	CAbstractFactory<CTutorialDialog>::CreateObj(pTutorial);
	CObjMgr::GetInstance()->AddObject(pTutorial, OBJ_UI);

	return S_OK;
}

void CCamera::Update()
{
	if (!this->isFollowing())
	{
		this->Following();
	}

	D3DXMATRIX matCamera;

	D3DXMatrixIdentity(&matCamera);

	if (m_pTarget)
	{
		matCamera = this->m_pTarget->GetInfo().matWorld;

		matCamera._41 = this->m_pTarget->GetInfo().matWorld._41 + 100.f;
		matCamera._42 = this->m_pTarget->GetInfo().matWorld._42;
	}

	D3DXVECTOR2 vScroll = D3DXVECTOR2(matCamera._41 - CScrollMgr::GetScroll().x, 300.f - CScrollMgr::GetScroll().y);

	if ((vScroll.x >= (0.f) && vScroll.x <= BACKCX - (m_pTarget->GetInfo().matWorld._41))
		|| (matCamera._41 >= 0.f && matCamera._41 <= 800.f))
	{
		this->m_matView = D3DXMATRIX(
			m_vScaleFactors.x * cosf(m_fAngle), m_vScaleFactors.x * sinf(m_fAngle), 0, 0,
			-m_vScaleFactors.y * sinf(m_fAngle), m_vScaleFactors.y * cosf(m_fAngle), 0, 0,
			0, 0, m_vScaleFactors.z, 0,
			-matCamera._41 * m_vScaleFactors.x * cosf(m_fAngle) + 300.f * m_vScaleFactors.y * sinf(m_fAngle),
			-matCamera._41 * m_vScaleFactors.y * sinf(m_fAngle) - 300.f * m_vScaleFactors.y * cosf(m_fAngle),
			0, 1
		);


		/*if (m_bIsShake == true)
		{
			matCamera._41 += cosf(180.f);

			this->m_matView = D3DXMATRIX(
				m_vScaleFactors.x * cosf(m_fAngle), m_vScaleFactors.x * sinf(m_fAngle), 0, 0,
				-m_vScaleFactors.y * sinf(m_fAngle), m_vScaleFactors.y * cosf(m_fAngle), 0, 0,
				0, 0, m_vScaleFactors.z, 0,
				-matCamera._41 * m_vScaleFactors.x * cosf(m_fAngle) + matCamera._42 * m_vScaleFactors.y * sinf(m_fAngle),
				-matCamera._41 * m_vScaleFactors.y * sinf(m_fAngle) - matCamera._42 * m_vScaleFactors.y * cosf(m_fAngle),
				0, 1
			);

		}*/

		D3DXMATRIX matPos;
		DATA		data;

		//matPos = dynamic_cast<CCamera*>(m_pTarget)->matCamera;
		data = dynamic_cast<CPlayer*>(m_pTarget)->GetData();

		CDataSubject::GetInstance()->AddData(PLAYER_DATA, &data);
		CDataSubject::GetInstance()->AddData(CAMERA_MATRIX, &matCamera);

		CDataSubject::GetInstance()->Notify(CAMERA_MATRIX, &matCamera);
	}
}

void CCamera::Following()
{
	this->m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	m_pTarget->SetPos(D3DXVECTOR3(-100.f, 0.f, 0.f));
}

void CCamera::UnFollow()
{
	this->m_pTarget = nullptr;
}

void CCamera::Release()
{
	/*CObjMgr::GetInstance()->Release();

	if (m_pTarget != nullptr)
	{
		m_pTarget = nullptr;
	}*/

	UnFollow();

	//CObjMgr::GetInstance()->Release();
	//CObjMgr::GetInstance()->DestroyInstance();
}

bool CCamera::isFollowing()
{
	return this->m_pTarget != nullptr;
}

void CCamera::isShake()
{
}
