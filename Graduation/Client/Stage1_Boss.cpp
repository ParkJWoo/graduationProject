#include "stdafx.h"
#include "Stage1_Boss.h"
#include "Player.h"

#include "Mouse.h"

#include "BackLight.h"
#include "StreetLight.h"

#include "StreetLamp.h"

#include "StageBoss.h"

CStage1_Boss::CStage1_Boss()
	:m_pPlayer(nullptr)
{
}

CStage1_Boss::~CStage1_Boss()
{
	Release();
}

HRESULT CStage1_Boss::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene4.png", L"Stage1_Boss_Background", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage Boss Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pPlayer = nullptr;
	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	//if (FAILED(CCStageCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	//{
	//	ERR_MSG(L"Boss Stage Camera Init Failed");
	//	return E_FAIL;
	//}

	if (FAILED(CStageCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Boss Stage Camera Init Failed");
		return E_FAIL;
	}

	CObj* pStageBoss = nullptr;
	if (FAILED(CAbstractFactory<CStageBoss>::CreateObj(pStageBoss, D3DXVECTOR3(700.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pStageBoss, OBJ_MONSTER);

	CObj* pFrontLayer = nullptr;
	if (FAILED(CAbstractFactory<CStreetLamp>::CreateObj(pFrontLayer)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pFrontLayer, OBJ_FRONTLAYER);

	CObj* pLight = nullptr;
	if (FAILED(CAbstractFactory<CStreetLight>::CreateObj(pLight, D3DXVECTOR3(0.f, -10.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pLight, OBJ_STREETLIGHT);

	CLineMgr::GetInstance()->Initialize();

	ShowCursor(true);

	return S_OK;
}

void CStage1_Boss::Update()
{
	//if (CKeyMgr::GetInstance()->KeyDown(KEY_DOWN))
	//{
	//	CObj* pEffect = CEffectFactory<CEffect, CAnimEffect>::CreateEffect(D3DXVECTOR3(200.f, 300.f, 0.f),
	//		L"Explosion", { 0.f,7.f });

	//	CObjMgr::GetInstance()->AddObject(pEffect, OBJ_EFFECT);
	//}

	CObjMgr::GetInstance()->Update();
	//CCStageCamera::GetInstance()->Update();
	CStageCamera::GetInstance()->Update();

	/*D3DXMATRIX matPos;
	DATA		data;

	matPos = dynamic_cast<CPlayer*>(m_pPlayer)->GetInfo().matWorld;
	data = dynamic_cast<CPlayer*>(m_pPlayer)->GetData();

	CDataSubject::GetInstance()->AddData(PLAYER_DATA, &data);
	CDataSubject::GetInstance()->AddData(PLAYER_MATRIX, &matPos);

	CDataSubject::GetInstance()->Notify(PLAYER_MATRIX, &matPos);*/


}

void CStage1_Boss::LateUpdate()
{
	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_INTRO);

		return;
	}

	CObjMgr::GetInstance()->LateUpdate();
}

void CStage1_Boss::Render()
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

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Stage1_Boss_Background");

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
		&D3DXVECTOR3((float)1920.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();
	//CCStageCamera::GetInstance()->SetTransform();
	CStageCamera::GetInstance()->SetTransform();
}

void CStage1_Boss::Release()
{
	//CObjMgr::GetInstance()->Release();
	////CCStageCamera::GetInstance()->Release();
	//CTextureMgr::GetInstance()->Release();
	//CStageCamera::GetInstance()->Release();
	CTextureMgr::GetInstance()->Release();
	CStageCamera::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();
	CLineMgr::GetInstance()->Release();

	CSoundMgr::GetInstance()->Shutdown();

	CTextureMgr::GetInstance()->DestroyInstance();
	CStageCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
}
