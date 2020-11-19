#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"


CSubject::CSubject()
{
}


CSubject::~CSubject()
{
	Release();
}

void CSubject::Subscribe(CObserver* pObserver)
{
	m_ObserverLst.push_back(pObserver);
}

void CSubject::UnSubscribe(CObserver* pObserver)
{
	for (auto& iter_begin = m_ObserverLst.begin(); iter_begin != m_ObserverLst.end(); )
	{
		if (pObserver == *iter_begin)
			iter_begin = m_ObserverLst.erase(iter_begin);
		else
			++iter_begin;
	}
}

void CSubject::Notify(int iMessage, void * pData)
{
	for (auto& pObserver : m_ObserverLst)
		pObserver->Update(iMessage, pData);
}

void CSubject::Release()
{
	// Subject는 옵저를 생성하고 해제할 권리는 없다.
	m_ObserverLst.clear();
}
