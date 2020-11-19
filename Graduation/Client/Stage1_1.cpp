#include "stdafx.h"
#include "Stage1_1.h"

#include "BackLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"
#include "FrontLayer.h"

#include "Door.h"
#include "Cage.h"
#include "FrontCage.h"
#include "CageDoor.h"

#include "Player.h"
#include "BackLight.h"

#include "Monster1.h"
#include "Monster2.h"
#include "Monster3.h"

#include "Mouse.h"

CStage1_1::CStage1_1()
	:m_pPlayer(nullptr), fAlphaCnt(0.f), bIsNext(false)
{
	pMonster = nullptr;
	pMonster2 = nullptr;

	bIsCreate = false;
}

CStage1_1::~CStage1_1()
{
	Release();
}

HRESULT CStage1_1::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene1.png", L"Background", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage 1-1 Image Insert Failed!!!");
		return E_FAIL;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(m_pPlayer/*, D3DXVECTOR3(-1000.f,450.f,0.f)*/)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(m_pPlayer, OBJ_PLAYER);

	if (FAILED(CCStageCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Camera Init Failed");
		return E_FAIL;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	CObj* pFirstLayer = nullptr;

	if (FAILED(CAbstractFactory<CFirstLayer>::CreateObj(pFirstLayer, D3DXVECTOR3(-200.f, 440.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pFirstLayer, OBJ_FIRSTLAYER);

	dynamic_cast<CFirstLayer*>(pFirstLayer)->SetDrawID(6);

	CObj* pFirstLayer2 = nullptr;

	if (FAILED(CAbstractFactory<CFirstLayer>::CreateObj(pFirstLayer2, D3DXVECTOR3(900.f, 430.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pFirstLayer2, OBJ_FIRSTLAYER);

	dynamic_cast<CFirstLayer*>(pFirstLayer2)->SetDrawID(7);

	//pFirstLayer = nullptr;

	//if (FAILED(CAbstractFactory<CFirstLayer>::CreateObj(pFirstLayer, D3DXVECTOR3(1000.f, 455.f, 0.f))))
	//	return E_FAIL;

	//CObjMgr::GetInstance()->AddObject(pFirstLayer, OBJ_FIRSTLAYER);


	//CObj* pSecondLayer = nullptr;
	//if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(904.f, 520.f, 0.f))))
	//	return E_FAIL;

	//CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);

	/*if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(1000.f, 550.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);*/

	/*if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(297.f, 520.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);*/



	/*CObj* pMonster2 = nullptr;
	if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster2)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	CObj* pMonster3 = nullptr;
	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster3)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster3, OBJ_MONSTER);*/

	//CObj* pStageBoss = nullptr;
	//if (FAILED(CAbstractFactory<CStageBoss>::CreateObj(pStageBoss)))
	//	return E_FAIL;
	//CObjMgr::GetInstance()->AddObject(pStageBoss, OBJ_MONSTER);

	/*CObj* pMonster = nullptr;
	if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster, D3DXVECTOR3(1000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);*/

	//////////////////////////////////////////////////// 1 - 1  몬 스 터 //////////////////////////////////////////////////////////////////////////



	//CObj* pMonster = nullptr;
	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(2000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(2500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(3000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	//////////////////////////////////////////////////// 1 - 2  몬 스 터 //////////////////////////////////////////////////////////////////////////

	

	/*if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(5500.f, 450.f, 0.f))))
		return E_FAIL;*/
	//CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	/*if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1800.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);*/

	/*if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);*/

	//CObj* pMonster2 = nullptr;
	/*if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster2, D3DXVECTOR3(5800.f, 450.f, 0.f))))
		return E_FAIL;*/
	//CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);


	//////////////////////////////////////////////////// 맨 앞 레이어 //////////////////////////////////////////////////////////////////////////


	/*CObj* pMonster3 = nullptr;
	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster3, D3DXVECTOR3(500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster3, OBJ_MONSTER);*/

	/*if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster2, D3DXVECTOR3(300.f, 400.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);*/

	CObj* pFrontLayer = nullptr;
	if (FAILED(CAbstractFactory<CFrontLayer>::CreateObj(pFrontLayer, D3DXVECTOR3(525.f, 1000.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pFrontLayer, OBJ_FRONTLAYER);

	/*CObj* pFrontLayer2 = nullptr;
	if (FAILED(CAbstractFactory<CFrontLayer>::CreateObj(pFrontLayer2, D3DXVECTOR3(550.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pFrontLayer2, OBJ_FRONTLAYER);*/

	//////////////////////////////////////////////////// 조 명 //////////////////////////////////////////////////////////////////////////

	CObj* pLight = nullptr;
	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(525.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(1500.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(2690.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	/*if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(4525.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(5500.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);*/

	/*if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(6690.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(8525.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(9500.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);*/

	//if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(6690.f, 500.f, 0.f))))
	//	return E_FAIL;
	//CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	////////////////////////////////////////////////////감 옥//////////////////////////////////////////////////////////////////////////

	/*CObj* pDoor = nullptr;
	CAbstractFactory<CDoor>::CreateObj(pDoor);
	CObjMgr::GetInstance()->AddObject(pDoor, OBJ_CAGEDOOR);*/

	CObj* pCage = nullptr;
	if (FAILED(CAbstractFactory<CCage>::CreateObj(pCage, D3DXVECTOR3(-800.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pCage, OBJ_CAGE);

	CObj* pFrontCage = nullptr;
	if (FAILED(CAbstractFactory<CFrontCage>::CreateObj(pFrontCage, D3DXVECTOR3(-810.f, 445.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pFrontCage, OBJ_FRONTLAYER);

	CObj* pCageDoor = nullptr;
	if (FAILED(CAbstractFactory<CCageDoor>::CreateObj(pCageDoor, D3DXVECTOR3(-600.f, 445.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pCageDoor, OBJ_CAGEDOOR);

	//	지면(라인)
	CLineMgr::GetInstance()->Initialize();
	
	//CSoundMgr::GetInstance()->Initialize(g_hWnd);

	ShowCursor(true);


	//CObjMgr::GetInstance()->AddObject(pTerrain, OBJ_TERRAIN);

	return S_OK;
}

void CStage1_1::Update()
{
	CObjMgr::GetInstance()->Update();
	CCStageCamera::GetInstance()->Update();

	//if (m_pPlayer->GetInfo().vPos.x >= 4500.f)
	//{
	//	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);
	//	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	//	//bIsCreate = true;
	//}
}

void CStage1_1::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_2);
		return;
	}

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage1_1::Render()
{
	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"DiaBack");

	D3DXMATRIX matScale2, matRotZ2, matTrans2, matWorld2;

	D3DXMatrixScaling(&matScale2, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans2, 500.f - CScrollMgr::GetScroll().x, 400.f, 0.f);

	matWorld2 = matScale2 * matTrans2;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	// 이미지의 중점 구하기.
	int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX2, (float)iCenterY2, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Background");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	
	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;
	
	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)2000.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	//const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"Background");

	//D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	//D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);

	//D3DXMatrixTranslation(&matTrans3, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	//matWorld3 = matScale3 * matTrans3;

	////// SetTransform: 행렬을 반영하는 함수.
	//CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	//// 이미지의 중점 구하기.
	//int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	//int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	////// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//	nullptr /*출력할 이미지 영역의 RECT*/,
	//	&D3DXVECTOR3((float)-1510.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//	nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	////// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//	nullptr /*출력할 이미지 영역의 RECT*/,
	//	&D3DXVECTOR3((float)-5000.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//	nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();

	CCStageCamera::GetInstance()->SetTransform();


	//const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	//D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	//D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);
	//D3DXMatrixTranslation(&matTrans3, 500.f, 300.f, 0.f);

	//matWorld3 = matScale3 * matTrans3;

	//CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	////// 이미지의 중점 구하기.
	//int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	//int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	////// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo3->pTexture,
	//	nullptr /*출력할 이미지 영역의 RECT*/,
	//	&D3DXVECTOR3((float)iCenterX3, (float)iCenterY3, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//	nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB((int)fAlphaCnt, 255, 255, 255));

}

void CStage1_1::Release()
{
	CTextureMgr::GetInstance()->Release();
	CCStageCamera::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();
	CLineMgr::GetInstance()->Release();
	//CSoundMgr::GetInstance()->Shutdown();

	//CSoundMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CCStageCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
} 
