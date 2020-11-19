#include "stdafx.h"
#include "Dia_DialogBox.h"


CDia_DialogBox::CDia_DialogBox()
	:m_iDiaCnt(0)
{
}


CDia_DialogBox::~CDia_DialogBox()
{
	Release();
}

HRESULT CDia_DialogBox::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Dialog/Dialog_Layer.png", L"DialogBox", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Leo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadText()))
		return E_FAIL;

	return S_OK;
}

int CDia_DialogBox::Update()
{
	//CObj::LateInit();

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 260.f, 830.f, m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return NO_EVENT;
}

void CDia_DialogBox::LateUpdate()
{
	/*list<TCHAR*>::iterator iter_begin = m_DialogLst.begin();
	list<TCHAR*>::iterator iter_end = m_DialogLst.end();*/

	/*iter_begin = m_DialogLst.begin();
	iter_end = m_DialogLst.end();*/

	//if (CKeyMgr::GetInstance()->KeyDown(KEY_SPACE))
	//{
	//	++m_iDiaCnt;

	//	/*if (m_iDiaCnt >= m_vecDialog.size())
	//	{
	//		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_1);

	//		Release();
	//	}*/
	//}
}

void CDia_DialogBox::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"DialogBox");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (WINCX / 2) - CScrollMgr::GetScroll().x, (WINCY / 2) - CScrollMgr::GetScroll().y, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	// 이미지의 중점 구하기.
	/*int iCenterX2 = pTexInfo->tImgInfo.Width / 2;
	int iCenterY2 = pTexInfo->tImgInfo.Height / 2;*/

	//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*출력할 이미지 영역의 RECT*/,
		&D3DXVECTOR3((float)900.f, (float)550.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
		nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));


	TCHAR szBuf[MIN_STR] = L"";

	swprintf_s(szBuf, m_vecDialog[m_iDiaCnt]);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));

	//if (m_iDiaCnt >= 1)
	//{
	//	Release();

	//	CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE1_1);
	//}

}

void CDia_DialogBox::Release()
{
	m_vecDialog.clear();

	CTextureMgr::GetInstance()->DestroyInstance();
}

HRESULT CDia_DialogBox::LoadText()
{
	wifstream fin;

	fin.open(L"../Data/Dialog/Intro_Dialog.txt");

	if (fin.fail())
	{
		ERR_MSG(L"Intro Dialog Load Failed!");
		return E_FAIL;
	}

	TCHAR szCopyDialog[MAX_STR] = L"";

	m_vecDialog.clear();
	
	/*while (true)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pDialog = new DIALOG;

		_tcscpy_s(pDialog->szDialog, szCopyDialog);

		m_vecDialog.push_back(pDialog->szDialog);
	}*/

	for (size_t i = 0; i < 13; i++)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pDialog = new DIALOG;

		_tcscpy_s(pDialog->szDialog, szCopyDialog);

		m_vecDialog.push_back(pDialog->szDialog);

		fin.clear();
	}

	//if (fin.is_open())
	//{
	//	while (!fin.eof())
	//	{
	//		/*if (fin.eof())
	//			break;*/

	//		fin.getline(szCopyDialog, MIN_STR);

	//		pDialog = new DIALOG;

	//		_tcscpy_s(pDialog->szDialog, szCopyDialog);

	//		m_vecDialog.push_back(pDialog->szDialog);

	//		fin.clear();
	//	}
	//}

	fin.close();

	return S_OK;
}