#include "stdafx.h"
#include "LogIn.h"

#include "Button.h"
#include "Mouse.h"
//#include "Fade.h"

CLogIn::CLogIn()
	:fAlphaCnt(0.f)
{
}

CLogIn::~CLogIn()
{
	Release();
}

HRESULT CLogIn::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Logo/Logo.png", L"Logo", TEX_SINGLE)))
	{
		ERR_MSG(L"Logo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Button/Start.png", L"Start", TEX_SINGLE)))
	{
		ERR_MSG(L"Start Button Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Button/Stop.png", L"Stop", TEX_SINGLE)))
	{
		ERR_MSG(L"Stop Button Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Button/Load.png", L"Load", TEX_SINGLE)))
	{
		ERR_MSG(L"Load Button Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pMouse = nullptr;

	if (FAILED(CAbstractFactory<CMouse>::CreateObj(pMouse)))
		return E_FAIL;

	/*pFade = nullptr;
	if (FAILED(CAbstractFactory<CFade>::CreateObj(pFade)))
		return E_FAIL;*/

	pStart = CAbstractFactory<CButton>::CreateObj(D3DXVECTOR3(1700.f, 80.f, 0.f));
	CObj* pStop = CAbstractFactory<CButton>::CreateObj(D3DXVECTOR3(1700.f, 140.f, 0.f));
	CObj* pLoad = CAbstractFactory<CButton>::CreateObj(D3DXVECTOR3(1700.f, 200.f, 0.f));

	dynamic_cast<CButton*>(pStart)->SetImageKey(L"Start");
	dynamic_cast<CButton*>(pStop)->SetImageKey(L"Stop");
	dynamic_cast<CButton*>(pLoad)->SetImageKey(L"Load");

	CObjMgr::GetInstance()->AddObject(pStart, OBJ_BUTTON);
	//CObjMgr::GetInstance()->AddObject(pStop, OBJ_BUTTON);
	//CObjMgr::GetInstance()->AddObject(pLoad, OBJ_BUTTON);

	//CObjMgr::GetInstance()->AddObject(pMouse, OBJ_MOUSE);

	ShowCursor(true);

	return S_OK;
}

void CLogIn::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CLogIn::LateUpdate()
{
	if (pStart->GetClicked() == true)
	{
		fAlphaCnt += 0.05f;
		//CObjMgr::GetInstance()->AddObject(pFade, OBJ_FADE);

		if (fAlphaCnt >= 255.f)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::INTRO);
			return;
		}
	}

	CObjMgr::GetInstance()->LateUpdate();
}

void CLogIn::Render()
{
	//const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Logo");

	//D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	//D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	//matWorld = matScale * matTrans;

	////// SetTransform: 행렬을 반영하는 함수.
	//CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	//// 이미지의 중점 구하기.
	//int iCenterX = pTexInfo->tImgInfo.Width / 2;
	//int iCenterY = pTexInfo->tImgInfo.Height / 2;

	////// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	//CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
	//	nullptr /*출력할 이미지 영역의 RECT*/,
	//	&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
	//	nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo2 = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	D3DXMATRIX matScale2, matRotZ2, matTrans2, matWorld2;

	D3DXMatrixScaling(&matScale2, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans2, 500.f, 300.f, 0.f);

	matWorld2 = matScale2 * matTrans2;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	//// 이미지의 중점 구하기.
	int iCenterX2 = pTexInfo2->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo2->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo2->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX2, (float)iCenterY2, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"Logo");

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
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();

	const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans3, 500.f, 300.f, 0.f);

	matWorld3 = matScale3 * matTrans3;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld2);

	//// 이미지의 중점 구하기.
	int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo3->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)iCenterX2, (float)iCenterY2, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB((int)fAlphaCnt, 255, 255, 255));

}

void CLogIn::Release()
{
	//CObjMgr::GetInstance()->Release();

	CTextureMgr::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();

	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
}
