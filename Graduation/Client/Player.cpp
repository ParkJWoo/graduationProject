#include "stdafx.h"
#include "Player.h"
#include "Mouse.h"
#include "Effect.h"
#include "BuffEffect.h"
#include "AnimEffect.h"
#include "NonAnimEffect.h"
#include "HpBar.h"
#include "MpBar.h"
#include "MpBarRight.h"
#include "AttackCollider.h"
#include "SpecialAttackCollider.h"

#include "LeftAttackEffect.h"

#include "InvenIcon.h"
#include "Inventory.h"
#include "SettingIcon.h"
#include "TutorialDialog.h"

CPlayer::CPlayer()
	:m_fSpeed(0.f), pHpCase(nullptr), pHpBar(nullptr), pInven(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{
	//m_tInfo.vSize = { 95.f, 246.f ,0.f };

	//m_tInfo.vPos = { 0.f, 450.f, 0.f };

	m_wstrObjKey = L"PLAYER";
	m_wstrStateKey = L"Right_Idle";

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 6.f;
	

	m_tData.iHp = 4;
	m_tData.iMp = 2;

	m_tInfo.vSize = { 10.f,150.f,0.f };

	m_fSpeed = 0.2f;

	m_fJupPow = 0.9f;
	m_fJupAcc = 0.f;

	m_bIsJump = false;
	m_bIsDamage = false;

	return S_OK;
}

void CPlayer::LateInit()
{
	/*CAbstractFactory<CHpBar>::CreateObj(pHpCase, D3DXVECTOR3(-370.f, -220.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpCase, OBJ_UI);

	CAbstractFactory<CHpBar>::CreateObj(pHpBar, D3DXVECTOR3(-310.f, -237.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpBar, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpBar, D3DXVECTOR3(-10.f, -20.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpBar2,D3DXVECTOR3(23.5f, -20.f,0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar2, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpCase, D3DXVECTOR3(13.f, -30.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpCase, OBJ_UI);

	dynamic_cast<CHpBar*>(pHpCase)->SetImageKey(L"HPCase");
	dynamic_cast<CHpBar*>(pHpBar)->SetImageKey(L"HPBar");

	dynamic_cast<CMpBar*>(pMpCase)->SetImageKey(L"MPCase");
	dynamic_cast<CMpBar*>(pMpBar)->SetImageKey(L"MPBar");
	dynamic_cast<CMpBar*>(pMpBar2)->SetImageKey(L"MPBar");


	CObj* pInvenIcon = nullptr;
	CAbstractFactory<CInvenIcon>::CreateObj(pInvenIcon);
	CObjMgr::GetInstance()->AddObject(pInvenIcon, OBJ_UI);

	CObj* pSettingIcon = nullptr;
	CAbstractFactory<CSettingIcon>::CreateObj(pSettingIcon);
	CObjMgr::GetInstance()->AddObject(pSettingIcon, OBJ_UI);*/

	/*CObj* pTutorial = nullptr;
	CAbstractFactory<CTutorialDialog>::CreateObj(pTutorial);
	CObjMgr::GetInstance()->AddObject(pTutorial, OBJ_UI);*/

	/*CAbstractFactory<CMpBar>::CreateObj(pMpBar, D3DXVECTOR3(-10.f, -20.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar, OBJ_UI);

	CAbstractFactory<CMpBarRight>::CreateObj(pMpBar2, D3DXVECTOR3(23.5f, -20.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar2, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpCase, D3DXVECTOR3(13.f, -30.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpCase, OBJ_UI);

	dynamic_cast<CMpBar*>(pMpCase)->SetImageKey(L"MPCase");
	dynamic_cast<CMpBar*>(pMpBar)->SetImageKey(L"MPBar");*/
	//dynamic_cast<CMpBarRight*>(pMpBar2)->SetImageKey(L"MPBar");

	CDataSubject::GetInstance()->AddData(PLAYER_DATA, &m_tData); // 관찰 대상 등록
	//CDataSubject::GetInstance()->AddData(PLAYER_MATRIX, &m_tInfo.matWorld);

	CDataSubject::GetInstance()->Notify(PLAYER_DATA, &m_tData);

}

int CPlayer::Update()
{
	CObj::LateInit();

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	//CDataSubject::GetInstance()->AddData(PLAYER_MATRIX, &m_tInfo.matWorld);
	CDataSubject::GetInstance()->Notify(PLAYER_MATRIX, &m_tInfo.matWorld);

	KeyCheck();

	IsJumping();

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	CObj::MoveFrame();

	//if (m_tData.iHp <= 3 && !m_bIsDamage)
	//{
	//	m_wstrStateKey = L"Right_Damaged";

	//	m_tFrame.fMax = 10.f;

	//	if (m_tFrame.fFrame > m_tFrame.fMax)
	//	{
	//		m_bIsDamage = true;
	//	}

	//}

	//else
	//	m_bIsDamage = false;
}

void CPlayer::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), &D3DXVECTOR3(0.f, m_tInfo.vPos.y - 350.f, 0.f)/*&D3DXVECTOR3(m_tInfo.vPos.x - 500.f, m_tInfo.vPos.y - 350.f,0.f)*/, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
	//CObjMgr::GetInstance()->Release();
	//CDataSubject::GetInstance()->RemoveData(PLAYER_DATA,&m_tData);
	//CDataSubject::GetInstance()->RemoveData(PLAYER_MATRIX, &m_tInfo.matWorld);
	//CDataSubject::GetInstance()->Release();
}

void CPlayer::KeyCheck()
{
	bool bIsFirstAttack = false;
	bool bIsSecondAttack = false;

	//	플레이어 이동 키 설정	///////////////////////////////////////////////////////////////////////////

	///////	오른쪽 이동 ///////
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RIGHT))
	{
		m_wstrStateKey = L"Right_Run";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 36.f;

		m_bIsRight = true;
		m_bIsLeft = false;
	} 

	if (CKeyMgr::GetInstance()->KeyPress(KEY_RIGHT))
	{
		m_tInfo.vPos += D3DXVECTOR3(m_fSpeed, 0.f, 0.f);

		m_bIsRight = true;
		m_bIsLeft = false;
	}

	if (CKeyMgr::GetInstance()->KeyUp(KEY_RIGHT))
	{
		m_wstrStateKey = L"Right_Idle";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 7.f;

		m_bIsRight = true;
		m_bIsLeft = false;
	}

	//////////////////////////	

	///////	왼쪽 이동 ///////

	if (CKeyMgr::GetInstance()->KeyDown(KEY_LEFT))
	{
		//m_tInfo.vPos -= D3DXVECTOR3(m_fSpeed, 0.f, 0.f);
		m_wstrStateKey = L"Left_Run";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 36.f;

		m_bIsRight = false;
		m_bIsLeft = true;
	}

	if (CKeyMgr::GetInstance()->KeyPress(KEY_LEFT))
	{
		m_tInfo.vPos -= D3DXVECTOR3(m_fSpeed, 0.f, 0.f);

		m_bIsRight = false;
		m_bIsLeft = true;
	}

	if (CKeyMgr::GetInstance()->KeyUp(KEY_LEFT))
	{
		CObj::MoveFrame();

		m_wstrStateKey = L"Left_Idle";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 7.f;

		m_bIsRight = false;
		m_bIsLeft = true;
	}

	//	플레이어 공격 //
	if (CKeyMgr::GetInstance()->KeyDown(KEY_A))
	{
		if (m_bIsLeft && !m_bIsRight)
		{
			m_wstrStateKey = L"Left_Attack";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 11.f;

			m_bIsRight = false;
			m_bIsLeft = true;

			CObjMgr::GetInstance()->AddObject(CreateLeftAttackCollider<CAttackCollider>(), OBJID::OBJ_BULLET);

			/*CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(m_tInfo.vPos,
				L"LeftEffect", { 0.f, 4.f });*/

			/*CObj* pEffect = CEffectFactory<CEffect, CNonAnimEffect>::CreateEffect(m_tInfo.vPos,
				L"LeftEffect", 1.f);*/

			CObj* pEffect = CEffectFactory<CEffect, CNonAnimEffect>::CreateEffect(m_tInfo.vPos,
				L"LeftEffect", 1.f);

			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
		}

		if (!m_bIsLeft && m_bIsRight)
		{
			m_wstrStateKey = L"Right_Attack";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 11.f;

			m_bIsRight = true;
			m_bIsLeft = false;

			CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CAttackCollider>(), OBJID::OBJ_BULLET);

			/*CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(m_tInfo.vPos,
				L"RightEffect", { 0.f, 4.f });*/

			CObj* pEffect = CEffectFactory<CEffect, CNonAnimEffect>::CreateEffect(D3DXVECTOR3(m_tInfo.vPos.x - 50.f, m_tInfo.vPos.y, 0.f),
				L"RightEffect", 2.f);

			CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
		}

		++iAttackCnt;

	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_X))
	{
		m_tData.iMp -= 1;

		/*if (m_tData.iMp < 0)
		{
			m_wstrStateKey = L"Right_Idle";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 6.f;
		}*/

	/*	else
		{
			m_wstrStateKey = L"Right_Special";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 17.f;

			CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CSpecialAttackCollider>(), OBJID::OBJ_SPECIALATTACK);
			CDataSubject::GetInstance()->Notify(PLAYER_DATA, &m_tData);
		}*/

		m_wstrStateKey = L"Right_Special";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 17.f;

		CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CSpecialAttackCollider>(), OBJID::OBJ_SPECIALATTACK);
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_DOWN))
	{
		m_wstrStateKey = L"Right_Avoid";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 7.f;
	}


	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		m_bIsJump = true;
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_UP))
	{
		m_wstrStateKey = L"Right_Damaged";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 10.f;

		//m_iHpNum -= 1;
		m_tData.iHp -= 1;

		CDataSubject::GetInstance()->Notify(PLAYER_DATA, &m_tData);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//	플레이어 공격 //
	/*if (CKeyMgr::GetInstance()->KeyDown(KEY_A))
	{
		m_wstrStateKey = L"Right_Attack";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 11.f;

		++iAttackCnt;

		CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CAttackCollider>(), OBJID::OBJ_BULLET);
	}*/


	if (CKeyMgr::GetInstance()->KeyDown(KEY_I))
	{
		//	i키 입력 시 인벤토리 나올 예정
		m_bIsInven = true;
	}
}

void CPlayer::IsJumping()
{
	float fY = m_tInfo.vPos.y;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.vPos.x, &fY);
	bool bColl2 = CStage2LineMgr::GetInstance()->LineCollision(m_tInfo.vPos.x, &fY);

	if (m_bIsJump)
	{
		// y축 포물선 공식
		// y = v * sin@ * t - g * t^2 * 0.5
		if (m_bIsLeft && !m_bIsRight)
		{
			m_wstrStateKey = L"Left_Run";

			m_tFrame.fFrame = 17.f;
			m_tFrame.fMax = 17.f;

			m_bIsRight = false;
			m_bIsLeft = true;
		}

		if (!m_bIsLeft && m_bIsRight)
		{
			m_wstrStateKey = L"Right_Run";

			m_tFrame.fFrame = 17.f;
			m_tFrame.fMax = 17.f;

			m_bIsRight = true;
			m_bIsLeft = false;
		}


		m_tInfo.vPos.y -= m_fJupPow * m_fJupAcc - GRAVITY * m_fJupAcc * m_fJupAcc * 0.5f;
		m_fJupAcc += 0.0001f;

		if ((bColl && m_tInfo.vPos.y > fY) || (bColl2 && m_tInfo.vPos.y > fY) ) // 지면에 닿았을 때
		{
			/*m_wstrStateKey = L"Right_Idle";
			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 7.f;*/

			m_bIsJump = false;
			m_fJupAcc = 0.f;
			m_tInfo.vPos.y = fY;
		}
	}

	else if ((!m_bIsJump && bColl) || (!m_bIsJump && bColl2))	// 점프 중이 아니지만 지면에 충돌했을 때
		m_tInfo.vPos.y = fY;
}