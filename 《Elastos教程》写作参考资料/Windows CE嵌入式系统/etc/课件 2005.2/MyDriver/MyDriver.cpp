// MyDriver.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <ceddk.h>
#include "led_ioctl.h"

#pragma comment(lib, "ceddk.lib")



#define ELECTROMOTOR_MAJOR 140

#define ELECTROMOTOR_6 (ELECTROMOTOR_1 + 6)
#define ELECTROMOTOR_7 (ELECTROMOTOR_1 + 7)

#define electromotor_sle (*(volatile unsigned long *)ELECTROMOTOR_GPACON)
#define electromotor_sle_data (*(volatile unsigned long *)ELECTROMOTOR_GPADATA)


unsigned long ELECTROMOTOR_1;
unsigned long ELECTROMOTOR_GPACON;
unsigned long ELECTROMOTOR_GPADATA;




DWORD DEM_Init(LPCTSTR pContext, LPCVOID lpvBusContext);
BOOL DEM_Deinit( DWORD hDeviceContext );
DWORD DEM_Open( DWORD hDeviceContext, DWORD AccessCode, DWORD ShareMode );
BOOL DEM_Close( DWORD hOpenContext );
BOOL DEM_IOControl( DWORD hOpenContext, DWORD dwCode, PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut, PDWORD pdwActualOut );
void DEM_PowerUp( DWORD hDeviceContext );
void DEM_PowerDown( DWORD hDeviceContext );
DWORD DEM_Read( DWORD hOpenContext, LPVOID pBuffer, DWORD Count );
DWORD DEM_Write( DWORD hOpenContext, LPCVOID pBuffer, DWORD Count );
DWORD DEM_Seek( DWORD hOpenContext, long Amount, WORD Type );


BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"MyDriver - DLL_PROCESS_ATTACH\r\n");
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugString(L"MyDriver - DLL_PROCESS_DETACH\r\n");
		break;
	case DLL_THREAD_ATTACH:
		OutputDebugString(L"MyDriver - DLL_THREAD_ATTACH\r\n");
		break;
	case DLL_THREAD_DETACH:
		OutputDebugString(L"MyDriver - DLL_THREAD_DETACH\r\n");
		break;
	}
	return TRUE;
}

DWORD DEM_Init( LPCTSTR pContext, LPCVOID lpvBusContext)
{
	OutputDebugString(L"Electronic Motor Driver Init");

	PHYSICAL_ADDRESS GPACON = {0x56000000, 0}; 
	PHYSICAL_ADDRESS GPADATA = {0x56000004, 0}; 
	PHYSICAL_ADDRESS EMOTOR_1 = {0x10000000, 0}; 

 
	// Eelctronic motor physical address
	ELECTROMOTOR_GPACON = (ULONG)MmMapIoSpace(GPACON, 4, FALSE);
	ELECTROMOTOR_GPADATA = (ULONG)MmMapIoSpace(GPADATA, 4, FALSE);
	
	ELECTROMOTOR_1 = (ULONG)MmMapIoSpace(EMOTOR_1, 8, FALSE);


	return TRUE;
}

BOOL DEM_Deinit( DWORD hDeviceContext )
{
	OutputDebugString(L"MyDriver - DEM_Deinit\r\n");

	return TRUE;
}

DWORD DEM_Open( DWORD hDeviceContext, DWORD AccessCode, DWORD ShareMode )
{
	OutputDebugString(L"MyDriver - DEM_Open\n");

	/* select NGCS2 */
	electromotor_sle |= 0x2000;
	electromotor_sle_data &= (~0x2000);

	return TRUE;
}

BOOL DEM_Close( DWORD hOpenContext )
{
	OutputDebugString(L"MyDriver - DEM_Close\r\n");

	electromotor_sle &= (~0x2000);
	electromotor_sle_data |= 0x2000;
	
	return TRUE;
}

BOOL DEM_IOControl( DWORD hOpenContext, DWORD dwCode, PBYTE pBufIn, DWORD dwLenIn, PBYTE pBufOut, DWORD dwLenOut, PDWORD pdwActualOut )
{
	OutputDebugString(L"MyDriver - DEM_IOControl\r\n");
	return TRUE;
}

void DEM_PowerUp( DWORD hDeviceContext )
{
	OutputDebugString(L"MyDriver - DEM_PowerUp\r\n");
}

void DEM_PowerDown( DWORD hDeviceContext )
{
	OutputDebugString(L"MyDriver - DEM_PowerDown\r\n");
}

DWORD DEM_Read( DWORD hOpenContext, LPVOID pBuffer, DWORD Count )
{
	OutputDebugString(L"MyDriver - DEM_Read\r\n");
	return NULL;
}

DWORD DEM_Write( DWORD hOpenContext, LPCVOID pBuffer, DWORD Count )
{
	OutputDebugString(L"MyDriver - DEM_Write\r\n");
	
	
    /* send message to control eletromotor */
	(*(volatile unsigned char *) ELECTROMOTOR_6) = *(unsigned char *)pBuffer;
    return 1;

}

DWORD DEM_Seek( DWORD hOpenContext, long Amount, WORD Type )
{
	OutputDebugString(L"MyDriver - DEM_Seek\r\n");
	
	return 0;
}

