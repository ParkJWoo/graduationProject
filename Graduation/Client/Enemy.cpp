#include "stdafx.h"
#include "Enemy.h"
#include "AnimEffect.h"
#include "NonAnimEffect.h"

#include "Mob1_Body.h"
#include "Mob1_Head.h"
#include "Mob1_LeftArm.h"
#include "Mob1_RightArm.h"
#include "Mob1_BodyBack.h"
#include "Mob1_LeftLeg.h"
#include "Mob1_LeftCalf.h"
#include "Mob1_RightLeg.h"
#include "Mob1_RightCalf.h"

CEnemy::CEnemy()
	:m_fSpeed(0.f), m_pTarget(nullptr)
{
}

CEnemy::~CEnemy()
{
	Release();
}

HRESULT CEnemy::Initialize()
{
	/*m_wstrObjKey = L"ENEMY";
	m_wstrStateKey = L"Idle";*/

	m_tInfo.vPos = D3DXVECTOR3(400.f, 400.f, 0.f);

	//m_tFrame.fFrame = 0.f;
	//m_tFrame.fMax = 14.f;

	//m_fSpeed = 0.005f;

	//m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	

	return S_OK;
}

void CEnemy::LateInit()
{
	CObj* pMob1_Back = nullptr;
	CAbstractFactory<CMob1_BodyBack>::CreateObj(pMob1_Back);
	CObjMgr::GetInstance()->AddObject(pMob1_Back, OBJ_MONSTER);
	dynamic_cast<CMob1_BodyBack*>(pMob1_Back)->SetImageKey(L"Stage1_Boss_BodyBack");

	CObj* pMob1_LeftArm = nullptr;
	CAbstractFactory<CMob1_LeftArm>::CreateObj(pMob1_LeftArm);
	CObjMgr::GetInstance()->AddObject(pMob1_LeftArm, OBJ_MONSTER);
	dynamic_cast<CMob1_LeftArm*>(pMob1_LeftArm)->SetImageKey(L"Stage1_Boss_LeftArm");

	CObj* pMob1_Body = nullptr;
	CAbstractFactory<CMob1_Body>::CreateObj(pMob1_Body);
	CObjMgr::GetInstance()->AddObject(pMob1_Body, OBJ_MONSTER);
	dynamic_cast<CMob1_Body*>(pMob1_Body)->SetImageKey(L"Stage1_Boss_Body");

	CObj* pMob1_LeftLeg = nullptr;
	CAbstractFactory<CMob1_LeftLeg>::CreateObj(pMob1_LeftLeg);
	CObjMgr::GetInstance()->AddObject(pMob1_LeftLeg, OBJ_MONSTER);
	dynamic_cast<CMob1_LeftLeg*>(pMob1_LeftLeg)->SetImageKey(L"Stage1_Boss_LeftLeg");


	CObj* pMob1_LeftCalf = nullptr;
	CAbstractFactory<CMob1_LeftCalf>::CreateObj(pMob1_LeftCalf);
	CObjMgr::GetInstance()->AddObject(pMob1_LeftCalf, OBJ_MONSTER);
	dynamic_cast<CMob1_LeftCalf*>(pMob1_LeftCalf)->SetImageKey(L"Stage1_Boss_LeftCalf");


	CObj* pMob1_Head = nullptr;
	CAbstractFactory<CMob1_Head>::CreateObj(pMob1_Head);
	CObjMgr::GetInstance()->AddObject(pMob1_Head, OBJ_MONSTER);
	dynamic_cast<CMob1_Head*>(pMob1_Head)->SetImageKey(L"Stage1_Boss_Head");

	
	CObj* pMob1_RightArm = nullptr;
	CAbstractFactory<CMob1_RightArm>::CreateObj(pMob1_RightArm);
	CObjMgr::GetInstance()->AddObject(pMob1_RightArm, OBJ_MONSTER);
	dynamic_cast<CMob1_RightArm*>(pMob1_RightArm)->SetImageKey(L"Stage1_Boss_RightArm");

	CObj* pMob1_RightLeg = nullptr;
	CAbstractFactory<CMob1_RightLeg>::CreateObj(pMob1_RightLeg);
	CObjMgr::GetInstance()->AddObject(pMob1_RightLeg, OBJ_MONSTER);
	dynamic_cast<CMob1_RightLeg*>(pMob1_RightLeg)->SetImageKey(L"Stage1_Boss_RightLeg");

	CObj* pMob1_RightCalf = nullptr;
	CAbstractFactory<CMob1_RightCalf>::CreateObj(pMob1_RightCalf);
	CObjMgr::GetInstance()->AddObject(pMob1_RightCalf, OBJ_MONSTER);
	dynamic_cast<CMob1_RightCalf*>(pMob1_RightCalf)->SetImageKey(L"Stage1_Boss_RightCalf");

}

int CEnemy::Update()
{
	CObj::LateInit();

	//if (nullptr != m_pTarget)
	//{
	//	// 몬스와 타겟을 이루는 삼각형의 세변을 구한다.
	//	// 순서유의! 반드시 타겟에서부터 뺄샘을 한다!
	//	float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x;
	//	float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
	//	float d = sqrtf(w * w + h * h);

	//	// 삼각형의 삼각비를 이용하여 끼인각을 얻어낸다.
	//	// 역삼각함수는 끼인각을 라디안으로 반환한다.
	//	m_fAngle = acosf(w / d);

	//	// acosf이 구할 수 있는 각도 범위는 0 ~ 180도.
	//	// 따라서, 180도를 넘어설 때에는 아래와 같이 예외처리를 해주어야한다.
	//	if (m_tInfo.vPos.x < m_pTarget->GetInfo().vPos.x)
	//	{
	//		//m_fAngle = (2.f * PI) - m_fAngle;
	//		m_fAngle *= -1.f;
	//	}

	//	// 구한 각도대로 몬스터를 이동.

	//	if (m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x >= 100.f)
	//	{
	//		m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;

	//	}
	//}

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	//CObjMgr::GetInstance()->Update();

	return NO_EVENT;
}

void CEnemy::LateUpdate()
{
	CObj::MoveFrame();

	//CObjMgr::GetInstance()->LateUpdate();
}

void CEnemy::Render()
{
	/*const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	if (CSceneMgr::GetInstance()->GetID() == CSceneMgr::STAGE1_1)
		m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	m_tRect.left = (LONG)(m_tInfo.vPos.x - fCenterX);
	m_tRect.right = (LONG)(m_tInfo.vPos.x + fCenterX);
	m_tRect.top = (LONG)(m_tInfo.vPos.y - fCenterY);
	m_tRect.bottom = (LONG)(m_tInfo.vPos.y + fCenterY);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), &D3DXVECTOR3(m_tInfo.vPos.x - 500.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));*/

	//CObjMgr::GetInstance()->Render();
}

void CEnemy::Release()
{
	//CObjMgr::GetInstance()->Release();
}