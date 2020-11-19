#include "stdafx.h"
#include "Monster3.h"


CMonster3::CMonster3()
	:m_pTarget(nullptr)
{
}


CMonster3::~CMonster3()
{
	Release();
}

HRESULT CMonster3::Initialize()
{

	m_wstrObjKey = L"Enemy3";
	m_wstrStateKey = L"Idle";

	m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 10.f;


	m_tInfo.vSize = { 150.f,280.f,0.f };

	m_fSpeed = 0.1f;

	m_tData.iHp = 5;

	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	return S_OK;
}

int CMonster3::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	if (nullptr != m_pTarget)
	{
		// 몬스와 타겟을 이루는 삼각형의 세변을 구한다.
		// 순서유의! 반드시 타겟에서부터 뺄샘을 한다!
		float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x ;
		float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
		float d = sqrtf(w * w + h * h);

		// 삼각형의 삼각비를 이용하여 끼인각을 얻어낸다.
		// 역삼각함수는 끼인각을 라디안으로 반환한다.
		m_fAngle = acosf(w / d);

		// acosf이 구할 수 있는 각도 범위는 0 ~ 180도.
		// 따라서, 180도를 넘어설 때에는 아래와 같이 예외처리를 해주어야한다.
		if (m_tInfo.vPos.x < m_pTarget->GetInfo().vPos.x)
		{
			//m_fAngle = (2.f * PI) - m_fAngle;
			m_fAngle *= -1.f;
		}

		// 구한 각도대로 몬스터를 이동.

		if (m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x >= 200.f)
		{
			m_wstrStateKey = L"Run";

			m_tFrame.fMax = 37.f;

			m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
		}

		if(m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x <= 200.f)
		{
			m_wstrStateKey = L"Attack";

			//m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 17.f;

			m_tInfo.vPos.y = 500.f;
		}


		if (m_tData.iHp == 1)
		{
			m_wstrStateKey = L"Damaged";

			//m_tFrame.fFrame = 0.f;
			m_tFrame.fMax = 10.f;

			m_tInfo.vPos.y = 500.f;
		}

		if (m_tData.iHp <= 0)
		{
			//m_wstrStateKey = L"Mob3_Die";

			////m_tFrame.fFrame = 0.f;
			//m_tFrame.fMax = 20.f;

			m_bIsDead = true;
		}
	}



	return NO_EVENT;
}

void CMonster3::LateUpdate()
{
	CObj::MoveFrame();
}

void CMonster3::Render()
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

void CMonster3::Release()
{
}
