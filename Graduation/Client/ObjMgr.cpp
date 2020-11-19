#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

IMPLEMENT_SINGLETON(CObjMgr)

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
	Release();
}

//CObj * CObjMgr::GetTarget(CObj * pSrc, OBJID eID)
//{
//	if (m_ObjLst[eID].empty())
//		return nullptr;
//
//	CObj* pTarget = m_ObjLst[eID].front();
//	float fDist = CMathMgr::CalcDistance(pTarget, pSrc);
//
//	for (auto& pObj : m_ObjLst[eID])
//	{
//		float fCmpDist = CMathMgr::CalcDistance(pObj, pSrc);
//
//		if (fDist > fCmpDist)
//		{
//			pTarget = pObj;
//			fDist = fCmpDist;
//		}
//	}
//
//	return pTarget;
//}

void CObjMgr::AddObject(CObj * pObject, OBJID eID)
{
	m_ObjLst[eID].push_back(pObject);
}

void CObjMgr::Update()
{
	for (OBJLIST& objLst : m_ObjLst)
	{
		OBJITER iter_begin = objLst.begin();
		OBJITER iter_end = objLst.end();

		for (; iter_begin != iter_end;)
		{
			int iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete(*iter_begin);
				iter_begin = objLst.erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}
}

void CObjMgr::LateUpdate()
{
	for (OBJLIST& objLst : m_ObjLst)
	{
		for (CObj*& pObj : objLst)
			pObj->LateUpdate();
	}
	CCollisionMgr::CollisionSphere_AttackMonster(m_ObjLst[OBJ_MONSTER], m_ObjLst[OBJ_BULLET]);
	CCollisionMgr::CollisionSphere_AttackMonster(m_ObjLst[OBJ_PLAYER], m_ObjLst[OBJ_ENEMYATTACK]);

	CCollisionMgr::CollisionSphere_SpecialAttackMonster(m_ObjLst[OBJ_MONSTER], m_ObjLst[OBJ_SPECIALATTACK]);
	CCollisionMgr::CollisionRectEX_Door(m_ObjLst[OBJ_DOOR], m_ObjLst[OBJ_PLAYER]);
	CCollisionMgr::CollisionSphere_SpecialAttackMonster(m_ObjLst[OBJ_CAGEDOOR], m_ObjLst[OBJ_SPECIALATTACK]);

	//CCollisionMgr::CollisionSphere(m_ObjLst[OBJ_SECONDLAYER], m_ObjLst[OBJ_PLAYER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[OBJ_SECONDLAYER], m_ObjLst[OBJ_PLAYER]);
	//CCollisionMgr::CollisionRect(m_ObjLst[OBJ_SECONDLAYER], m_ObjLst[OBJ_MONSTER]);
	CCollisionMgr::CollisionRectEX(m_ObjLst[OBJ_CAGEDOOR], m_ObjLst[OBJ_PLAYER]);
}

void CObjMgr::Render()
{
	for (OBJLIST& objLst : m_ObjLst)
	{
		for (CObj*& pObj : objLst)
			pObj->Render();
	}
}

void CObjMgr::Release()
{
	for (OBJLIST& objLst : m_ObjLst)
	{
		for_each(objLst.begin(), objLst.end(), SafeDelete<CObj*>);
		objLst.clear();
	}
}
