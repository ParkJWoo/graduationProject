#include "stdafx.h"
#include "DialogGasStation.h"

#include "Dia_StationMatika.h"
#include "Dia_StationDiaBox.h"

CDialogGasStation::CDialogGasStation()
	:iStationDiaCnt(0),m_pStationDialog(nullptr)
{
}

CDialogGasStation::~CDialogGasStation()
{
	Release();
}

HRESULT CDialogGasStation::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Station_Background.png", L"DiaStationBack", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Background Image Insert Failed!!!");
		return E_FAIL;
	}

	CObj* pStationMatika = nullptr;
	if (FAILED(CAbstractFactory<CDia_StationMatika>::CreateObj(pStationMatika)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pStationMatika, OBJ_DIALOG_MATIKA);


	CObj* pStationDialog = nullptr;
	if (FAILED(CAbstractFactory<CDia_StationDiaBox>::CreateObj(pStationDialog)))
		return E_FAIL;
	CObjMgr::GetInstance()->AddObject(pStationDialog, OBJ_DIALOGBOX);

	m_pStationDialog = dynamic_cast<CDia_StationDiaBox*>(pStationDialog);

	return S_OK;
}

void CDialogGasStation::Update()
{
	CObjMgr::GetInstance()->Update();
}

void CDialogGasStation::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();

	if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	{
		++iStationDiaCnt;

		m_pStationDialog->SetStationDiaCnt(iStationDiaCnt);

		if (m_pStationDialog->GetStationDiaCnt() >= 5)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_1);
			return;
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_1);
		return;
	}
}

void CDialogGasStation::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"DiaStationBack");

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

void CDialogGasStation::Release()
{
	CObjMgr::GetInstance()->Release();
}
