#include "stdafx.h"
#include "Stage2Boss.h"

#include "Player.h"

#include "Kiano.h"

CStage2Boss::CStage2Boss()
	:m_pPlayer(nullptr)
{
}


CStage2Boss::~CStage2Boss()
{
	Release();
}

HRESULT CStage2Boss::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Scene8.png", L"Stage2_Boss_Background", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage Boss Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pPlayer = nullptr;
	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	CObj* pKiano = nullptr;
	if (FAILED(CAbstractFactory<CKiano>::CreateObj(pKiano, D3DXVECTOR3(700.f, 500.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pKiano, OBJ_MONSTER);

	if (FAILED(CStageCamera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Boss Stage Camera Init Failed");
		return E_FAIL;
	}

	/*CObj* pStageBoss = nullptr;
	if (FAILED(CAbstractFactory<CStageBoss>::CreateObj(pStageBoss, D3DXVECTOR3(200.f, 450.f, 0.f))))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pStageBoss, OBJ_MONSTER);*/
	

	//CObj* pLight = nullptr;
	//if (FAILED(CAbstractFactory<CStreetLight>::CreateObj(pLight/*D3DXVECTOR3(500.f, 450.f, 0.f)*/)))
	//	return E_FAIL;

	//CObjMgr::GetInstance()->AddObject(pLight, OBJ_STREETLIGHT);

	CStage2LineMgr::GetInstance()->Initialize();

	ShowCursor(true);

	return S_OK;
}

void CStage2Boss::Update()
{
	CObjMgr::GetInstance()->Update();
	CStageCamera::GetInstance()->Update();
}

void CStage2Boss::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::CLEAR);

		return;
	}
}

void CStage2Boss::Render()
{
	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"DiaBack");

	D3DXMATRIX matScale2, matRotZ2, matTrans2, matWorld2;

	D3DXMatrixScaling(&matScale2, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans2, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld2 = matScale2 * matTrans2;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	// 이미지의 중점 구하기.
	int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)1200.f, (float)540.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Stage2_Boss_Background");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)1920.f, (float)800.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();
	CStageCamera::GetInstance()->SetTransform();
}

void CStage2Boss::Release()
{
	//CObjMgr::GetInstance()->Release();
	//CStage2Camera::GetInstance()->Release();
	CTutorialSound::GetInstance()->Shutdown();

	CTutorialSound::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CStageCamera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CStage2LineMgr::GetInstance()->DestroyInstance();
}
