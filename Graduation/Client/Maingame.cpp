#include "stdafx.h"
#include "Maingame.h"

#include "Player.h"
#include "Mouse.h"

#include <iostream>

using namespace std;

CMaingame::CMaingame()
{
}

CMaingame::~CMaingame()
{
	Release();
}

HRESULT CMaingame::Initialize()
{
	CTimeMgr::GetInstance()->InitTime();

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		ERR_MSG(L"Device Init Failed");
		return E_FAIL;
	}

	if (FAILED(CSceneMgr::GetInstance()->SceneChange(CSceneMgr::STAGE2_BOSS)))
	{
		ERR_MSG(L"Stage Scene Change Failed");
		return E_FAIL;
	}

	/*CSoundMgr::GetInstance()->Initialize();
	CSoundMgr::GetInstance()->PlayBGM(L"Adam Levine - Lost Stars Lyrics.mp3");*/
	
	return S_OK;
}

void CMaingame::Update()
{
	// 시간 갱신은 Update 최상단에서 호출.
	CTimeMgr::GetInstance()->UpdateTime();
	CKeyMgr::GetInstance()->KeyCheck();
	CSceneMgr::GetInstance()->Update();
}

void CMaingame::LateUpdate()
{
	CSceneMgr::GetInstance()->LateUpdate();	
	//CSoundMgr::GetInstance()->UpdateSound();
}

void CMaingame::Render()
{
	// 1. 후면 버퍼를 비운다.
	CDevice::GetInstance()->GetDevice()->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	CDevice::GetInstance()->Render_Begin();
	CSceneMgr::GetInstance()->Render();

	/*if (CSceneMgr::GetInstance()->GetID() == CSceneMgr::STAGE1_1)
	{
		CCamera::GetInstance()->SetTransform();
	}*/

	CObjMgr::GetInstance()->Render();

	CDevice::GetInstance()->Render_End();
	//RenderLine(); // D3DXLINE은 D3DXSPRITE의 End 이후에 출력.

	// 3.후면버퍼를 전면버퍼로 교체한 후 화면에 출력한다.
	CDevice::GetInstance()->GetDevice()->Present(nullptr, nullptr, nullptr, nullptr);
}

void CMaingame::Release()
{
	CTextureMgr::GetInstance()->DestroyInstance();
	CCamera::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
	//CSoundMgr::GetInstance()->DestroyInstance();
	CTimeMgr::GetInstance()->DestroyInstance();
	CLineMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

void CMaingame::RenderLine()
{
	// 사각형을 그리기 위한 점 5개

	D3DXVECTOR2 vPoint[5] =
	{
		{ (float)CObjMgr::GetInstance()->GetPlayer()-> GetRect().left,(float)CObjMgr::GetInstance()->GetPlayer()->GetRect().top },
		{ (float)CObjMgr::GetInstance()->GetPlayer()->GetRect().right,(float)CObjMgr::GetInstance()->GetPlayer()->GetRect().top  },
		{ (float)CObjMgr::GetInstance()->GetPlayer()->GetRect().right,(float)CObjMgr::GetInstance()->GetPlayer()->GetRect().bottom },
		{ (float)CObjMgr::GetInstance()->GetPlayer()->GetRect().left,(float)CObjMgr::GetInstance()->GetPlayer()->GetRect().bottom },
		{ (float)CObjMgr::GetInstance()->GetPlayer()->GetRect().left ,(float)CObjMgr::GetInstance()->GetPlayer()->GetRect().top }
	};

	//cout << "Collision Position: " << CObjMgr::GetInstance()->GetPlayer()->GetRect().right - CObjMgr::GetInstance()->GetPlayer()->GetRect().left << endl;

	//cout << "Player Rect Size: " << CObjMgr::GetInstance()->GetPlayer()->GetRect().right << endl;
	
	CDevice::GetInstance()->GetLine()->SetWidth(2.f); // 선굵기
	CDevice::GetInstance()->GetLine()->Draw(vPoint, 5, D3DCOLOR_ARGB(255, 255, 0, 0));
}