#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	// ���� ��θ� ��� ��η� ��ȯ ���ִ� �Լ�.
	static CString ConvertRelativePath(CString strFullPath);

	// ��θ� ���� ObjectKey�� StateKey ���� ������ �����ϴ� �Լ�.
	static void DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoLst);

	// ���� ��ο� ����ִ� �̹��� ������ ������ ��ȯ.
	static int DirFileCount(const wstring& wstrPath);
};

