#include "stdafx.h"
#include "Stage2_2.h"

#include "Player.h"

#include "RedLight.h"

CStage2_2::CStage2_2()
{
}


CStage2_2::~CStage2_2()
{
	Release();
}

HRESULT CStage2_2::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->ReadImgPath(L"../Data/ImgPath.txt")))
		return E_FAIL;
	

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Scene10.png", L"Scene7", TEX_SINGLE)))
	{
		ERR_MSG(L"Stage 1-1 Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	/////////////////////////////	시체들	 /////////////////////////////////////////////

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Mordeo_Body0.png", L"Body0", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Mordeo_Body1.png", L"Body1", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Mordeo_Body2.png", L"Body2", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Background/Stage2/Laily1.png", L"Laily", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}


	CObj* pPlayer = nullptr;
	if (FAILED(CAbstractFactory<CPlayer>::CreateObj(pPlayer)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pPlayer, OBJ_PLAYER);

	if (FAILED(CStage2Camera::GetInstance()->Initialize(WINCX, WINCY, 0.f, D3DXVECTOR3(1.f, 1.f, 1.f))))
	{
		ERR_MSG(L"Camera Init Failed");
		return E_FAIL;
	}

	CObj* pLight = nullptr;
	if (FAILED(CAbstractFactory<CRedLight>::CreateObj(pLight, D3DXVECTOR3(1500.f, -160.f, 0.f))))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pLight, OBJ_LIGHT);

	CStage2LineMgr::GetInstance()->Initialize();

	return S_OK;
}

void CStage2_2::Update()
{
	CObjMgr::GetInstance()->Update();
	CStage2Camera::GetInstance()->Update();
}

void CStage2_2::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_DIALOG);
		return;
	}
}

void CStage2_2::Render()
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

	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"Scene7");

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
		&D3DXVECTOR3((float)2200.f, (float)1400.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"Body0");

	D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans3, WINCX - CScrollMgr::GetScroll().x, WINCY - CScrollMgr::GetScroll().y, 0.f);

	matWorld3 = matScale3 * matTrans3;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld3);

	// 이미지의 중점 구하기.
	int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo3->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)2100.f, (float)700.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo4 = CTextureMgr::GetInstance()->GetTexture(L"Body1");

	D3DXMATRIX matScale4, matRotZ4, matTrans4, matWorld4;

	D3DXMatrixScaling(&matScale4, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans4, WINCX - CScrollMgr::GetScroll().x, WINCY - CScrollMgr::GetScroll().y, 0.f);

	matWorld4 = matScale4 * matTrans4;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld4);

	// 이미지의 중점 구하기.
	int iCenterX4 = pTexInfo4->tImgInfo.Width / 2;
	int iCenterY4 = pTexInfo4->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo4->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)1450.f, (float)500.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo5 = CTextureMgr::GetInstance()->GetTexture(L"Body2");

	D3DXMATRIX matScale5, matRotZ5, matTrans5, matWorld5;

	D3DXMatrixScaling(&matScale5, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans5, WINCX - CScrollMgr::GetScroll().x, WINCY - CScrollMgr::GetScroll().y, 0.f);

	matWorld5 = matScale5 * matTrans4;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld5);

	// 이미지의 중점 구하기.
	int iCenterX5 = pTexInfo5->tImgInfo.Width / 2;
	int iCenterY5 = pTexInfo5->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo5->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)-460.f, (float)700.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo6 = CTextureMgr::GetInstance()->GetTexture(L"Laily");

	D3DXMATRIX matScale6, matRotZ6, matTrans6, matWorld6;

	D3DXMatrixScaling(&matScale6, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans6, WINCX - CScrollMgr::GetScroll().x, WINCY - CScrollMgr::GetScroll().y, 0.f);

	matWorld6 = matScale6 * matTrans6;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld6);

	// 이미지의 중점 구하기.
	int iCenterX6 = pTexInfo6->tImgInfo.Width / 2;
	int iCenterY6 = pTexInfo6->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo6->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)450.f, (float)650.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();


	CStage2Camera::GetInstance()->SetTransform();
}

void CStage2_2::Release()
{
	/*CObjMgr::GetInstance()->Release();
	CTextureMgr::GetInstance()->Release();*/
	CTextureMgr::GetInstance()->DestroyInstance();
	CStage2Camera::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	CStage2LineMgr::GetInstance()->DestroyInstance();

}
