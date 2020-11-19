#include "stdafx.h"
#include "StageBoss.h"
#include "BossAttackCollider.h"

CStageBoss::CStageBoss()
	:m_fTime(0.f)
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime1, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime2, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CStageBoss::~CStageBoss()
{
	Release();
}

HRESULT CStageBoss::Initialize()
{
	m_wstrObjKey = L"Stage1_Boss";
	m_wstrStateKey = L"Right_Idle";

	//m_tInfo.vPos = D3DXVECTOR3(500.f, 350.f, 0.f);

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 14.f;

	m_tInfo.vSize = { 150.f,280.f,0.f };

	m_fSpeed = 0.1f;
	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	m_tData.iHp = 10;

	CTimeMgr::GetInstance()->InitTime();

	return S_OK;
}

int CStageBoss::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_fTime += CTimeMgr::GetInstance()->GetTime();


	if (nullptr != m_pTarget)
	{
		// �󽺿� Ÿ���� �̷�� �ﰢ���� ������ ���Ѵ�.
		// ��������! �ݵ�� Ÿ�ٿ������� ������ �Ѵ�!
		float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x;
		//float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
		float d = sqrtf(w * w);

		// �ﰢ���� �ﰢ�� �̿��Ͽ� ���ΰ��� ����.
		// ���ﰢ�Լ��� ���ΰ��� �������� ��ȯ�Ѵ�.
		m_fAngle = acosf(w / d);

		// acosf�� ���� �� �ִ� ���� ������ 0 ~ 180��.
		// ����, 180���� �Ѿ ������ �Ʒ��� ���� ����ó���� ���־���Ѵ�.
		if (m_tInfo.vPos.x < m_pTarget->GetInfo().vPos.x)
		{
			//m_fAngle = (2.f * PI) - m_fAngle;
			m_fAngle *= -1.f;
		}


		// ���� ������� ���͸� �̵�.

		if (m_fTime >= 3.f && m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x >= 200.f)
		{
			m_wstrStateKey = L"Right_Run";

			//m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 37.f;

			m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
		}

		else if((m_fTime >= 3.f && m_fTime <= 8.f)&& m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x >= 150.f)
		{
			m_wstrStateKey = L"Right_Kicking";

			m_tFrame.fMax = 10.f;
			m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() *0.5f;

			CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CBossAttackCollider>(), OBJID::OBJ_ENEMYATTACK);
		}
		
		else if ((m_fTime >= 10.f && m_fTime <= 15.f))
		{
			m_wstrStateKey = L"Right_Idle";

			m_tFrame.fMax = 14.f;
		}

		else if ((m_fTime >= 17.f && m_fTime <= 20.f))
		{
			m_wstrStateKey = L"Right_DipDown";

			m_tFrame.fMax = 10.f;

			m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() *0.5f;

			CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CBossAttackCollider>(), OBJID::OBJ_ENEMYATTACK);
		}

		else if ((m_fTime >= 22.f && m_fTime <= 28.f))
		{
			m_wstrStateKey = L"Right_Idle";

			m_tFrame.fMax = 14.f;
		}

		else if ((m_fTime >= 30.f && m_fTime <= 38.f))
		{
			m_wstrStateKey = L"Shooting";

			m_tFrame.fMax = 7.f;

			m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() *0.5f;

			CObjMgr::GetInstance()->AddObject(CreateAttackCollider<CBossAttackCollider>(), OBJID::OBJ_ENEMYATTACK);
		}

		else
		{
			m_wstrStateKey = L"Right_Idle";

			m_tFrame.fMax = 14.f;
		}

		if (m_tData.iHp >= 0 && m_tData.iHp <= 2)
		{
			m_tInfo.vPos.y = 450.f;

			m_wstrStateKey = L"Right_Damaged";

			m_tFrame.fMax = 7.f;
			//m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::GetInstance()->GetTime() *0.5f;
			//if (m_tFrame.fFrame > m_tFrame.fMax)
			//{
			//	m_wstrStateKey = L"Right_Run";

			//	//m_tFrame.fFrame = 0.f;
			//	m_tFrame.fMax = 37.f;

			//	m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
			//}
		}

		if (m_tData.iHp <= 0)
		{
			/*m_tInfo.vPos.y = 400.f;

			m_wstrStateKey = L"Mob3_Die";

			m_tFrame.fMax = 20.f;*/

			/*if (m_tFrame.fMax == m_tFrame.fFrame)
			{
				m_tFrame.fFrame = 19.f;
			}*/

			m_bIsDead = true;
		}

		/*if (m_tFrame.fFrame >= m_tFrame.fMax)
		{
			if (m_wstrStateKey == L"Mob3_Die")
				return DEAD_OBJ;
		}*/
	}


	return NO_EVENT;
}

void CStageBoss::LateUpdate()
{
	CObj::MoveFrame();
}

void CStageBoss::Render()
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

void CStageBoss::Release()
{
}
