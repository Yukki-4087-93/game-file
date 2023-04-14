//--------------------------------------------------------------------------------------
//
// ���C��
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ���C�u�����[�����N
//-----------------------------------------------------------------------------
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>
#include "main.h"
#include "application.h"

//-----------------------------------------------------------------------------
// �萔��`
//-----------------------------------------------------------------------------
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("MetaBot-Metal Poping Sound-");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("MetaBot-Metal Poping Sound-");

	// �X�N���[���̕�
	const int SCREEN_WIDTH = 1280;
	// �X�N���[���̍���
	const int SCREEN_HEIGHT = 720;
}

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hinstace,HWND hWnd, bool bWindow);
void Uninit();
void Update();
void Draw();
int GetCount();

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
// FPS�J�E���^
int g_nCountFPS;

// �A�v���P�[�V�����̃|�C���^�錾
CApplication* pApplecation;

//-----------------------------------------------------------------------------
// ���C���֐�
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̍쐬
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//���I�m��
	pApplecation = new CApplication;

	// ����������
	if (FAILED(Init(hInstance,hWnd,TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// ���b�Z�[�W���[�v
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}
#endif // _DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 1/60�b�o��
				// ���݂̎��Ԃ�ۑ�
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif // _DEBUG
			}
		}
	}

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//-----------------------------------------------------------------------------
// �E�C���h�E�v���V�[�W��
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]�L�[�������ꂽ
			// �E�B���h�E��j��
			Uninit();
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HRESULT Init(HINSTANCE hinstace, HWND hWnd, bool bWindow)
{
	pApplecation->Init(hinstace, hWnd, bWindow);
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
void Uninit()
{
	if (pApplecation != nullptr)
	{
		pApplecation->Uninit();
		delete pApplecation;
		pApplecation = nullptr;
	}
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Update()
{
	pApplecation->Update();
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Draw()
{
	pApplecation->Draw();
}

//-----------------------------------------------------------------------------
// �J�E���^�[���̎擾
//-----------------------------------------------------------------------------
int GetCount()
{
	return g_nCountFPS;
}

/*
�����_�����O�c�v�Z�Ȃǂ���g���ĕ`����s������

���C���Ő������ă����_�����O�����Ŏ��̂�����

//�L���X�g�����g����������

//�ϐ��̐錾
CObject *g_pObj = nullptr;

//�|���S������
if (!g_pObj)
{
g_pObj = new CObject2D;
}

if (g_pObj)
{
g_pObj->Init();
//�L���X�g����
CObject2D *pObj2D = (CObject2D*)g_pObj;
pObj2D->Setpos
}

if(g_pObj)
{//�I��
g_pObj->Uninit();
g_pObj = nullptr;
}

//�|�C���^�̂��炵��

 CObject **ppObject = GetObject();

//�|�C���^���̂��{�{���Ă��炷���@
for(int nCnt = 0; nCnt < �ő吔; nCnt++,ppObject++;)
{
	if((*(ppObject) != nullptr )
	{
		(*ppObject)-> Updata();
	}
}

//�z��̐����𑫂��ԍ������炷���@
for(int nCnt = 0; nCnt < �ő吔; nCnt++;)
{
	if((*(ppObject + nCnt)) != nullptr )
	{
		(*(ppObject + nCnt))-> Updata();
	}
}

g_pObject[nCnt]->Setpos({ 100.0f*nCnt,50.0f,0.0f });

// �����̃g���r�A //
NULL�`�F�b�N�@�v���������@�厖�ł�
*/