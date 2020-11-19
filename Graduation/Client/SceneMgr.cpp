#include "stdafx.h"
#include "SceneMgr.h"

#include "LogIn.h"
#include "TutorialScene.h"
#include "Intro.h"
#include "DialogScene.h"
#include "Stage1_1.h"
#include "Stage1_2.h"
#include "Stage1_3.h"
#include "Stage1_Boss.h"

#include "DialogGasStation.h"
#include "Stage2_1.h"
#include "Stage2_2.h"
#include "DialogMordeo.h"
#include "Stage2Cartoon.h"
#include "AfterDialogMordeo.h"
#include "Stage2Boss.h"
#include "StageClear.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr), m_eCurScene(END), m_ePreScene(END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurScene)
		{
		case LOGO:
			m_pScene = new CLogIn;
			break;

		case TUTORIAL:
			m_pScene = new CTutorialScene;
			break;

		case INTRO:
			m_pScene = new CIntro;
			break;

		case DIALOG_SCENE:
			m_pScene = new CDialogScene;
			break;

		case STAGE1_1:
			m_pScene = new CStage1_1;
			break;

		case STAGE1_2:
			m_pScene = new CStage1_2;
			break;

		case STAGE1_3:
			m_pScene = new CStage1_3;
			break;

		case STAGE1_BOSS:
			m_pScene = new CStage1_Boss;
			break;

		case STAGE2_INTRO:
			m_pScene = new CDialogGasStation;
			break;

		case STAGE2_1:
			m_pScene = new CStage2_1;
			break;

		case STAGE2_2:
			m_pScene = new CStage2_2;
			break;

		case STAGE2_DIALOG:
			m_pScene = new CDialogMordeo;
			break;

		case STAGE2_CARTOON:
			m_pScene = new CStage2Cartoon;
			break;

		case STAGE2_AFTERDIALOG:
			m_pScene = new CAfterDialogMordeo;
			break;

		case STAGE2_BOSS:
			m_pScene = new CStage2Boss;
			break;

		case CLEAR:
			m_pScene = new CStageClear;
			break;
		}

		m_ePreScene = m_eCurScene;
		return m_pScene->Initialize();
	}

	return S_OK;
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
