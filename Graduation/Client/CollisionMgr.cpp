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
			// IntersectRect: 사각형 충돌을 판별하는 함수. 두 사각형이 충돌 됬을 때 TRUE 반환.
			// IntersectRect(겹친 영역을 기록할 사각형, 충돌 사각형1, 충돌 사각형2);
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
	// 밀려날 거리
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				// 파고든 깊이가 짧은 쪽으로 pSrc를 밀어내자!
				if (fMoveX > fMoveY) // y축으로 밀어냄
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
	// 밀려날 거리
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				if (fMoveX > fMoveY) // y축으로 밀어냄
				{
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.y < fY)
						fMoveY *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX, fY + fMoveY, 0.f));
				}

				else// x축으로 밀어냄
				{
					//cout << "충돌하는 프랍 위치: " << pDst->GetTerrainLst().back()->vPos.x << endl;
					float fX = pSrc->GetInfo().vPos.x;
					float fY = pSrc->GetInfo().vPos.y;

					if (pDst->GetInfo().vPos.x > fX)
						fMoveX *= -1.f;

					pSrc->SetPos(D3DXVECTOR3(fX + fMoveX, fY, 0.f));
				}
				// 파고든 깊이가 짧은 쪽으로 pSrc를 밀어내자!
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
	//		// IntersectRect: 사각형 충돌을 판별하는 함수. 두 사각형이 충돌 됬을 때 TRUE 반환.
	//		// IntersectRect(겹친 영역을 기록할 사각형, 충돌 사각형1, 충돌 사각형2);
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
	// 밀려날 거리
	float fMoveX = 0.f, fMoveY = 0.f;

	for (CObj*& pDst : dstLst)
	{
		for (CObj*& pSrc : srcLst)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				// 파고든 깊이가 짧은 쪽으로 pSrc를 밀어내자!
				if (fMoveX > fMoveY) // y축으로 밀어냄
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
	// 두 사각형의 가로, 세로 축 반지름의 합을 구한다.

	float fSumRadX = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;
	float fSumRadY = (pDst->GetInfo().vSize.y + pSrc->GetInfo().vSize.y) * 0.5f;

	// 두 사각형의 가로, 세로 중점의 거리를 구한다.
	// fabs(X): X의 절대 값을 구하는 함수. <cmath>에서 제공. 
	float fDistX = fabs(pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x);
	float fDistY = fabs(pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y);

	// 가로 축 반지름 합이 가로 축 거리보다 클 때와
	// 세로 축 반지름 합이 세로 축 거리보다 클 때
	if (fSumRadX > fDistX && fSumRadY > fDistY)
	{
		// 두 사각형이 겹쳤을 때 파고든 길이도 구한다.
		*pMoveX = fSumRadX - fDistX;
		*pMoveY = fSumRadY - fDistY;

		return true;
	}


	return false;
}

bool CCollisionMgr::CheckSphere(CObj * pDst, CObj * pSrc)
{
	// 원충돌
	// 두 원의 반지름 합이 두 원의 거리보다 커질 때 충돌!

	// 두 원의 반지름 합을 구한다.
	float fSumRad = (pDst->GetInfo().vSize.x + pSrc->GetInfo().vSize.x) * 0.5f;

	// 두 원의 거리를 구한다. 피타고라스를 이용.
	float w = pDst->GetInfo().vPos.x - pSrc->GetInfo().vPos.x;
	float h = pDst->GetInfo().vPos.y - pSrc->GetInfo().vPos.y;

	// sqrtf(X): X에 대한 제곱근을 구해주는 함수. <cmath>에서 제공한다.
	float fDist = sqrtf(w * w + h * h); // 피타고라스

	return (fSumRad >= fDist);
}