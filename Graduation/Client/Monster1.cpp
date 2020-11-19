#include "stdafx.h"
#include "Monster1.h"
#include "AnimEffect.h"
#include "NonAnimEffect.h"

#include "AttackCollider.h"

#include "EnemyHP.h"

CMonster1::CMonster1()
	:m_fSpeed(0.f), m_pTarget(nullptr), m_fTime(0.f), m_fRestTime(0.f)
{
	//ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	//ZeroMemory(&m_OldTime1, sizeof(LARGE_INTEGER));
	//ZeroMemory(&m_OldTime2, sizeof(LARGE_INTEGER));
	//ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));

	m_eStateID = STATEID::STATE_END;
	m_bIsCheck = false;
	pHpBar = nullptr;

	m_tData = { 3,0,1 };

	m_bIsJump = false;
}


CMonster1::~CMonster1()
{
	Release();
}

HRESULT CMonster1::Initialize()
{
	/*m_wstrObjKey = L"Enemy1";
	m_wstrStateKey = L"Idle";*/

	//m_tInfo.vPos = D3DXVECTOR3(400.f, 400.f, 0.f);

	m_wstrObjKey = L"Enemy1";

	MonsterState(STATEID::IDLE);

	m_tInfo.vSize = { 150.f,280.f,0.f };

	//m_tFrame.fFrame = 0.f;

	m_fSpeed = 0.1f;

	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	CTimeMgr::GetInstance()->InitTime();

	/*CAbstractFactory<CEnemyHP>::CreateObj(pHpBar);
	CObjMgr::GetInstance()->AddObject(pHpBar, OBJ_UI);

	CDataSubject::GetInstance()->AddData(ENEMY_DATA, &tData);
	CDataSubject::GetInstance()->AddData(ENEMY_MATRIX, &m_tInfo.matWorld);*/

	return S_OK;
}

void CMonster1::LateInit()
{
	//CAbstractFactory<CEnemyHP>::CreateObj(pHpBar);
	//CObjMgr::GetInstance()->AddObject(pHpBar, OBJ_UI);

	//CDataSubject::GetInstance()->AddData(ENEMY_DATA, &m_tData);
	//CDataSubject::GetInstance()->AddData(ENEMY_MATRIX, &m_tInfo.matWorld);
}

int CMonster1::Update()
{
	CObj::LateInit();

	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_fTime += CTimeMgr::GetInstance()->GetTime();


	if (nullptr != m_pTarget)
	{
		// 몬스와 타겟을 이루는 삼각형의 세변을 구한다.
		// 순서유의! 반드시 타겟에서부터 뺄샘을 한다!
		float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x;
		float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
		float d = sqrtf(w * w + h * h);

		// 삼각형의 삼각비를 이용하여 끼인각을 얻어낸다.
		// 역삼각함수는 끼인각을 라디안으로 반환한다.
		m_fAngle = acosf(w / d);

		// acosf이 구할 수 있는 각도 범위는 0 ~ 180도.
		// 따라서, 180도를 넘어설 때에는 아래와 같이 예외처리를 해주어야한다.
		if (m_tInfo.vPos.x < m_pTarget->GetInfo().vPos.x)
		{
			m_fAngle = (2.f * PI) - m_fAngle;
		}

		// 구한 각도대로 몬스터를 이동.
		
		if (m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x >= 200.f)
		{
			MonsterState(STATEID::RUN);

			m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
		}

		else
		{
			/*MonsterState(STATEID::ATTACK);

			if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_fTime += CTimeMgr::GetInstance()->GetTime();

				MonsterState(STATEID::IDLE);
			}*/

			BehaviorFunction();

				/*if (m_fTime >= 0.05f)
				{
					MonsterState(STATEID::IDLE);

					if (m_tFrame.fFrame > m_tFrame.fMax)
					{
						m_tFrame.fFrame = 0.f;

						m_fTime = 0.f;
					}

				}*/

					//if (m_tFrame.fFrame > m_tFrame.fMax)
					//{
					//	m_tFrame.fFrame = 0.f;

					//	m_fTime = AttackTerm();

					//	if (m_fTime >= 5.f)
					//	{
					//		/*m_wstrStateKey = L"Attack";

					//		m_tFrame.fMax = 5.f;

					//		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 3;*/

					//		m_wstrStateKey = L"Idle";

					//		m_tFrame.fMax = 10.f;

					//		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();
					//	}
					//}

				/*else
				{
					m_wstrStateKey = L"Attack";

					m_tFrame.fMax = 5.f;

					m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 3;
				}*/
			

		}

		if (0 < m_tData.iHp && m_tData.iHp <= 2)
		{
			MonsterState(STATEID::DAMAGED);

			//m_tInfo.vPos.y = 450.f;

			if (m_tFrame.fFrame >= m_tFrame.fMax)
			{
				MonsterState(STATEID::IDLE);
			}

		}

		if (m_tData.iHp <= 0)
		{
			//m_fTime = 0.f;

			MonsterState(STATEID::DIE);

			//m_tInfo.vPos.y = 450.f;

			/*if (m_tFrame.fFrame > m_tFrame.fMax)
			{
				m_fTime += CTimeMgr::GetInstance()->GetTime();

				if (m_fTime <= 10.f)
					m_bIsDead = true;
			}*/
		}
	}

	//CDataSubject::GetInstance()->Notify(ENEMY_MATRIX, &m_tInfo.matWorld);

	return NO_EVENT;
}

void CMonster1::LateUpdate()
{
	//CObj::MoveFrame();
}

void CMonster1::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
		m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	if (CSceneMgr::GetInstance()->GetID() == CSceneMgr::STAGE1_1)
		m_tInfo.vSize = { (float)pTexInfo->tImgInfo.Width, (float)pTexInfo->tImgInfo.Height,0.f };

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), &D3DXVECTOR3(0.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMonster1::Release()
{
}

float CMonster1::AttackTerm()
{
	m_fTime = 0.f;

	QueryPerformanceCounter(&m_CurTime);

	// 현재 시간과 과거 시간의 갭이 m_CpuTick을 넘을 경우 보정.
	if (m_CurTime.QuadPart - m_OldTime2.QuadPart > m_CpuTick.QuadPart)
	{
		// 현재 CPU 진동수를 새로 얻어온다.
		QueryPerformanceFrequency(&m_CpuTick);
		m_OldTime2 = m_CurTime;

		m_fTime = float(m_CurTime.QuadPart - m_OldTime1.QuadPart) / m_CpuTick.QuadPart;
	}

	return m_fTime;
}

float CMonster1::RestTerm()
{
	m_fRestTime = 0.f;

	QueryPerformanceCounter(&m_CurTime);

	// 현재 시간과 과거 시간의 갭이 m_CpuTick을 넘을 경우 보정.
	if (m_CurTime.QuadPart - m_OldTime2.QuadPart > m_CpuTick.QuadPart)
	{
		// 현재 CPU 진동수를 새로 얻어온다.
		QueryPerformanceFrequency(&m_CpuTick);
		m_OldTime2 = m_CurTime;

		m_fRestTime = float(m_CurTime.QuadPart - m_OldTime1.QuadPart) / m_CpuTick.QuadPart;
	}

	return m_fRestTime;
}


HRESULT CMonster1::MonsterState(STATEID eID)
{
	m_eState = eID;

	switch (m_eState)
	{
	case IDLE:
		m_eStateID = STATEID::IDLE;
		m_wstrStateKey = L"Idle";
		m_tFrame.fMax = 10.f;
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

		if (m_tFrame.fFrame > m_tFrame.fMax)
			m_tFrame.fFrame = 0.f;
		break;

	case ATTACK:
		m_eStateID = STATEID::ATTACK;
		m_wstrStateKey = L"Attack";
		m_tFrame.fMax = 41.f;
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() * 0.5f;

		//CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CAttackCollider>(), OBJID::OBJ_ENEMYATTACK);

		if (m_tFrame.fFrame > m_tFrame.fMax)
			m_tFrame.fFrame = 0.f;

		break;

	case DAMAGED:
		m_eStateID = STATEID::DAMAGED;
		m_wstrStateKey = L"Damaged";
		m_tFrame.fMax = 17.f;
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

		if (m_tFrame.fFrame > m_tFrame.fMax)
			m_tFrame.fFrame = 0.f;
		break;

	case RUN:
		m_eStateID = STATEID::RUN;
		m_wstrStateKey = L"Run";
		m_tFrame.fMax = 31.f;
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

		if (m_tFrame.fFrame > m_tFrame.fMax)
			m_tFrame.fFrame = 0.f;
		break;

	case DIE:
		m_eStateID = STATEID::DIE;
		m_wstrStateKey = L"Die";
		m_tFrame.fMax = 11.f;
		m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime();

		if (m_tFrame.fFrame > m_tFrame.fMax)
			m_tFrame.fFrame = 0.f;
		break;
	}

	return S_OK;
}

void CMonster1::BehaviorFunction()
{
	if (m_eStateID == STATEID::DIE)
	{
		m_bIsDead = true;
		return;
	}

	MonsterState(STATEID::ATTACK);

	//if (m_tFrame.fFrame > m_tFrame.fMax)
	//{
	//	//MonsterState(STATEID::IDLE);

	//	if (m_tFrame.fFrame > m_tFrame.fMax)
	//	{
	//	/*	if ((int)m_fTime % 10 == 0)
	//			BehaviorFunction();*/

	//	/*	if (m_fTime >= 10.f)
	//			BehaviorFunction();*/

	//		if (m_fTime >= 1.f)
	//			MonsterState(STATEID::IDLE);
	//	}
	//}
}

void CMonster1::OnLine()
{
	float fY = m_tInfo.vPos.y;
	bool bColl = CLineMgr::GetInstance()->LineCollision(m_tInfo.vPos.x, &fY);
	bool bColl2 = CStage2LineMgr::GetInstance()->LineCollision(m_tInfo.vPos.x, &fY);

	if ((!m_bIsJump && bColl) || (!m_bIsJump && bColl2))	// 점프 중이 아니지만 지면에 충돌했을 때
		m_tInfo.vPos.y = fY;
}
