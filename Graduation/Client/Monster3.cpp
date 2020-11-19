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
		// �󽺿� Ÿ���� �̷�� �ﰢ���� ������ ���Ѵ�.
		// ��������! �ݵ�� Ÿ�ٿ������� ������ �Ѵ�!
		float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x ;
		float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
		float d = sqrtf(w * w + h * h);

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
