#include "stdafx.h"
#include "Monster2.h"
#include "AnimEffect.h"
#include "NonAnimEffect.h"
#include "Bullet.h"

CMonster2::CMonster2()
	:m_pTarget(nullptr), m_fTime(0.f), iShootCnt(0), m_fRestTime(0.f)
{
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime1, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_OldTime2, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}

CMonster2::~CMonster2()
{
	Release();
}

HRESULT CMonster2::Initialize()
{
	m_wstrObjKey = L"Enemy2";
	m_wstrStateKey = L"Idle";

	////m_tInfo.vPos = D3DXVECTOR3(500.f, 400.f, 0.f);

	//m_tFrame.fFrame = 0.f;

	m_tInfo.vSize = { 150.f,280.f,0.f };

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 13.f;

	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime1);
	QueryPerformanceCounter(&m_OldTime2);

	// QueryPerformanceFrequency: CPU의 진동 주기를 얻어오는 함수. 1초에 몇번 진동하는가!
	QueryPerformanceFrequency(&m_CpuTick);

	m_tData.iHp = 2;

	return S_OK;
}

int CMonster2::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	//CTimeMgr::GetInstance()->InitTime();

	m_tInfo.matWorld = matScale * matTrans;

	//ShootingTerm();

	m_fTime = ShootingTerm();

	if (m_fTime >= 0.1f && iShootCnt < 3)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_BULLET);

		++iShootCnt;
	}

	if (m_fTime >= 3.2f && m_fTime <= 6.f)
	{
		m_wstrStateKey = L"Idle";

		m_tFrame.fMax = 13.f;
	}

	if (m_fTime >= 7.f && iShootCnt < 6)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);
	
		++iShootCnt;
	}

	if (m_fTime >= 9.2f && m_fTime <= 12.f)
	{
		m_wstrStateKey = L"Idle";

		m_tFrame.fMax = 13.f;
	}

	if (m_fTime >= 13.f && iShootCnt < 9)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);

		++iShootCnt;
	}

	if (m_fTime >= 15.2f && m_fTime <= 18.f)
	{
		m_wstrStateKey = L"Idle";

		m_tFrame.fMax = 13.f;
	}

	if (m_fTime >= 19.f && iShootCnt < 12)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);

		++iShootCnt;
	}

	if (m_fTime >= 21.2f && m_fTime <= 24.f)
	{
		m_wstrStateKey = L"Idle";

		m_tFrame.fMax = 13.f;
	}

	if (m_fTime >= 25.f && iShootCnt < 15)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);

		++iShootCnt;
	}

	if (m_fTime >= 27.2f && m_fTime <= 30.f)
	{
		m_wstrStateKey = L"Idle";

		m_tFrame.fMax = 13.f;
	}

	if (m_fTime >= 31.f && iShootCnt < 18)
	{
		m_wstrStateKey = L"Attack";

		m_tFrame.fMax = 5.f;

		CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);

		++iShootCnt;
	}

	//m_wstrStateKey = L"Idle";

	//m_tFrame.fMax = 13.f;
	
	//if (m_fTime >= 2.f && (iShootCnt >= 0 && iShootCnt < 3))
	//{
	//	m_wstrStateKey = L"Attack";

	//	m_tFrame.fMax = 5.f;
	//	/*m_tFrame.fMax = 5.f;

	//	m_tFrame.fFrame += m_tFrame.fMax * m_fTime;

	//	if (m_tFrame.fFrame > m_tFrame.fMax)
	//	{
	//		m_tFrame.fFrame = 0.f;
	//		m_tFrame.fMax = 5.f;
	//	}*/

	//	CObjMgr::GetInstance()->AddObject(CreateBullet<CBullet>(), OBJID::OBJ_ENEMYATTACK);

	//	++iShootCnt;

	//	m_fTime = 0.f;

	//	if (iShootCnt == 3)
	//	{
	//		RestTerm();
	//	}
	//}

	if (m_tData.iHp <= 1)
	{
		m_wstrStateKey = L"Damaged";

		//m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 6.f;

		m_tInfo.vPos.y = 450.f;
	}

	if (m_tData.iHp <= 0)
	{
		m_wstrStateKey = L"Die";

		//m_tFrame.fFrame = 0.f;
		m_tFrame.fMax = 11.f;

		m_bIsDead = true;

		m_tInfo.vPos.y = 450.f;
	}

	return NO_EVENT;
}


void CMonster2::LateUpdate()
{
	CObj::MoveFrame();
}

void CMonster2::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(
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
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), &D3DXVECTOR3(0.f, 0.f, 0.f), D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CMonster2::Release()
{
}

float CMonster2::ShootingTerm()
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

float CMonster2::RestTerm()
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
