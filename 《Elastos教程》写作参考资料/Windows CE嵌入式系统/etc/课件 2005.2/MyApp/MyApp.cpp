// MyApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <ceddk.h>
#include <commctrl.h>
#include <devload.h>

#pragma comment(lib, "ceddk.lib")
#pragma comment(lib, "commctrl.lib")

#define MAX_LOADSTRING 100

#define IDC_CMDBAR 0x101
HWND hWndCmdBar;


#pragma comment(lib, "ceddk.lib")


#define ELECTROMOTOR_MAJOR 140

#define ELECTROMOTOR_6 (ELECTROMOTOR_1 + 6)
#define ELECTROMOTOR_7 (ELECTROMOTOR_1 + 7)

#define electromotor_sle (*(volatile unsigned long *)ELECTROMOTOR_GPACON)
#define electromotor_sle_data (*(volatile unsigned long *)ELECTROMOTOR_GPADATA)


unsigned long ELECTROMOTOR_1;
unsigned long ELECTROMOTOR_GPACON;
unsigned long ELECTROMOTOR_GPADATA;


DWORD MyWrite( DWORD hOpenContext, LPCVOID pBuffer, DWORD Count )
{
	OutputDebugString(L"Control From App\r\n");
	
    /* send message to control eletromotor */
	(*(volatile unsigned char *) ELECTROMOTOR_6) = *(unsigned char *)pBuffer;
    return 1;
}



void WriteToDriver( );
void ControlMotor( );
void HandleActivate( );

#define IOCTL_DRIVER_DEMO   42

// Global Variables:
HINSTANCE hInst;            // current instance
TCHAR szTitle[MAX_LOADSTRING];                        // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];                        // The title bar text

// Forward declarations of functions included in this code module:
ATOM            MyRegisterClass(HINSTANCE hInstance);
BOOL            InitInstance(HINSTANCE, int);
LRESULT CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPTSTR     lpCmdLine,
				   int       nCmdShow)
{
    // TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MYAPP);
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = 0;
    wc.lpszClassName = szWindowClass;
	
	return RegisterClass(&wc);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
		0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND   - process the application menu
//  WM_PAINT   - Paint the main window
//  WM_DESTROY   - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	
	switch (message) 
	{
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case ID_FILE_EXIT:
			PostQuitMessage(0);
            break;
		case ID_DRIVER_WRITE:
			WriteToDriver( );
            break;
		case ID_DRIVER_READ:
			ControlMotor( );
            break;
		case ID_DRIVER_IOCTL:
			HandleActivate( );
            break;
		}
		break;
		case WM_CREATE:
			hWndCmdBar=CommandBar_Create(hInst,hWnd,IDC_CMDBAR);
			CommandBar_InsertMenubar(hWndCmdBar,hInst,IDR_MENU,0);
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, _tcslen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WriteToDriver( )
{
	DWORD dwWritten;
	int count;
	int ret;

	HANDLE hDrv = CreateFile(L"DEM1:",GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE == hDrv) 
	{
		OutputDebugString(L"Failed to open Driver...\r\n");
		return ;
	}


	for (int i = 0; i < 100; i++)
	{
		ret = 0x7;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0x3;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0xb;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0x9;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0xd;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0xc;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
		ret = 0xe;	
		count = WriteFile(hDrv, &ret, 1, &dwWritten, NULL);
		Sleep(10);
	}

	CloseHandle(hDrv);
}


// This function control Motorl Directly
void ControlMotor( )
{

	DWORD ret, count;

	OutputDebugString(L"Electronic Motor - DEM_Init - Context: ");

	PHYSICAL_ADDRESS GPACON = {0x56000000, 0}; 
	PHYSICAL_ADDRESS GPADATA = {0x56000004, 0}; 
	PHYSICAL_ADDRESS EMOTOR_1 = {0x10000000, 0}; 

 
	// Eelctronic motor physical address
	ELECTROMOTOR_GPACON = (ULONG)MmMapIoSpace(GPACON, 4, FALSE);
	ELECTROMOTOR_GPADATA = (ULONG)MmMapIoSpace(GPADATA, 4, FALSE);
	
	ELECTROMOTOR_1 = (ULONG)MmMapIoSpace(EMOTOR_1, 8, FALSE);
	

	/* select NGCS2 */
	electromotor_sle |= 0x2000;
	electromotor_sle_data &= (~0x2000);

	for (int i = 0; i < 100; i++)
	{
		ret = 0x7;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0x3;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0xb;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0x9;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0xd;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0xc;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
		ret = 0xe;	
		count = MyWrite(1, &ret, 1);
		Sleep(10);
	}


	electromotor_sle &= (~0x2000);
	electromotor_sle_data |= 0x2000;
	
}

// This function is used to load device drvier
void HandleActivate( )
{
	TCHAR szDevKey[] = _T("Drivers\\Motor");
	TCHAR szDllName[] = _T("MyDriver.DLL");
	TCHAR szPrefix[] = _T("DEM");
	HKEY hKey;
	DWORD dwDisposition;

	// Open the registry key and add these values
	RegCreateKeyEx( HKEY_LOCAL_MACHINE,
		szDevKey,
		0,
		_T("MotorDriver"),
		REG_OPTION_VOLATILE,
		0,
		NULL,
		&hKey,
		&dwDisposition );

	// Create the key specifying the dll name
	RegSetValueEx( hKey,
		_T("Dll"),
		0,
		REG_SZ,
		(const BYTE*)szDllName,
		sizeof(szDllName) );

	// Create the key specifying the Prefix
	RegSetValueEx( hKey,
		_T("Prefix"),
		0,
		REG_SZ,
		(const BYTE*)szPrefix,
		sizeof(szPrefix) );

	RegCloseKey( hKey );

	ActivateDeviceEx( szDevKey, NULL, 0, NULL );


	OutputDebugString(L"Activating Device\r\n");
}
