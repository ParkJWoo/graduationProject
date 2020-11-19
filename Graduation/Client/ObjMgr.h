#pragma once

class CObj;
class CObjMgr
{
	DECLARE_SINGLETON(CObjMgr)

private:
	CObjMgr();
	~CObjMgr();

public:
	CObj* GetTerrain() { return m_ObjLst[OBJ_TERRAIN].front(); }
	CObj* GetPlayer() { return m_ObjLst[OBJ_PLAYER].front(); }
	CObj* GetButton() { return m_ObjLst[OBJ_BUTTON].back(); }
	//CObj* GetTarget(CObj* pSrc, OBJID eID);

public:
	void AddObject(CObj* pObject, OBJID eID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	OBJLIST	m_ObjLst[OBJ_END];
};

