#pragma once
class CObserver
{
public:
	CObserver();
	virtual ~CObserver();

public:
	// Subject(���� ���)���κ��� �˸��� �ް� ������ ����.
	virtual void Update(int iMessage, void* pData) PURE;
};

