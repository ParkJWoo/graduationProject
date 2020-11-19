#include "stdafx.h"
#include "Obj.h"

#include "LeftAttackEffect.h"
#include "RightAttackEffect.h"

#include "Effect.h"
#include "AnimEffect.h"
#include "NonAnimEffect.h"


CObj::CObj()
	: m_bIsInit(false), m_bIsDead(false), bIsFirstAttack(false), bIsSecondAttack(false), m_tTime(0.f), m_bIsClick(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = { 1.f, 0.f, 0.f };
	m_bIsLeft = false;
	m_bIsRight = true;
	m_bOnButton = false;
	m_bIsInven = false;
	m_bIsDoor = false;
	m_iHpNum = 4;
	m_eState = STATEID::STATE_END;

	m_pPlayer = nullptr;
}

CObj::~CObj()
{
}

void CObj::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}

HRESULT CObj::LoadObjects()
{
	return S_OK;
}

void CObj::MoveFrame()
{
	// 1초당 fMax길이 만큼 재생될 것!


	if ((m_wstrStateKey == L"Right_Attack" || m_wstrStateKey == L"Left_Attack" || m_wstrStateKey == L"Right_Damaged") && m_tFrame.fMax <= 12.f)
	{
		if (iAttackCnt >= 3)
		{
			m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

			m_tFrame.fFrame = 17.f;
			m_tFrame.fMax = 27.f;

			/*if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_wstrStateKey = L"Right_WaitingAttack";

				m_tFrame.fFrame = 0.f;
				m_tFrame.fMax = 10.f;
			}*/

			//CObjMgr::GetInstance()->AddObject(CreateRightAttackEffect<CRightAttackEffect>(), OBJID::OBJ_EFFECT);

		}

		else if (iAttackCnt < 3)
		{
			m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

			if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				if (m_bIsLeft && !m_bIsRight)
				{
					m_wstrStateKey = L"Left_WaitingAttack";

					m_tFrame.fFrame = 0.f;
					m_tFrame.fMax = 10.f;
				}

				if (!m_bIsLeft && m_bIsRight)
				{
					m_wstrStateKey = L"Right_WaitingAttack";

					m_tFrame.fFrame = 0.f;
					m_tFrame.fMax = 10.f;
				}
			}
		}
	}

	if (m_wstrObjKey == L"Enemy1" && m_wstrStateKey == L"Attack" && m_tFrame.fMax <= 10.f)
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 100;

	else
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();


	if (m_wstrStateKey == L"Right_Special" && m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_wstrStateKey = L"Right_Idle";

		m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 7.f;
	}


	if (m_tFrame.fFrame > m_tFrame.fMax && iAttackCnt >= 3)
	{
		if (m_bIsLeft && !m_bIsRight)
		{
			iAttackCnt = 0;

			m_wstrStateKey = L"Left_WaitingAttack";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 10.f;
		}

		if (!m_bIsLeft && m_bIsRight)
		{
			iAttackCnt = 0;

			m_wstrStateKey = L"Right_WaitingAttack";

			m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 10.f;
		}
	}

	/*if ((m_wstrObjKey == L"Enemy3" && m_wstrStateKey == L"Mob3_Die") && m_tFrame.fFrame > m_tFrame.fMax)
		m_bIsDead = true;*/

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

}

void CObj::OnceFrame()
{
	// 1초당 fMax길이 만큼 재생될 것!
	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		m_tFrame.fFrame = 0;
		m_tFrame.fMax = 0;
	}
}

void CObj::QuickFrame()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.vPos.x + m_tInfo.vSize.x * 0.5f);
	m_tRect.top = LONG(m_tInfo.vPos.y + m_tInfo.vSize.y * 0.5f);
	m_tRect.right = LONG(m_tInfo.vPos.x - m_tInfo.vSize.x * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.vPos.y - m_tInfo.vSize.y * 0.5f);
}

