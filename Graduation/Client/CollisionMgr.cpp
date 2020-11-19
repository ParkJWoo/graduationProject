#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			RECT rc = {};
			// IntersectRect: �簢�� �浹�� �Ǻ��ϴ� �Լ�. �� �簢���� �浹 ���� �� TRUE ��ȯ.
			// IntersectRect(��ģ ������ ����� �簢��, �浹 �簢��1, �浹 �簢��2);
			const RECT& dstRect = pDst->GetRect();
			const RECT& srcRect = pSrc->GetRect();

			if (IntersectRect(&rc, &dstRect, &srcRect))
			{
				pDst->IsDead();
				pSrc->IsDead();
			}
		}
	}
}

void CCollisionMgr::CollisionRectEX(OBJLIST & dstLst, OBJLIST & srcLst)
{
	// �з��� �Ÿ�
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				// �İ�� ���̰� ª�� ������ pSrc�� �о��!
				if (fMoveX > fMoveY) // y������ �о
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.y > fY)
						fMoveY *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX, fY + fMoveY, 0.f));
				}

				else
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.x > fX)
						fMoveX *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX + fMoveX, fY, 0.f));
				}
			}
		}
	}
}

void CCollisionMgr::CollisionPlayerProp(OBJLIST & dstLst, OBJLIST & srcLst)
{
	// �з��� �Ÿ�
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY) // y������ �о
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.y < fY)
						fMoveY *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX, fY + fMoveY, 0.f));
				}

				else// x������ �о
				{
					//cout << "�浹�ϴ� ���� ��ġ: " << pDst->GetTerrainLst().back()->vPos.x << endl;
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.x > fX)
						fMoveX *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX + fMoveX, fY, 0.f));
				}
				// �İ�� ���̰� ª�� ������ pSrc�� �о��!
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckSphere(pDst, pSrc))
			{
				pDst->IsDead();
			}
		}
	}
}

void CCollisionMgr::CollisionSphere_AttackMonster(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckSphere(pDst, pSrc))
			{
				pDst->SetDamage(pSrc->GetData().iDamage);
				pSrc->IsDead();
			}
		}
	}

	//for (CObj*& pDst : dstLst)
	//{
	//	for (CObj*& pSrc : srcLst)
	//	{
	//		RECT rc = {};
	//		// IntersectRect: �簢�� �浹�� �Ǻ��ϴ� �Լ�. �� �簢���� �浹 ���� �� TRUE ��ȯ.
	//		// IntersectRect(��ģ ������ ����� �簢��, �浹 �簢��1, �浹 �簢��2);
	//		const RECT& dstRect = pDst->GetRect();
	//		const RECT& srcRect = pSrc->GetRect();

	//		if (IntersectRect(&rc, &dstRect, &srcRect))
	//		{
	//			pDst->SetDamage(pSrc->GetData().iDamage);
	//			pSrc->IsDead();
	//		}
	//	}
	//}
}

void CCollisionMgr::CollisionSphere_SpecialAttackMonster(OBJLIST & dstLst, OBJLIST & srcLst)
{
	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckSphere(pDst, pSrc))
			{
				pDst->IsDead();
				pSrc->IsDead();
			}
		}
	}
}


void CCollisionMgr::CollisionRectEX_Door(OBJLIST & dstLst, OBJLIST & srcLst)
{
	// �з��� �Ÿ�
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				// �İ�� ���̰� ª�� ������ pSrc�� �о��!
				if (fMoveX > fMoveY) // y������ �о
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.y > fY)
						fMoveY *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX, fY + fMoveY, 0.f));
				}

				else
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.x > fX)
						fMoveX *= -1.f;

					pDst->SetDoor(true);
					//pSrc->SetPos(D3DXVECTOR3(fX + fMoveX, fY, 0.f));
				}
			}
		}
	}
}

bool CCollisionMgr::CheckRect(CObj * pDst, CObj * pSrc, float * pMoveX, float * pMoveY)
{
	// �� �簢���� ����, ���� �� �������� ���� ���Ѵ�.

	float fSumRadX = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;
	float fSumRadY = (pDst->GetInfo().vSize.y + pSrc->GetInfo().vSize.y) * 0.5f;

	// �� �簢���� ����, ���� ������ �Ÿ��� ���Ѵ�.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <cmath>���� ����. 
	float fDistX = fabs(pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x);
	float fDistY = fabs(pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y);

	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ����
	// ���� �� ������ ���� ���� �� �Ÿ����� Ŭ ��
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// �� �簢���� ������ �� �İ�� ���̵� ���Ѵ�.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}


	return false;
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	// ���浹
	// �� ���� ������ ���� �� ���� �Ÿ����� Ŀ�� �� �浹!

	// �� ���� ������ ���� ���Ѵ�.
	float fSumRad = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;

	// �� ���� �Ÿ��� ���Ѵ�. ��Ÿ��󽺸� �̿�.
	float w = pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x;
	float h = pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y;

	// sqrtf(X): X�� ���� �������� �����ִ� �Լ�. <cmath>���� �����Ѵ�.
	float fDist = sqrtf(w * w + h * h); // ��Ÿ���

	return (fSumRad >= fDist);
}