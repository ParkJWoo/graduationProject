#include "stdafx.h"
#include "DialogScene.h"

#include "Dia_MatikaLayer.h"
#include "Dia_IronWindow.h"
#include "Dia_LeoLayer.h"
#include "DustLayer.h"

#include "Dia_DialogBox.h"

#include "Mouse.h"

CDialogScene::CDialogScene()
	:m_pDialog(nullptr), iDiaCnt(0)
{
}

CDialogScene::~CDialogScene()
{
	Release();
}

HRESULT CDialogScene::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Background.png", L"DiaBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pDust = nullptr;
	if (FAILED(CAbstractFactory<CDustLayer>::CreateObj(pDust, D3DXVECTOR3(1000.f, 400.f, 0.f))))
		return E_FAIL;

	CObj* pMatika = nullptr;
	if (FAILED(CAbstractFactory<CDia_MatikaLayer>::CreateObj(pMatika)))
		return E_FAIL;

	CObj* pIronWindow = nullptr;
	if (FAILED(CAbstractFactory<CDia_IronWindow>::CreateObj(pIronWindow)))
		return E_FAIL;

	CObj* pLeo = nullptr;
	if (FAILED(CAbstractFactory<CDia_LeoLayer>::CreateObj(pLeo)))
		return E_FAIL;

	CObj* pDialogBox = nullptr;
	if (FAILED(CAbstractFactory<CDia_DialogBox>::CreateObj(pDialogBox)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pDust, OBJ_DUST);
	CObjMgr::GetInstance()->AddObject(pMatika, OBJ_DIALOG_MATIKA);
	CObjMgr::GetInstance()->AddObject(pIronWindow, OBJ_DIALOG_IRONWINDOW);
	CObjMgr::GetInstance()->AddObject(pLeo, OBJ_DIALOG_LEO);
	CObjMgr::GetInstance()->AddObject(pDialogBox, OBJ_DIALOGBOX);

	CObj* pMouse = nullptr;

	if (FAILED(CAbstractFactory<CMouse>::CreateObj(pMouse)))
		return E_FAIL;

	//CObjMgr::GetInstance()->AddObject(pMouse, OBJ_MOUSE);

	ShowCursor(true);

	m_pDialog = dynamic_cast<CDia_DialogBox*>(pDialogBox);

	//CSoundMgr::GetInstance()->Initialize(g_hWnd);

	return S_OK;
}

void CDialogScene::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CDialogScene::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();

	/*if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_1);
		return;
	}*/

	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		++iDiaCnt;

		m_pDialog->SetDiaCnt(iDiaCnt);

		if (m_pDialog->GetDiaCnt() >= 13)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::TUTORIAL);
			return;
		}
	}
}

void CDialogScene::Render()
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
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();
}

void CDialogScene::Release()
{
	CTextureMgr::GetInstance()->Release();
	CObjMgr::GetInstance()->Release();

	//CSoundMgr::GetInstance()->Shutdown();

	//CSoundMgr::GetInstance()->DestroyInstance();
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
}
