#include "stdafx.h"
#include "Mordeo_DialogBox.h"


CMordeo_DialogBox::CMordeo_DialogBox()
	:m_iMordeoDiaCnt(0)
{
}


CMordeo_DialogBox::~CMordeo_DialogBox()
{
	Release();
}

HRESULT CMordeo_DialogBox::LoadMordeoText()
{
	wifstream fin;

	fin.open(L"../Data/Dialog/Mordeo_Dialog.txt");

	if (fin.fail())
	{
		ERR_MSG(L"Mordeo Dialog Load Failed!");
		return E_FAIL;
	}

	TCHAR szCopyDialog[MAX_STR] = L"";

	m_vecMordeoDialog.clear();

	for (size_t i = 0; i < 10; i++)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pMordeoDialog = new DIALOG;

		_tcscpy_s(pMordeoDialog->szDialog, szCopyDialog);

		m_vecMordeoDialog.push_back(pMordeoDialog->szDialog);

		fin.clear();
	}

	fin.close();

	return S_OK;
}

HRESULT CMordeo_DialogBox::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Station_Dia.png", L"MordeoDialogBox", TEX_SINGLE)))
	{
		ERR_MSG(L"DialogBox Mordeo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadMordeoText()))
		return E_FAIL;

	return S_OK;
}

int CMordeo_DialogBox::Update()
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 300.f, 900.f, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return NO_EVENT;
}

void CMordeo_DialogBox::LateUpdate()
{
}

void CMordeo_DialogBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"MordeoDialogBox");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	TCHAR szBuf[MIN_STR] = L"";

	swprintf_s(szBuf, m_vecMordeoDialog[m_iMordeoDiaCnt]);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CMordeo_DialogBox::Release()
{
	m_vecMordeoDialog.clear();
	m_vecMordeoDialog.shrink_to_fit();
}
