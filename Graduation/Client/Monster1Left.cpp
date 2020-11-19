#include "stdafx.h"
#include "Monster1Left.h"


CMonster1Left::CMonster1Left()
	:m_fSpeed(0.f), m_pTarget(nullptr)
{
}


CMonster1Left::~CMonster1Left()
{
	Release();
}

HRESULT CMonster1Left::Initialize()
{
	/*m_wstrObjKey = L"Enemy1";
	m_wstrStateKey = L"Idle";*/

	//m_tInfo.vPos = D3DXVECTOR3(400.f, 400.f, 0.f);

	m_tInfo.vSize = { 150.f,280.f,0.f };

	/*m_tFrame.fFrame = 0.f;
	m_tFrame.fMax = 10.f;*/

	m_tFrame.fFrame = 0.f;

	m_tData.iHp = 3;

	m_fSpeed = 0.1f;

	m_pTarget = CObjMgr::GetInstance()->GetPlayer();

	return S_OK;
}

int CMonster1Left::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);

	m_tInfo.matWorld = matScale * matTrans;

	m_wstrObjKey = L"Enemy1";
	m_wstrStateKey = L"LeftIdle";

	m_tFrame.fMax = 10.f;

	//m_pTarget = CObjMgr::GetInstance()->GetTarget(this, OBJID::OBJ_PLAYER);

	if (nullptr != m_pTarget)
	{
		// �󽺿� Ÿ���� �̷�� �ﰢ���� ������ ���Ѵ�.
		// ��������! �ݵ�� Ÿ�ٿ������� ������ �Ѵ�!
		float w = m_pTarget->GetInfo().vPos.x - m_tInfo.vPos.x;
		float h = m_pTarget->GetInfo().vPos.y - m_tInfo.vPos.y;
		float d = sqrtf(w * w + h * h);

		// �ﰢ���� �ﰢ�� �̿��Ͽ� ���ΰ��� ����.
		// ���ﰢ�Լ��� ���ΰ��� �������� ��ȯ�Ѵ�.
		m_fAngle = acosf(w / d);

		// acosf�� ���� �� �ִ� ���� ������ 0 ~ 180��.
		// ����, 180���� �Ѿ ������ �Ʒ��� ���� ����ó���� ���־���Ѵ�.
		if (m_tInfo.vPos.x < m_pTarget->GetInfo().vPos.x)
		{
			m_fAngle = (2.f * PI) - m_fAngle;
		}

		// ���� ������� ���͸� �̵�.

		if (m_tInfo.vPos.x - m_pTarget->GetInfo().vPos.x <= -200.f)
		{
			m_wstrStateKey = L"LeftRun";

			m_tFrame.fMax = 31.f;

			m_tInfo.vPos.x += cosf(m_fAngle) * m_fSpeed;
		}

		else
		{
			m_wstrStateKey = L"LeftAttack";

			m_tFrame.fMax = 41.f;
		}

		if (m_tData.iHp == 1)
		{
			m_wstrStateKey = L"LeftDamaged";

			m_tFrame.fMax = 17.f;

			//m_tInfo.vPos.y = 450.f;
		}

		if (m_tData.iHp <= 0)
		{
			m_wstrStateKey = L"Die";

			m_tFrame.fMax = 11.f;

			m_bIsDead = true;

			//m_tInfo.vPos.y = 450.f;
		}
	}

	return NO_EVENT;
}

void CMonster1Left::LateUpdate()
{
	CObj::MoveFrame();
}

void CMonster1Left::Render()
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

void CMonster1Left::Release()
{
}
