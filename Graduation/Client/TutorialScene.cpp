#include "stdafx.h"
#include "TutorialScene.h"
#include "Terrain.h"

#include "BackLayer.h"
#include "FirstLayer.h"
#include "SecondLayer.h"
#include "FrontLayer.h"

#include "Cage.h"

#include "TutorialDialog.h"

#include "Monster3.h"

#include "Player.h"
#include "Mouse.h"

#include "InvenIcon.h"
#include "Inventory.h"
#include "SettingIcon.h"
#include "HpBar.h"
#include "MpBar.h"

#include "Door.h"

CTutorialScene::CTutorialScene()
	:pPlayer(nullptr), m_pDoor(nullptr), m_pCage(nullptr)
{
}

CTutorialScene::~CTutorialScene()
{
	Release();
}

HRESULT CTutorialScene::Initialize()
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
		ERR_MSG(L"Tutorial Scene Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	/*CAbstractFactory<CHpBar>::CreateObj(pHpCase, D3DXVECTOR3(-370.f, -220.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpCase, OBJ_UI);

	CAbstractFactory<CHpBar>::CreateObj(pHpBar, D3DXVECTOR3(-310.f, -237.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pHpBar, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpBar, D3DXVECTOR3(-10.f, -160.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpBar2, D3DXVECTOR3(23.5f, -160.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpBar2, OBJ_UI);

	CAbstractFactory<CMpBar>::CreateObj(pMpCase, D3DXVECTOR3(13.f, -150.f, 0.f));
	CObjMgr::GetInstance()->AddObject(pMpCase, OBJ_UI);*/

	/*dynamic_cast<CHpBar*>(pHpCase)->SetImageKey(L"HPCase");
	dynamic_cast<CHpBar*>(pHpBar)->SetImageKey(L"HPBar");

	dynamic_cast<CMpBar*>(pMpCase)->SetImageKey(L"MPCase");
	dynamic_cast<CMpBar*>(pMpBar)->SetImageKey(L"MPBar");
	dynamic_cast<CMpBar*>(pMpBar2)->SetImageKey(L"MPBar");*/

	/*pInvenIcon = nullptr;
	CAbstractFactory<CInvenIcon>::CreateObj(pInvenIcon);
	CObjMgr::GetInstance()->AddObject(pInvenIcon, OBJ_UI);

	CObj* pSettingIcon = nullptr;
	CAbstractFactory<CSettingIcon>::CreateObj(pSettingIcon);
	CObjMgr::GetInstance()->AddObject(pSettingIcon, OBJ_UI);*/

	/*CObj* pDoor = nullptr;
	CAbstractFactory<CDoor>::CreateObj(pDoor);
	CObjMgr::GetInstance()->AddObject(pDoor, OBJ_DOOR);

	m_pDoor = dynamic_cast<CDoor*>(pDoor);

	CObj* pCage = nullptr;
	if (FAILED(CAbstractFactory<CCage>::CreateObj(pCage, D3DXVECTOR3(0.f,450.f,0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pCage, OBJ_BACKLAYER);

	m_pCage = dynamic_cast<CCage*>(pCage);*/

	/*pInventory = nullptr;
	CAbstractFactory<CInventory>::CreateObj(pInventory);
	CObjMgr::GetInstance()->AddObject(pInventory, OBJ_UI);*/

	/*CObj* pMonster2 = nullptr;
	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster2,D3DXVECTOR3(500.f, 350.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);

	if (FAILED(CAbstractFactory<CMonster3>::CreateObj(pMonster2, D3DXVECTOR3(300.f, 350.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMonster2, OBJ_MONSTER);*/


	if (FAILED(CCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Camera Init Failed");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Prop/Front/Front1.png", L"FrontProp", TEX_SINGLE)))
	{
		ERR_MSG(L"Front Prop Image Insert Failed!!!");
		return E_FAIL;
	}

	/*CObj* pTutorial = nullptr;
	CAbstractFactory<CTutorialDialog>::CreateObj(pTutorial);
	CObjMgr::GetInstance()->AddObject(pTutorial, OBJ_UI);*/

	CObj* pMouse = nullptr;

	/*if (FAILED(CAbstractFactory<CMouse>::CreateObj(pMouse, D3DXVECTOR3(-960.f, -225.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pMouse, OBJ_MOUSE);*/

	ShowCursor(true);

	CLineMgr::GetInstance()->Initialize();

	//CSoundMgr::GetInstance()->PlayBGM(L"Adam Levine - Lost Stars Lyrics.mp3");

	return S_OK;
}

void CTutorialScene::Update()
{
	CObjMgr::GetInstance()->Update();
	CCamera::GetInstance()->Update();

	/*D3DXMATRIX matPos;
	DATA		data;

	matPos = dynamic_cast<CPlayer*>(pPlayer)->GetInfo().matWorld;
	data = dynamic_cast<CPlayer*>(pPlayer)->GetData();

	CDataSubject::GetInstance()->AddData(PLAYER_DATA, &data);
	CDataSubject::GetInstance()->AddData(PLAYER_MATRIX, &matPos);
	CDataSubject::GetInstance()->Notify(PLAYER_MATRIX, &matPos);*/
}

void CTutorialScene::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_1);

		return;
	}

	/*if (m_pDoor->GetDoor() == true)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_1);

		return;
	}*/


	CObjMgr::GetInstance()->LateUpdate();
}

void CTutorialScene::Render()
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

	//// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)2000.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	//const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"FrontProp");

	////D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixTranslation(&matTrans, -700.f, 300.f, 0.f);

	//matWorld = matScale * matTrans;

	////// SetTransform: 행렬을 반영하는 함수.
	//CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	////// 이미지의 중점 구하기.
	//int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	//int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	////// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
	//	nullptr /*출력할 이미지 영역의 RECT*/,
	//	&D3DXVECTOR3((float)400.f, (float)iCenterY2, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//	nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(200, 255, 255, 255));

	CObjMgr::GetInstance()->Render();

	CCamera::GetInstance()->SetTransform();
}

void CTutorialScene::Release()
{
	//CObjMgr::GetInstance()->Release();
	//CTextureMgr::GetInstance()->Release();
	//CCamera::GetInstance()->Release();
	CTextureMgr::GetInstance()->Release();
	CCamera::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();
	CLineMgr::GetInstance()->Release();

	CTextureMgr::GetInstance()->DestroyInstance();
	CCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
}
