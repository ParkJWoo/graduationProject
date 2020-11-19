#include "stdafx.h"
#include "Dia_StationDiaBox.h"


CDia_StationDiaBox::CDia_StationDiaBox()
	:m_iStationDiaCnt(0)
{
}


CDia_StationDiaBox::~CDia_StationDiaBox()
{
	Release();
}

HRESULT CDia_StationDiaBox::LoadStationText()
{
	wifstream fin;

	fin.open(L"../Data/Dialog/Station_Dialog.txt");

	if (fin.fail())
	{
		ERR_MSG(L"Intro Dialog Load Failed!");
		return E_FAIL;
	}

	TCHAR szCopyDialog[MAX_STR] = L"";

	m_vecStationDialog.clear();

	/*while (true)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pDialog = new DIALOG;

		_tcscpy_s(pDialog->szDialog, szCopyDialog);

		m_vecDialog.push_back(pDialog->szDialog);
	}*/

	for (size_t i = 0; i < 5; i++)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pStationDialog = new DIALOG;

		_tcscpy_s(pStationDialog->szDialog, szCopyDialog);

		m_vecStationDialog.push_back(pStationDialog->szDialog);

		fin.clear();
	}

	fin.close();

	return S_OK;
}

HRESULT CDia_StationDiaBox::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Station_Dia.png", L"StationDialogBox", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Leo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadStationText()))
		return E_FAIL;

	return S_OK;
}

int CDia_StationDiaBox::Update()
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 300.f, 900.f, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return NO_EVENT;
}

void CDia_StationDiaBox::LateUpdate()
{
}

void CDia_StationDiaBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"StationDialogBox");

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


	TCHAR szBuf[MIN_STR] = L"";

	swprintf_s(szBuf, m_vecStationDialog[m_iStationDiaCnt]);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CDia_StationDiaBox::Release()
{
}