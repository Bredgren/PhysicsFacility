// PhysicsFacilityGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PhysicsFacilityGame.h"
#include "physfacengine.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

PFEngine pfe = PFEngine("fake");

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

  // Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PHYSICSFACILITYGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PHYSICSFACILITYGAME));

  bool quit = false;
  while (!quit) {
		// check for messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// handle or dispatch messages
			if ( msg.message == WM_QUIT ) {
				quit = TRUE;
			} else {
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		} else {
      pfe.Step();
      pfe.Draw();
      SwapBuffers(glcontext.hDC);
		}
  }

	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PHYSICSFACILITYGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PHYSICSFACILITYGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
  HWND hWnd;

  hInst = hInstance; // Store instance handle in our global variable

  RECT r = {0, 0, 1024, 768};
  AdjustWindowRect(&r, WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0);

  hWnd = CreateWindow(szWindowClass, szTitle, 
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU| WS_MINIMIZEBOX,
    CW_USEDEFAULT, 0, r.right-r.left, r.bottom-r.top, NULL, NULL, hInstance, NULL);

  if (!hWnd) {
    return FALSE;
  }

  glcontext.init(hWnd);

  if (!pfe.init())
    return FALSE;

  if (!pfe.LoadLevel("fake"))
    return FALSE;
 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	//HDC hdc;

	switch (message) {
  case WM_KEYDOWN: {
      switch(wParam) {
      case 'W':
        pfe.SetActorAction(0, kMoveForward);
        break;
      case 'R':
        pfe.SetActorAction(0, kMoveBackward);
        break;
      case 'A':
        pfe.SetActorAction(0, kTurnLeft);
        break;
      case 'S':
        pfe.SetActorAction(0, kTurnRight);
        break;
      default: break;
      }
      break;
  }
  case WM_KEYUP: {
    switch(wParam) {
    case 'W':
    case 'R':
      pfe.SetActorAction(0, kMoveStop);
      break;
    case 'A':
    case 'S':
      pfe.SetActorAction(0, kTurnStop);
      break;
    default: break;
    }
    break;
  }
  case WM_MOUSEMOVE: {
    int x = (short)LOWORD(lParam);
    int y = (short)HIWORD(lParam);
    pfe.SetActorAction(0, kArmPosition, x, y);
    break;
  }
	case WM_DESTROY:
    glcontext.purge();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}