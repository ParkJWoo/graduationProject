#include "stdafx.h"
#include "DialogMordeo.h"

#include "Mordeo_DialogBox.h"
#include "Dia_Laily.h"

CDialogMordeo::CDialogMordeo()
	:iMordeoDiaCnt(0)
{
}


CDialogMordeo::~CDialogMordeo()
{
	Release();
}

HRESULT CDialogMordeo::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Mordeo.png", L"DiaMordeoBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pMordeoLaily = nullptr;
	if (FAILED(CAbstractFactory<CDia_Laily>::CreateObj(pMordeoLaily)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMordeoLaily, OBJ_DIALOG_MATIKA);

	CObj* pMordeoDialog = nullptr;

	if (FAILED(CAbstractFactory<CMordeo_DialogBox>::CreateObj(pMordeoDialog)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pMordeoDialog, OBJ_DIALOGBOX);

	m_pMordeoDialog = dynamic_cast<CMordeo_DialogBox*>(pMordeoDialog);

	m_pMordeoDialog->SetDrawID(0);

	return S_OK;
}

void CDialogMordeo::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CDialogMordeo::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();

	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		++iMordeoDiaCnt;

		m_pMordeoDialog->SetMordeoDiaCnt(iMordeoDiaCnt);

		if (m_pMordeoDialog->GetMordeoDiaCnt() >= 6)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_CARTOON);
			return;
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_1);
		return;
	}
}

void CDialogMordeo::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"DiaMordeoBack");

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

void CDialogMordeo::Release()
{
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	//CObjMgr::GetInstance()->Release();
}
