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

	D3DXVECTOR2 vStartPos;	//	시작점
	D3DXVECTOR2 vEndPos;	//	끝점

	float fWidth;			//	선 굵기

} LINEINFO;

typedef struct tagTexture
{
	// LPDIRECT3DTEXTURE9: 이미지 한장을 제어할 Com객체
	LPDIRECT3DTEXTURE9	pTexture;

	// 이미지 정보를 보관하기 위한 구조체.
	D3DXIMAGE_INFO		tImgInfo;
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;	// 타일의 중점.
	D3DXVECTOR3	vSize;	// 타일의 크기.
	BYTE byOption;		// 타일의 옵션.
	BYTE byDrawID;		// 렌더링 옵션.

	int iIndex = 0;	// 현재 타일의 인덱스 정보.
	int iParentIdx = 0;	// 부모 타일의 인덱스 정보.
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

	float fFrame; // 현재 애니메이션 재생 구간.
	float fMax;	// 최대 재생 길이.

}FRAME;

typedef struct tagData
{
	int iHp;
	int iMp;
	int iDamage;

}DATA;