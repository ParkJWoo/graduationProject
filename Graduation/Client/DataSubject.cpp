#include "stdafx.h"
#include "DataSubject.h"

IMPLEMENT_SINGLETON(CDataSubject)

CDataSubject::CDataSubject()
{
}


CDataSubject::~CDataSubject()
{
	Release();
}

list<void*>* CDataSubject::GetDataLst(int iMessage)
{
	auto iter_find = m_MapData.find(iMessage);

	if (m_MapData.end() == iter_find)
		return nullptr;

	return &iter_find->second;
}

void CDataSubject::Release()
{
	for (auto& MyPair : m_MapData)
		MyPair.second.clear();

	m_MapData.clear();
}

void CDataSubject::AddData(int iMessage, void * pData)
{
	if (nullptr != pData)
	{
		m_MapData[iMessage].push_back(pData);
		CSubject::Notify(iMessage, pData);	// 데이터가 등록되었음을 알림.
	}
}

void CDataSubject::RemoveData(int iMessage, void* pData)
{
	auto Map_iter = m_MapData.find(iMessage);

	if (m_MapData.end() != Map_iter)
	{
		auto iter_begin = Map_iter->second.begin();
		auto iter_end = Map_iter->second.end();

		for (; iter_begin != iter_end;)
		{
			if (pData == *iter_begin)
				iter_begin = Map_iter->second.erase(iter_begin);
			else
				++iter_begin;
		}
	}
}
