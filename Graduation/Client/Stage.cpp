#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

HRESULT CStage::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	CObj* pTerrain = nullptr;
	if (FAILED(CAbstractFactory<CTerrain>::CreateObj(pTerrain)))
		return E_FAIL;

	CObj* pPlayer = nullptr;
	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;	

	//CObjMgr::GetInstance()->AddObject(pTerrain, OBJ_TERRAIN);
	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	return S_OK;
}

void CStage::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CStage::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage::Render()
{
	CObjMgr::GetInstance()->Render();
}

void CStage::Release()
{
}
