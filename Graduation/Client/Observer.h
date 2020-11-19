#pragma once
class CObserver
{
public:
	CObserver();
	virtual ~CObserver();

public:
	// Subject(관찰 대상)으로부터 알림을 받고 데이터 갱신.
	virtual void Update(int iMessage, void* pData) PURE;
};

