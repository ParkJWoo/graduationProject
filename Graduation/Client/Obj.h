#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO& GetInfo() const { return m_tInfo; }
	const RECT& GetRect() const { return m_tRect; }
	const wstring& GetObjKey() { return m_wstrObjKey; }
	const int& GetDrawID() const { return m_iDrawID; }
	const DATA& GetData() const { return m_tData; }
	const bool& GetClicked() const { return m_bIsClick; }
	const bool& GetOnButton() const { return m_bOnButton; }
	const bool& GetInventory() const { return m_bIsInven; }
	const bool& GetDoor() const { return m_bIsDoor; }

	list<TERRAIN*>& GetTerrainLst() { return m_TerrainLst; }

	vector<TERRAIN*>& GetVecTerrain() { return m_vecTerrain; }

	TERRAIN* GetTerrain() { return pTerrain; }

	DATA& GetData() { return m_tData; }

	const int& GetDamageUI() const { return m_iHpNum; }

	const TCHAR* GetImgKey() const { return m_pImageKey; }
public:
	void SetPos(D3DXVECTOR3 vPos) { m_tInfo.vPos = vPos; }
	void SetMatrix(D3DXMATRIX vMat) { matTrans = vMat; }
	void SetDamage(int iDamage) { m_tData.iHp -= iDamage; }
	void SetDamageUI(int iDamage) { m_iHpNum -= iDamage; }
	void SetInventory(bool bIsInven) { m_bIsInven = bIsInven; }
	void SetDoor(bool bDoor) { m_bIsDoor = bDoor; }
	void SetDrawID(int iDrawID) { m_iDrawID = iDrawID; }

public:
	virtual HRESULT Initialize() PURE;
	virtual void LateInit();
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual HRESULT LoadObjects();


public:
	void IsDead() { m_bIsDead = true; }

public:
	INFO	m_tInfo;
	RECT	m_tRect;

	DATA	m_tData;

	D3DXMATRIX matTrans;

public:
	template <typename T>
	CObj* CreateLeftAttackEffect()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x + 100.f, m_tInfo.vPos.y, 0.f));
	}

	template <typename T>
	CObj* CreateRightAttackEffect()
	{
		return CAbstractFactory<T>::CreateObj(D3DXVECTOR3(m_tInfo.vPos.x - 100.f, m_tInfo.vPos.y, 0.f));
	}


protected:
	void MoveFrame();
	void OnceFrame();
	void QuickFrame();
	void UpdateRect();

protected:
	FRAME				m_tFrame;
	float				m_tTime;

	bool				m_bIsInit;
	bool				m_bIsDead;

	bool				m_bIsClick;

	TERRAIN*			pTerrain;
	list<TERRAIN*>		m_TerrainLst;
	vector<TERRAIN*>	m_vecTerrain;


	vector<INFO*>		m_vecInfo;

	wstring				m_wstrObjKey;
	wstring				m_wstrStateKey;

	TCHAR*				m_pImageKey;

	int					m_iDrawID;

	int					iAttackCnt;

	bool				bIsFirstAttack;
	bool				bIsSecondAttack;


	bool				m_bIsRight;
	bool				m_bIsLeft;

	bool				m_bOnButton;

	bool				m_bIsInven;

	bool				m_bIsDoor;

	float				m_fAlphaCnt;

	int					m_iHpNum;

	STATEID				m_eState;

	CObj*				m_pPlayer;


};
