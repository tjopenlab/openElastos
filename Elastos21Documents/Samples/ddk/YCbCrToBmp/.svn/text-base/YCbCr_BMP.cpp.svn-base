#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include <deprecated.h>

#define UINT unsigned int
#define MAX_BYTE (1280*960*2)
//point of YCbCrBuffer
unsigned char *g_pY;
unsigned char *g_pCb;
unsigned char *g_pCr;
//the sum of the bmp pic pixels
UINT g_USum;
//bmp pic Width and Height
int g_iWidth;
int g_iHeight;
//buffer
unsigned char g_pYCbCrBuffer[MAX_BYTE];
unsigned char *g_pRGB888Buffer;
//bmp file header
BITMAPFILEHEADER g_BmfHeader;
BITMAPINFOHEADER g_BmiHeader;

UINT ReadYCbCrFile(char*fname)
{
    UINT sumOfFile;
    FILE* YCbCrFile = fopen(fname, "rb");
    if(NULL == YCbCrFile){
        printf("open %s fail!\n", fname);
        return 0;
    }
    sumOfFile = fread(g_pYCbCrBuffer, 1, MAX_BYTE, YCbCrFile);
    fclose(YCbCrFile);
    return sumOfFile;
}

BOOL AcquireVariableInfo(UINT sumByte)
{
    g_USum = sumByte / 2;
    switch(g_USum){
        case 240*320:
            g_iWidth = 320;
            g_iHeight = 240;
            break;
        case 480*640:
            g_iWidth = 640;
            g_iHeight = 480;
            break;
        case 960*1280:
            g_iWidth = 1280;
            g_iHeight = 960;
            break;
        default:
            printf("There is unfixble size of pic.\n");
            return FALSE;
    }

    g_pRGB888Buffer = (unsigned char *)malloc(3 * g_USum);
    g_pY = g_pYCbCrBuffer;
    g_pCb = g_pYCbCrBuffer + g_USum;
    g_pCr = g_pYCbCrBuffer + g_USum + g_USum / 2;
    return TRUE;
}

void TurnYCbCrToRGB888()
{
    int RGB_R, RGB_G, RGB_B;
    int YCbCr_Y, YCbCr_Cb, YCbCr_Cr;
    int index;
    for (int j = 0; j < g_iHeight; j++) {
        for (int i = 0; i < g_iWidth; i++) {
            YCbCr_Y = (int)g_pY[i + j * g_iWidth];
            YCbCr_Cb =(int)g_pCb[(i + j * g_iWidth) / 2];
            YCbCr_Cr =(int)g_pCr[(i + j * g_iWidth) / 2];

            RGB_R = (int)(YCbCr_Y + 1.402 * (YCbCr_Cr - 128));
            RGB_G = (int)(YCbCr_Y - 0.344 * (YCbCr_Cb - 128) - 0.714 * (YCbCr_Cr - 128));
            RGB_B = (int)(YCbCr_Y + 1.773 * (YCbCr_Cb - 128));

            if (RGB_R < 0) RGB_R = 0;
            if (RGB_R > 0xFF) RGB_R = 0xFF;

            if (RGB_G < 0) RGB_G = 0;
            if (RGB_G > 0xFF) RGB_G = 0xFF;

            if (RGB_B < 0) RGB_B = 0;
            if (RGB_B > 0xFF) RGB_B = 0xFF;

            index = 3 * (i + ((g_iHeight-1)-j) * g_iWidth);
            g_pRGB888Buffer[index] = (unsigned char)RGB_B;
            g_pRGB888Buffer[index + 1] = (unsigned char)RGB_G;
            g_pRGB888Buffer[index + 2] = (unsigned char)RGB_R;

        }
    }
}


void setBmpFileHead(BITMAPFILEHEADER *pBmfHeader, BITMAPINFOHEADER *pBmiHeader)
{
    pBmfHeader->bfType = 0x4D42;
    pBmfHeader->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
                        + 3 * g_USum;
    pBmfHeader->bfReserved1 = 0;
    pBmfHeader->bfReserved2 = 0;
    pBmfHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    pBmiHeader->biSize = 0x28;
    pBmiHeader->biWidth = g_iWidth;
    pBmiHeader->biHeight = g_iHeight;
    pBmiHeader->biPlanes = 1;
    pBmiHeader->biBitCount = 24;
    pBmiHeader->biCompression = 0;
    pBmiHeader->biSizeImage = 3 * g_USum;
    pBmiHeader->biXPelsPerMeter = 0;
    pBmiHeader->biYPelsPerMeter = 0;
    pBmiHeader->biClrUsed = 0;
    pBmiHeader->biClrImportant = 0;
}

int SaveBmpFile(char *fname)
{
    if(0 == _access(fname, 0)) {
        printf("There already have file nameed %s!\n", fname);
        printf("Save %s file fail!\n", fname);
        return 1;
    }
    FILE* BMPFile = fopen(fname, "wb");
    if(NULL == BMPFile){
        printf("Save %s file fail!\n", fname);
        return 1;
    }
    fwrite((void *)&g_BmfHeader, 1, sizeof(BITMAPFILEHEADER), BMPFile);
    fwrite((void *)&g_BmiHeader, 1, sizeof(BITMAPINFOHEADER), BMPFile);
    fwrite((void *)g_pRGB888Buffer, 1, 3 * g_USum, BMPFile);
    fclose(BMPFile);
    return 0;
}

int TurnDatToBMP(char *argv)
{

    printf("Turning %s to BMP file.\n", argv);

    UINT USum = ReadYCbCrFile(argv);
    if(0 == USum)
        return -1;

    if(!AcquireVariableInfo(USum)){
        return -1;
    }

    TurnYCbCrToRGB888();
    setBmpFileHead(&g_BmfHeader, &g_BmiHeader);
    int lenth = strlen(argv);
    strcpy(&argv[lenth-4], ".bmp");
    if(0 != SaveBmpFile(argv)){
        return -1;
    }
    free(g_pRGB888Buffer);
    printf("Produce file: %s succeed\n", argv);
    return 0;
}

//If the function succeeds, the return value is zero.
//and if no more file be finded filename value is NULL
int GetFileFromDir(BOOL on_off,
                   char *scDirPath,
                   char *FilePostfix,
                   char *filename)
{
    WIN32_FIND_DATA FindFileData;
    static HANDLE hFind;
    int lenth;
    wchar_t wscDirPath[MAX_PATH];
    wchar_t wscFilePostfix[MAX_PATH];
    if(NULL == scDirPath){
        wcscpy(wscDirPath, L".\\*");
    } else {
        mbstowcs(wscDirPath, scDirPath, MAX_PATH*sizeof(wchar_t));
        wcscat(wscDirPath, L"*");
    }
    mbstowcs(wscFilePostfix, FilePostfix, MAX_PATH*sizeof(wchar_t));
    //close the search
    if(!on_off){
        FindClose(hFind);
        *filename = NULL;
        hFind = NULL;
        return 0;
    }
    //the first search
    if(NULL == hFind) {
        hFind = FindFirstFile(wscDirPath, &FindFileData);
        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf ("Can not find file. GetLastError reports %d\n", GetLastError ());
            *filename = NULL;
            hFind = NULL;
            return -1;
        }
        lenth = wcslen(FindFileData.cFileName);
        if(0 == wcscmp(&FindFileData.cFileName[lenth-4], wscFilePostfix)){
            if(NULL == scDirPath) {
                wcstombs(filename, FindFileData.cFileName, MAX_PATH*sizeof(wchar_t));
            } else {
                strcpy(filename, scDirPath);
                wcstombs(&filename[strlen(filename)], FindFileData.cFileName, MAX_PATH*sizeof(wchar_t));
            }
            return 0;
        }
    }
    //find more target file
    for(;0 != FindNextFile(hFind, &FindFileData);) {
        lenth = wcslen(FindFileData.cFileName);
        if(0 == wcscmp(&FindFileData.cFileName[lenth-4], wscFilePostfix)){
            if(NULL == scDirPath) {
                wcstombs(filename, FindFileData.cFileName, MAX_PATH*sizeof(wchar_t));
            } else {
                strcpy(filename, scDirPath);
                wcstombs(&filename[strlen(filename)], FindFileData.cFileName, MAX_PATH*sizeof(wchar_t));
            }
            return 0;
        }
    }

    FindClose(hFind);
    *filename = NULL;
    hFind = NULL;
    return -1;
}

int main(int argc, char *argv[])
{
    char *scDirPath = NULL;
    if(argc > 1){
        int lenth = strlen(argv[1]);
        if('*' == argv[1][lenth-1]){
            argv[1][lenth-1] = '\0';
            scDirPath = argv[1];
            if ('\0' == *scDirPath) {
                scDirPath = NULL;
            }
        } else {
            if(0 != TurnDatToBMP(argv[1])) {
                printf("format: YCbCr_BMP.exe [path\\*]|[file name]\n");
            }
            return 0;
        }
    }
    char filename[MAX_PATH];
    for(; 0 == GetFileFromDir(TRUE, scDirPath, ".dat", filename);){
        TurnDatToBMP(filename);
    }
    return 0;
}
