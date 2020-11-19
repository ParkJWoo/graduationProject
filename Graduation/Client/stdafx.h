// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

//	�ܼ�â ���
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>
#include <io.h>
#include <ctime>

#include <iostream>

using namespace std;

// d3d9: ��ġ(GPU)�� �����ϱ� ���� �ڷ����̳� �Լ��� �����Ѵ�.
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

//#include "fmod.h"
//#pragma comment(lib, "fmodex_vc.lib")
//#pragma comment(lib, "fmodx_vc.lib")

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
//#include <stdio.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


// d3dx9: ���̷�Ʈ���� ����� ����, ��� �ڷ����̳� �����Լ����� �����Ѵ�.
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Extern.h"
#include "Define.h"
#include "Constant.h"
#include "Typedef.h"
#include "Enum.h"
#include "Struct.h"
#include "Function.h"
#include "Functor.h"

// managers
#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "AbstractFactoy.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "DataSubject.h"
#include "Camera.h"
#include "Stage2Camera.h"
#include "CStageCamera.h"
#include "StageCamera.h"
#include "LineMgr.h"
#include "CollisionMgr.h"
#include "Stage2LineMgr.h"
#include "TutorialSound.h"
//#include "MathMgr.h"