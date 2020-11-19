#include "stdafx.h"
#include "Stage2Cartoon.h"

#include "Stage2CutToon.h"

CStage2Cartoon::CStage2Cartoon()
{
}


CStage2Cartoon::~CStage2Cartoon()
{
	Release();
}

HRESULT CStage2Cartoon::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	pCutToon = nullptr;
	if (FAILED(CAbstractFactory<CStage2CutToon>::CreateObj(pCutToon)))
	{
		return E_FAIL;
	}


	CObjMgr::GetInstance()->AddObject(pCutToon, OBJ_CUTTOON);

	/*CObj* pMouse = nullptr;

	if (FAILED(CAbstractFactory<CMouse>::CreateObj(pMouse)))
		return E_FAIL;

	CObjMgr::GetInstance()->AddObject(pMouse, OBJ_MOUSE);

	ShowCursor(false);*/

	return S_OK;
}

void CStage2Cartoon::Update()
{
	CObjMgr::GetInstance()->Update();

	//fAlphaCnt += 1.f;

	if (pCutToon->GetInfo().vPos.y >= 6200.f)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_AFTERDIALOG);
		return;
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_RETURN))
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_AFTERDIALOG);
		return;
	}

	/*if (CKeyMgr::GetInstance()->KeyDown(KEY_DOWN))
	{
		fAlphaCnt += 1.f;

		if (fAlphaCnt >= 3.f)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::DIALOG_SCENE);
			return;
		}
	}*/
}

void CStage2Cartoon::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStage2Cartoon::Render()
{
	const TEXINFO* pTexInfo = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans, 500.f, 300.f, 0.f);

	matWorld = matScale * matTrans;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

	//// �̹����� ���� ���ϱ�.
	int iCenterX = pTexInfo->tImgInfo.Width / 2;
	int iCenterY = pTexInfo->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX, (float)iCenterY, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	CObjMgr::GetInstance()->Render();

	const TEXINFO* pTexInfo3 = CTextureMgr::GetInstance()->GetTexture(L"IntroBack");

	D3DXMATRIX matScale3, matRotZ3, matTrans3, matWorld3;

	D3DXMatrixScaling(&matScale3, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans3, 500.f, 300.f, 0.f);

	matWorld3 = matScale3 * matTrans3;

	//// SetTransform: ����� �ݿ��ϴ� �Լ�.
	CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld3);

	//// �̹����� ���� ���ϱ�.
	int iCenterX3 = pTexInfo3->tImgInfo.Width / 2;
	int iCenterY3 = pTexInfo3->tImgInfo.Height / 2;

	//// ������ ��� ������Ʈ�� �������� �� ���̿��� ����.
	CDevice::GetInstance()->GetSprite()->Draw(pTexInfo3->pTexture,
		nullptr /*����� �̹��� ������ RECT*/,
		&D3DXVECTOR3((float)iCenterX3, (float)iCenterY3, 0.f) /*����� �̹����� �߽� ��ǥ D3DXVECTOR3*/,
		nullptr /*����� ��ġ ��ǥ D3DXVECTOR3*/,
		D3DCOLOR_ARGB((int)255, 255, 255, 255));
}

void CStage2Cartoon::Release()
{
	//CObjMgr::GetInstance()->Release();
	CTextureMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
}
