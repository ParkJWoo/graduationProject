#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID {
		LOGO, TUTORIAL, INTRO, DIALOG_SCENE, STAGE1_1, STAGE1_2, STAGE1_3, STAGE1_BOSS, 
		STAGE2_INTRO, STAGE2_1, STAGE2_2, STAGE2_DIALOG, STAGE2_CARTOON, STAGE2_AFTERDIALOG,STAGE2_BOSS,
		CLEAR, END
	};

private:
	CSceneMgr();
	~CSceneMgr();

public:
	const SCENEID& GetID() { return m_eCurScene; }

public:
	HRESULT SceneChange(SCENEID eID);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	CScene*	m_pScene;
	SCENEID m_eCurScene;
	SCENEID m_ePreScene;
};

