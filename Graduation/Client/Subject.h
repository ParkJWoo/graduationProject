#pragma once

class CObserver;
class CSubject
{
public:
	CSubject();
	virtual ~CSubject();

public:
	// 정리
	virtual void Release();

public:
	// 관찰자 등록
	void Subscribe(CObserver* pObserver);

	// 구독 해제
	void UnSubscribe(CObserver* pObserver);

	// 관찰자들에게 알림.
	void Notify(int iMessage, void* pData = nullptr);

private:
	list<CObserver*>	m_ObserverLst;
};

