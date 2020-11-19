#pragma once
#include "Obj.h"
class CDoor :
	public CObj
{
public:
	CDoor();
	virtual ~CDoor();

public: 
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};

