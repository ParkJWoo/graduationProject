#include "stdafx.h"
#include "TutorialDialog.h"
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#include "UIObserver.h"

CTutorialDialog::CTutorialDialog()
	:m_iDiaCnt(0)
{
}


CTutorialDialog::~CTutorialDialog()
{
	Release();
}

HRESULT CTutorialDialog::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tutorial/Dialog_Tutorial.png", L"TutorialDialogBox", TEX_SINGLE)))
	{
		ERR_MSG(L"Dialog Leo Image Insert Failed!!!");
		return E_FAIL;
	}

	if (FAILED(LoadTutorialText()))
		return E_FAIL;

	//m_fSpeed = 0.1f;
	
	m_tInfo.vPos = D3DXVECTOR3(-300.f, 0.f, 0.f);

	pObserver = new CUIObserver;
	CDataSubject::GetInstance()->Subscribe(pObserver);

	return S_OK;
}

int CTutorialDialog::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	D3DXMATRIX matTrans, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	matParent = dynamic_cast<CUIObserver*>(pObserver)->GetMatrix();

	D3DXMatrixIdentity(&matPos);

	matPos._41 = matParent._41;

	m_tInfo.matWorld = matTrans * matPos;

	float fTime = 0.f;
	fTime += 15.f * CTimeMgr::GetInstance()->GetTime();

	/*if (fTime >= 10.f)
	{
		++m_iDiaCnt;

		fTime = 0.f;
		fTime += 15.f * CTimeMgr::GetInstance()->GetTime();
	}*/

	if (CKeyMgr::GetInstance()->KeyDown(KEY_D))
		++m_iDiaCnt;

	if (m_iDiaCnt >= 11)
		return DEAD_OBJ;

	return NO_EVENT;
}

void CTutorialDialog::LateUpdate()
{
}

void CTutorialDialog::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"TutorialDialogBox");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld, matParent;
	D3DXMATRIX matPos;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans, (float)300.f, (float)500.f, 0.f);

	matParent = dynamic_cast<CUIObserver*>(pObserver)->GetMatrix();

	D3DXMatrixIdentity(&matPos);

	matPos._41 = matParent._41;

	matWorld = matScale * matTrans * matParent;

	//// SetTransform: 행렬을 반영하는 함수.
	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	// 이미지의 중점 구하기.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	if (m_iDiaCnt % 2 != 0)
	{
		//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr /*출력할 이미지 영역의 RECT*/,
			&D3DXVECTOR3((float)iCenterX - 350.f, (float)iCenterY - 10.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
			nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
			D3DCOLOR_ARGB(0, 255, 255, 255));
	}

	else
	{
		//// 앞으로 모든 오브젝트의 렌더링은 이 사이에서 진행.
		CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
			nullptr /*출력할 이미지 영역의 RECT*/,
			&D3DXVECTOR3((float)iCenterX - 400.f, (float)iCenterY - 10.f, 0.f) /*출력할 이미지의 중심 좌표 D3DXVECTOR3*/,
			nullptr /*출력할 위치 좌표 D3DXVECTOR3*/,
			D3DCOLOR_ARGB(100, 255, 255, 255));
	}
	

	TCHAR szBuf[MIN_STR] = L"";

	swprintf_s(szBuf, m_vecTutorialDialog[m_iDiaCnt]);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);
	CDevice::GetInstance()->GetFont()->DrawTextW(CDevice::GetInstance()->GetSprite(),
		szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 0, 0, 0));
}

void CTutorialDialog::Release()
{
	//m_vecTutorialDialog.clear();
	//CTextureMgr::GetInstance()->DestroyInstance();
	//CObjMgr::GetInstance()->DestroyInstance();
}

HRESULT CTutorialDialog::LoadTutorialText()
{
	wifstream fin;

	fin.open(L"../Data/Tutorial/Tutorial_Dialog.txt");

	if (fin.fail())
	{
		ERR_MSG(L"Tutorial Dialog Load Failed!");
		return E_FAIL;
	}

	TCHAR szCopyDialog[MAX_STR] = L"";

	m_vecTutorialDialog.clear();

	for (size_t i = 0; i < 11; i++)
	{
		if (fin.eof())
			break;

		fin.getline(szCopyDialog, MIN_STR);

		pTutorialDialog = new DIALOG;

		_tcscpy_s(pTutorialDialog->szDialog, szCopyDialog);

		m_vecTutorialDialog.push_back(pTutorialDialog->szDialog);

		fin.clear();
	}

	fin.close();

	return S_OK;
}
