#include "stdafx.h"
#include "Stage1_3.h"
#include "Player.h"

#include "BackLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"
#include "FrontLayer.h"

#include "BackLight.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Monster3.h"

CStage1_3::CStage1_3()
{
}


CStage1_3::~CStage1_3()
{
	Release();
}

HRESULT CStage1_3::Initialize()
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
		ERR_MSG(L"Stage 1-3 Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pPlayer = nullptr;
	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	if (FAILED(CCStageCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Camera Init Failed");
		return E_FAIL;
	}

	//////////////////////////////////////	뒷배경 프랍 위치	///////////////////////////////////////////////

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


	//////////////////////////////////////	박스 프랍 위치	///////////////////////////////////////////////


	CObj* pSecondLayer = nullptr;
	/*if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(904.f, 520.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);*/

	if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(1300.f, 550.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);

	//////////////////////////////////////	와이어 위치	///////////////////////////////////////////////

	CObj* pWire = nullptr;

	if (FAILED(CAbstractFactory<CBackLayer>::CreateObj(pWire, D3DXVECTOR3(1400.f, 0.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pWire, OBJ_BACKLAYER);

	dynamic_cast<CBackLayer*>(pWire)->SetDrawID(1);

	CObj* pWire2 = nullptr;

	if (FAILED(CAbstractFactory<CBackLayer>::CreateObj(pWire2, D3DXVECTOR3(1850.f, 0.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pWire2, OBJ_BACKLAYER);

	dynamic_cast<CBackLayer*>(pWire2)->SetDrawID(1);

	CObj* pWire3 = nullptr;

	if (FAILED(CAbstractFactory<CBackLayer>::CreateObj(pWire3, D3DXVECTOR3(2250.f, 0.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pWire3, OBJ_BACKLAYER);

	dynamic_cast<CBackLayer*>(pWire3)->SetDrawID(1);

	//////////////////////////////////////	맨 앞 레이어 위치	///////////////////////////////////////////////

	CObj* pFrontLayer = nullptr;
	if (FAILED(CAbstractFactory<CFrontLayer>::CreateObj(pFrontLayer, D3DXVECTOR3(525.f, 500.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pFrontLayer, OBJ_FRONTLAYER);

	//////////////////////////////////////	몬스터 위치	///////////////////////////////////////////////

	CObj* pMonster = nullptr;
	/*if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(2000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);*/

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(2500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(3000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(3500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(4000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(4500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);
	/*if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1800.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1000.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);*/

	//CObj* pMonster2 = nullptr;
	//if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster2, D3DXVECTOR3(1800.f, 450.f, 0.f))))
	//	return E_FAIL;
	//CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	CObj* pMonster2 = nullptr;
	if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster2, D3DXVECTOR3(1800.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	//////////////////////////////////////	조명 위치	///////////////////////////////////////////////

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

	//	지면(라인)
	CLineMgr::GetInstance()->Initialize();

	return S_OK;
}

void CStage1_3::Update()
{
	CObjMgr::GetInstance()->Update();
	CCStageCamera::GetInstance()->Update();
}

void CStage1_3::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_BOSS);

		return;
	}

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage1_3::Render()
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

	CObjMgr::GetInstance()->Render();

	CCStageCamera::GetInstance()->SetTransform();
}

void CStage1_3::Release()
{
	CTextureMgr::GetInstance()->DestroyInstance();
	CCStageCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
}

