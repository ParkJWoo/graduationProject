#pragma once

#include "Obj.h"

class CMouse : public CObj
{

	enum MOUSE_STANCE { NORMAL = 1, CLICK, ATTACK, MOUSE_END };

public:
	CMouse();
	virtual ~CMouse();

public:
	static D3DXVECTOR3 GetMouse();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	HRESULT CursorChange(MOUSE_STANCE eCursor);

private:
	MOUSE_STANCE m_eCursor;
};

