#pragma once
#include "Obj.h"


// �߻���

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
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;

protected:
	CEffectIMP*	m_pBridge;
};

