#pragma once
#include "Obj.h"


// 추상층

class CEffectIMP;
class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	void SetBridge(CEffectIMP* pBridge) { m_pBridge = pBridge; }

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

protected:
	CEffectIMP*	m_pBridge;
};

