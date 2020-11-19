#pragma once

class CObj;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionSphere(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionSphere_AttackMonster(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionSphere_SpecialAttackMonster(OBJLIST& dstLst, OBJLIST& srcLst);

	static void CollisionRectEX_Door(OBJLIST& dstLst, OBJLIST& srcLst);

public:
	static void CollisionRectEX(OBJLIST& dstLst, OBJLIST& srcLst);
	static void CollisionPlayerProp(OBJLIST& dstLst, OBJLIST& srcLst);				//	�������� �� ������ �÷��̾� �浹ó�� �Լ�

private:
	static bool CheckRect(CObj* pDst, CObj* pSrc, float* pMoveX, float* pMoveY);
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
};

