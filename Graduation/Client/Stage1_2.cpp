#include "stdafx.h"
#include "Stage1_2.h"
#include "Player.h"

#include "BackLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"
#include "FrontLayer.h"

#include "BackLight.h"
#include "Monster1.h"
#include "Monster2.h"

CStage1_2::CStage1_2()
	:bIsNext(false), fAlphaCnt(0.f)
{
}

CStage1_2::~CStage1_2()
{
	Release();
}

HRESULT CStage1_2::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	//if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene1.png", L"Background", TEX_SINGLE)))
	//{
	//	ERR_MSG(L"Stage 1-1 Image Insert Failed!!!");
	//	return E_FAIL;
	//}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene1.png", L"Background", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage 1-2 Image Insert Failed!!!");
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


	CObj* pSecondLayer = nullptr;
	/*if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(904.f, 520.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);*/

	if (FAILED(CAbstractFactory<CSecondLayer>::CreateObj(pSecondLayer, D3DXVECTOR3(1000.f, 550.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pSecondLayer, OBJ_SECONDLAYER);

	CObj* pMonster = nullptr;
	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(1500.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(2000.f, 450.f, 0.f))))
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

	//CObj* pMonster2 = nullptr;
	//if (FAILED(CAbstractFactory<CMonster2>::CreateObj(pMonster2, D3DXVECTOR3(1800.f, 450.f, 0.f))))
	//	return E_FAIL;
	//CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	CObj* pFrontLayer = nullptr;
	if (FAILED(CAbstractFactory<CFrontLayer>::CreateObj(pFrontLayer, D3DXVECTOR3(525.f, 500.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pFrontLayer, OBJ_FRONTLAYER);

	CObj* pLight = nullptr;
	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(525.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	if (FAILED(CAbstractFactory<CBackLight>::CreateObj(pLight, D3DXVECTOR3(1500.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	//	지면(라인)
	CLineMgr::GetInstance()->Initialize();

	return S_OK;
}

void CStage1_2::Update()
{
	CObjMgr::GetInstance()->Update();
	CCStageCamera::GetInstance()->Update();
}

void CStage1_2::LateUpdate()
{
	//if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	//{
	//	bIsNext = true;
	//}

	//if (bIsNext == true)
	//{
	//	fAlphaCnt += 0.05f;
	//	//CObjMgr::GetInstance()->AddObject(pFade, OBJ_FADE);

	//	if (fAlphaCnt >= 255.f)
	//	{
	//		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_3);
	//		return;
	//	}

	//	//CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_2);

	//	return;
	//}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_3);
		return;
	}

	CObjMgr::GetInstance()->LateUpdate();

}

void CStage1_2::Render()
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
	/*int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;*/

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)2000.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

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

void CStage1_2::Release()
{
	CTextureMgr::GetInstance()->Release();
	CCStageCamera::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();
	CLineMgr::GetInstance()->Release();

	CTextureMgr::GetInstance()->DestroyInstance();
	CCStageCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
}

