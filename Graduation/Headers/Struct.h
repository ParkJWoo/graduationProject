#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX  matWorld;
}INFO;

typedef struct tagLinePoint
{
	tagLinePoint()
		:fX(0.f),fY(0.f){}

	tagLinePoint(float x, float y)
		:fX(x), fY(y) {}

	float fX;
	float fY;

} LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo()
	{
	}

	tagLineInfo(D3DXVECTOR2 pStartPos, D3DXVECTOR2 pEndPos)
		: vStartPos(pStartPos), vEndPos(pEndPos) {}

	D3DXVECTOR2 vStartPos;	//	������
	D3DXVECTOR2 vEndPos;	//	����

	float fWidth;			//	�� ����

} LINEINFO;

typedef struct tagTexture
{
	// LPDIRECT3DTEXTURE9: �̹��� ������ ������ Com��ü
	LPDIRECT3DTEXTURE9	pTexture;

	// �̹��� ������ �����ϱ� ���� ����ü.
	D3DXIMAGE_INFO		tImgInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;	// Ÿ���� ����.
	D3DXVECTOR3	vSize;	// Ÿ���� ũ��.
	BYTE byOption;		// Ÿ���� �ɼ�.
	BYTE byDrawID;		// ������ �ɼ�.

	int iIndex = 0;	// ���� Ÿ���� �ε��� ����.
	int iParentIdx = 0;	// �θ� Ÿ���� �ε��� ����.
}TILE;

typedef struct tagTerrain
{
	D3DXVECTOR3 vPos;
	BYTE		byOption;
	BYTE		byDrawID;
	D3DXMATRIX matWorld;

} TERRAIN;

typedef struct tagUnitData
{
#ifndef _AFX
	wstring strName;
#else
	CString strName;
#endif

	int		iAtt;
	int		iDef;
	BYTE	byJobIndex;
	BYTE	byItem;
}UNIT_DATA;

typedef struct tagTexturePath
{
	wstring wstrObjKey = L"";
	wstring wstrStateKey = L"";
	wstring wstrPath = L"";
	int iCount = 0;
}IMGPATH;

typedef struct tagDialogText
{
	TCHAR szDialog[MIN_STR] = L"";

}DIALOG;

typedef struct tagFrame
{
	tagFrame()
		: fFrame(0.f), fMax(0.f)
	{}

	tagFrame(float frame, float max)
		: fFrame(frame), fMax(max)
	{}

	float fFrame; // ���� �ִϸ��̼� ��� ����.
	float fMax;	// �ִ� ��� ����.

}FRAME;

typedef struct tagData
{
	int iHp;
	int iMp;
	int iDamage;

}DATA;