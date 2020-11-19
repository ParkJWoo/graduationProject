#include "stdafx.h"
#include "After_DialogBox.h"

CAfter_DialogBox::CAfter_DialogBox()
	:m_iAfterDialog(0)
{
}

CAfter_DialogBox::~CAfter_DialogBox()
{
	Release();
}

HRESULT CAfter_DialogBox::LoadAfterDialog()
{
	wifstream fin;

	fin.open(L"../Data/Dialog/After_Dialog.txt");

	if (fin.fail())
	{
		ERR_MSG(L"After Dialog Load Failed!");
		return E_FAIL;
	}

	TCHAR szCopyDialog[MAX_STR] = L"";

	m_vecAfterDialog.clear();

	for (size_t i = 0; i < 5; i++)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pAfterDialog = new DIALOG;

		_tcscpy_s(pAfterDialog->szDialog, szCopyDialog);

		m_vecAfterDialog.push_back(pAfterDialog->szDialog);

		fin.clear();
	}

	fin.close();

	return S_OK;
}

HRESULT CAfter_DialogBox::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Station_Dia.png", L"AfterDialogBox", TEX_SINGLE)))
	{
		ERR_MSG(L"DialogBox Mordeo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadAfterDialog()))
		return E_FAIL;

	return S_OK;
}

int CAfter_DialogBox::Update()
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 300.f, 900.f, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return NO_EVENT;
}

void CAfter_DialogBox::LateUpdate()
{
}

void CAfter_DialogBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"AfterDialogBox");

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

	swprintf_s(szBuf, m_vecAfterDialog[m_iAfterDialog]);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CAfter_DialogBox::Release()
{
	m_vecAfterDialog.clear();
	m_vecAfterDialog.shrink_to_fit();
}
