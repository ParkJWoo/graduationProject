#include "stdafx.h"
#include "Intro.h"

#include "CutToon.h"
#include "Mouse.h"

CIntro::CIntro()
	:fAlphaCnt(0.f)
{
}

CIntro::~CIntro()
{
	Release();
}

HRESULT CIntro::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Intro/IntroBack.png", L"IntroBack", TEX_SINGLE)))
	{
		ERR_MSG(L"IntroBackground Image Insert Failed!!!");
		return E_FAIL;
	}

	pCutToon = nullptr;
	if (FAILED(CAbstractFactory<CCutToon>::CreateObj(pCutToon)))
	{
		return E_FAIL;
	}


	CObjMgr::GetInstance()->AddObject(pCutToon, OBJ_CUTTOON);

	CObj* pMouse = nullptr;

	if (FAILED(CAbstractFactory<CMouse>::CreateObj(pMouse)))
		return E_FAIL;

	//CObjMgr::GetInstance()->AddObject(pMouse, OBJ_MOUSE);

	ShowCursor(true);

	CSoundMgr::GetInstance()->Initialize(g_hWnd);

	return S_OK;
}

void CIntro::Update()
{
	CObjMgr::GetInstance()->Update();

	fAlphaCnt += 1.f;

	if (pCutToon->GetInfo().vPos.y >= 5200.f)
	{
		CSceneMgr::GetInstance()->SceneChange(CSceneMgr::DIALOG_SCENE);
		return;
	}

	if (CKeyMgr::GetInstance()->KeyDown(KEY_DOWN))
	{
		fAlphaCnt += 1.f;

		if (fAlphaCnt >= 3.f)
		{
			CSceneMgr::GetInstance()->SceneChange(CSceneMgr::DIALOG_SCENE);
			return;
		}
	}
}

void CIntro::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CIntro::Render()
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

void CIntro::Release()
{
	CObjMgr::GetInstance()->Release();
	//CSoundMgr::GetInstance()->Shutdown();

	//CSoundMgr::GetInstance()->DestroyInstance();
	_CrtDumpMemoryLeaks();
}

