#include "stdafx.h"
#include "Stage2_1.h"

#include "Player.h"

#include "Monster1.h"
#include "Monster1Left.h"

#include "Monster3.h"
#include "LeftMonster3.h"

#include "StreetLamp2.h"
#include "StreetLight2.h"
#include "OilTank.h"
#include "FlowerPot.h"

CStage2_1::CStage2_1()
	:m_pPlayer(nullptr), bIsCreate(false),pMonster(nullptr)
{
	// 웨이브 1
	pMonster1 = nullptr;
	pMonster2 = nullptr;

	pLeftMonster = nullptr;
	pLeftMonster1 = nullptr;
	pLeftMonster2 = nullptr;

	// 웨이브 2
	pMonster3 = nullptr;
	pMonster4 = nullptr;
	pMonster5 = nullptr;

	pLeftMonster3 = nullptr;
	pLeftMonster4 = nullptr;
	pLeftMonster5 = nullptr;

	// 웨이브 3
	pMonster6 = nullptr;
	pMonster7 = nullptr;
	pMonster8 = nullptr;
	pMonster9 = nullptr;


	pLeftMonster6 = nullptr;
	pLeftMonster7 = nullptr;
	pLeftMonster8 = nullptr;
	

	bIsCreate1 = false;
	bIsCreate2 = false;
}

CStage2_1::~CStage2_1()
{
	Release();
}

HRESULT CStage2_1::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;


	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Stage2Background.png", L"STage2Background", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage 1-1 Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}


	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(m_pPlayer)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(m_pPlayer, OBJ_PLAYER);

	if (FAILED(CStage2Camera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Camera Init Failed");
		return E_FAIL;
	}


	//////////////////////////////////	프 랍	 //////////////////////////////////////////////////

	CObj* pStreetLamp = nullptr;
	if (FAILED(CAbstractFactory<CStreetLamp2>::CreateObj(pStreetLamp,D3DXVECTOR3(-100.f,5.f,0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pStreetLamp, OBJ_FRONTLAYER);

	CObj* pStreetLamp2 = nullptr;
	if (FAILED(CAbstractFactory<CStreetLamp2>::CreateObj(pStreetLamp2, D3DXVECTOR3(1700.f, 5.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pStreetLamp2, OBJ_FRONTLAYER);

	CObj* pStreetLamp3 = nullptr;
	if (FAILED(CAbstractFactory<CStreetLamp2>::CreateObj(pStreetLamp3, D3DXVECTOR3(4450.f, 5.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pStreetLamp3, OBJ_FRONTLAYER);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CObj* pLight = nullptr;
	if (FAILED(CAbstractFactory<CStreetLight2>::CreateObj(pLight, D3DXVECTOR3(-50.f, 60.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	pLight = nullptr;
	if (FAILED(CAbstractFactory<CStreetLight2>::CreateObj(pLight, D3DXVECTOR3(1750.f, 60.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	pLight = nullptr;
	if (FAILED(CAbstractFactory<CStreetLight2>::CreateObj(pLight, D3DXVECTOR3(4500.f, 60.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	CObj* pOilTank = nullptr;
	if (FAILED(CAbstractFactory<COilTank>::CreateObj(pOilTank, D3DXVECTOR3(1950.f, 0.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pOilTank, OBJ_FRONTLAYER);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	CObj* pFlowerPot = nullptr;
	if (FAILED(CAbstractFactory<CFlowerPot>::CreateObj(pFlowerPot, D3DXVECTOR3(1950.f, -100.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pFlowerPot, OBJ_FRONTLAYER);

	//////////////////////////////////	웨이브 1	 //////////////////////////////////////////////////

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster, D3DXVECTOR3(4000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster1, D3DXVECTOR3(4400.f, 500.f, 0.f))))
		return E_FAIL;



	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster, D3DXVECTOR3(2000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster1, D3DXVECTOR3(1500.f, 500.f, 0.f))))
		return E_FAIL;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////	웨이브 2	 //////////////////////////////////////////////////

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster2, D3DXVECTOR3(4000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster3, D3DXVECTOR3(4400.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster4, D3DXVECTOR3(4800.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster5, D3DXVECTOR3(5000.f, 450.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster2, D3DXVECTOR3(2000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster3, D3DXVECTOR3(1500.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster4, D3DXVECTOR3(1000.f, 500.f, 0.f))))
		return E_FAIL;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////	웨이브 3	 //////////////////////////////////////////////////


	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster6, D3DXVECTOR3(4000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster7, D3DXVECTOR3(4400.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1>::CreateObj(pMonster8, D3DXVECTOR3(4800.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster9, D3DXVECTOR3(5600.f, 450.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster10, D3DXVECTOR3(5600.f, 450.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster5, D3DXVECTOR3(2000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CMonster1Left>::CreateObj(pLeftMonster6, D3DXVECTOR3(1500.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CLeftMonster3>::CreateObj(pLeftMonster7, D3DXVECTOR3(1000.f, 500.f, 0.f))))
		return E_FAIL;

	if (FAILED(CAbstractFactory<CLeftMonster3>::CreateObj(pLeftMonster8, D3DXVECTOR3(500.f, 450.f, 0.f))))
		return E_FAIL;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CStage2LineMgr::GetInstance()->Initialize();

	CTutorialSound::GetInstance()->Initialize(g_hWnd);

	return S_OK;
}

void CStage2_1::Update()
{
	CObjMgr::GetInstance()->Update();
	CStage2Camera::GetInstance()->Update();

	if (m_pPlayer->GetInfo().vPos.x >= 2500.f && !bIsCreate)
	{
		CObjMgr::GetInstance()->AddObject(pMonster, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster1, OBJ_MONSTER);

		CObjMgr::GetInstance()->AddObject(pLeftMonster, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pLeftMonster1, OBJ_MONSTER);

		bIsCreate = true;
	}

	if (pMonster1->GetData().iHp <= 0 && !bIsCreate1)
	{
		CObjMgr::GetInstance()->AddObject(pMonster3, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster4, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster5, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster6, OBJ_MONSTER);

		CObjMgr::GetInstance()->AddObject(pLeftMonster2, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pLeftMonster3, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pLeftMonster4, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pLeftMonster5, OBJ_MONSTER);

		bIsCreate1 = true;
	}

	if (pMonster4->GetData().iHp <= 0 && !bIsCreate2)
	{
		CObjMgr::GetInstance()->AddObject(pMonster7, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster8, OBJ_MONSTER);
		CObjMgr::GetInstance()->AddObject(pMonster9, OBJ_MONSTER);


		bIsCreate2 = true;
	}
}

void CStage2_1::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_2);

		return;
	}

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage2_1::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"DiaBack");

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
		&D3DXVECTOR3((float)1950.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"STage2Background");

	D3DXMATRIX matScale2, matRotZ2, matTrans2, matWorld2;

	D3DXMatrixScaling(&matScale2, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans2, WINCX - CScrollMgr::GetScroll().x, WINCY - CScrollMgr::GetScroll().y, 0.f);

	matWorld2 = matScale2 * matTrans2;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	// 이미지의 중점 구하기.
	int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX2, (float)1350.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();


	CStage2Camera::GetInstance()->SetTransform();
}

void CStage2_1::Release()
{
	//CObjMgr::GetInstance()->Release();
	//CStage2Camera::GetInstance()->Release();

	CTextureMgr::GetInstance()->DestroyInstance();
	CStage2Camera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CStage2LineMgr::GetInstance()->DestroyInstance();
}
