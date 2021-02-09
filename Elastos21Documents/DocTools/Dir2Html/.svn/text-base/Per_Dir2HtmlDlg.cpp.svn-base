// Per_Dir2HtmlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Per_Dir2Html.h"
#include "Per_Dir2HtmlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "Sure.h"
#include <Windows.h>
#include <Afxtempl.h>

CArray<CString,CString> ptArray;

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

// Unicode 转换成UTF-8 
void UnicodeToUTF_8(char* pOut,WCHAR* pText)
{
	 // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	 char* pchar = (char *)pText;

	 pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	 pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	 pOut[2] = (0x80 | (pchar[0] & 0x3F));
	
	 return;
}    
     

// GB2312 转换成　Unicode
void Gb2312ToUnicode(WCHAR* pOut,char *gbBuffer)
{
	  ::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,pOut,1);
	  return;
}
     

//GB2312 转为 UTF-8
void GB2312ToUTF_8(char * pOut,char *pText, int pLen)
{
      char buf[4];
	  char* rst;
      rst = pOut;
      memset(buf,0,4);
      memset(rst,0,pLen + (pLen >> 2) + 2);
           
      int i = 0;
      int j = 0;      
      while(i < pLen)
      {
            //如果是英文直接复制就可以
            if( *(pText + i) >= 0)
            {
                  rst[j++] = pText[i++];
            }
            else
            {
                   WCHAR pbuffer;
                   Gb2312ToUnicode(&pbuffer,pText+i);
                           
                   UnicodeToUTF_8(buf,&pbuffer);
                           
                   unsigned short int tmp = 0;
                   tmp = rst[j] = buf[0];
                   tmp = rst[j+1] = buf[1];
                   tmp = rst[j+2] = buf[2];
                           
                           
                   j += 3;
                   i += 2;
            }
	 }
           rst[j] = '\0';       
           return;
}



//  int urlEncode(char *url)
//  功   能：编码。类似于java的urlEncode。就是把char pure[3] = {0xC4,0xE3,0x00};
//  这样的编码成char encode = "%C4%E3";
//  参   数：char * url需要转码的字符串，并使用这个字符串保存编码完的url
int urlEncode(char *url)
{
    char urlencoded[2000];
    char *cur_char = url, *urlencode = urlencoded;
 
    int curHex = 0;
    memset(urlencoded, 0x00, sizeof(urlencoded));
    if(strlen(url) == 0)
    {
        return 0;
    }
    do
    {
		if(*cur_char == 0x20)
			*urlencode = 0x2B;    //把空格换成+
		else 
			if(*cur_char == 0x3F)     //?问号在get请求的时候会引起错觉
			{
				*urlencode = 0x25;
				urlencode++;
				*urlencode = 0x33;
				urlencode;
				*urlencode = 0x46;
				urlencode++;
			}
			else 
			{
				if((*cur_char >= 65 && *cur_char <= 90) || (*cur_char >= 97 && *cur_char <= 122) || (*cur_char >= 48 && *cur_char <= 58) || *cur_char == 38 || (*cur_char >= 45 && *cur_char <= 47) || *cur_char == 58 || *cur_char == 61 || *cur_char == 63 || *cur_char == 126)
				{
					*urlencode = *cur_char;
				}
				else
				{
					//先加上一个百分号(%)
					*urlencode = 0x25;
					urlencode++;
					//转换高位
					curHex = ((*cur_char)&0xF0)>>4;
					if(curHex >= 0xA)
						 curHex = curHex - 0xA + 0x41;
					else
						 curHex = curHex + 0x30;
					*urlencode = curHex;
					urlencode++;
					//转换低位
					curHex = (*cur_char)&0xF;
					if(curHex >= 0xA)
						curHex = curHex - 0xA + 0x41;
					else
						curHex = curHex + 0x30;
					*urlencode = curHex;
				}
			}
			urlencode++;
			cur_char ++;
    }while(*cur_char);
	strcpy(url, urlencoded);
	return strlen(url);
} 


int Create_DEEP_HTML_Sub( char dir[],char name[],BOOL check,int m_type)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[2000];
	char pIn[2000];
	char pIn1[2000];
	strcpy(szName,dir);
	strcat(szName,"*.*");

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	} 
	else 
	{
		char szName1[2000];
		int ntype;
		strcpy(szName1,dir);
		strcat(szName1,name);

		int fh;
		fh = _creat(szName1, _S_IWRITE);

		TCHAR sz[2000] = "<html>\r\n<table align=\"center\" width=\"100%%\" cellspacing=\"0\" border=\"1\">\r\n<tr bgcolor=\"#EEEEEE\"><td align=\"center\"><b>文件名/文件夹名</b></td><td align=\"center\"><b>文件说明</b></td><td align=\"center\"><b>修改日期</b></td><td align=\"center\"><b>修改时间</b></td></tr>\r\n";
		_write(fh, sz, lstrlen(sz));

		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".") ==0)
				continue;
			SYSTEMTIME stUTC, lpSystemTime;
			FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
			CString strdate;
			strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
			CString strtime;
			strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,
				lpSystemTime.wSecond);
			CString strsize;
			double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
			strsize.Format("%.1f",fsize);

			ntype = 0;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				ntype = 1; //文件夹

			if(check)
			{
				strcpy(sz,"<tr><td>");
				if(ntype == 1)
				{
					strcat(sz,"<a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
						strcat(sz,"/");
						strcat(sz,name);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						strcat(pIn,"/");
						strcat(pIn,name);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
					strcat(sz,"\">");
				}
			}
			else
			{
				if(ntype == 1)
				{
					strcpy(sz,"<tr><td><a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
						strcat(sz,"/");
						strcat(sz,name);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						strcat(pIn,"/");
						strcat(pIn,name);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
				}
				else
				{
					strcpy(sz,"<tr><td><a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
				}
				strcat(sz,"\">");
			}
			strcat(sz,FindFileData.cFileName);
			strcat(sz,"</a></td><td>");
			if(ntype == 0)
			{
				
				strcat(sz,strsize.GetBuffer(1));
				strcat(sz,"KB</td><td>");
			}
			else
			{
				if(strcmp(FindFileData.cFileName,"..") ==0)
				{
					strcat(sz,"返回上一级目录");
				}
				else
				{
					strcat(sz,"文件夹");
				}
				strcat(sz,"</td><td>");
			}
			strcat(sz,strdate.GetBuffer(1));
			strcat(sz,"</td><td>");
			strcat(sz,strtime.GetBuffer(1));
			strcat(sz,"</td></tr>\r\n");
			_write(fh, sz, lstrlen(sz));
			if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0)
			{
				if(ntype == 1)
				{
					strcpy(sz,dir);
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"\\");
					if(!Create_DEEP_HTML_Sub(sz,name,check,m_type))
					{
						_close(fh);
						DeleteFile(szName1);
						FindClose(hFind);
						return 0;
					}
				}
			}
		}while(FindNextFile(hFind,&FindFileData));
		strcpy(sz,"</table>\r\n<p>&nbsp;&nbsp;请设使用IE浏览器<p>\r\n</html>");
		_write(fh, sz, lstrlen(sz));
        _close(fh);

		FindClose(hFind);
		return 1;
	}

}

int Create_DEEP_HTML_ALL( char dir[],char name[],BOOL check,int m_type)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[2000];
	char pIn[2000];
	char pIn1[2000];
	strcpy(szName,dir);
	strcat(szName,"*.*");

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	} 
	else 
	{
        //创建dirs
		int ntype;
		char szName1[2000];
		strcpy(szName1,dir);
		strcat(szName1,name);

		int fh;
		fh = _creat(szName1, _S_IWRITE);
		TCHAR sz[2000] = "<html>\r\n<table align=\"center\" width=\"100%%\" cellspacing=\"0\" border=\"1\">\r\n<tr bgcolor=\"#EEEEEE\"><td align=\"center\"><b>文件名/文件夹名</b></td><td align=\"center\"><b>文件说明</b></td><td align=\"center\"><b>修改日期</b></td><td align=\"center\"><b>修改时间</b></td></tr>\r\n";
		_write(fh, sz, lstrlen(sz));

		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0)
			{
				CString strsize;
				double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
				strsize.Format("%.1f",fsize);
				SYSTEMTIME stUTC, lpSystemTime;
				FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
				CString strdate;
				strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
				CString strtime;
				strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

				ntype = 0;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					ntype = 1; //文件夹

                
				if(check)
				{
					strcpy(sz,"<tr><td>");
					if(ntype == 1)
					{
						strcat(sz,"<a href=\"");
						if(m_type == 1)
						{
							strcat(sz,FindFileData.cFileName);
							strcat(sz,"/");
							strcat(sz,name);
						}
						else
						{
							strcpy(pIn,FindFileData.cFileName);
							strcat(pIn,"/");
							strcat(pIn,name);
							GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
							urlEncode(pIn1);
							strcat(sz,pIn1);
						}
						strcat(sz,"\">");
					}
				}
				else
				{
					if(ntype == 1)
					{
						strcpy(sz,"<tr><td><a href=\"");
						if(m_type == 1)
						{
							strcat(sz,FindFileData.cFileName);
							strcat(sz,"/");
							strcat(sz,name);
						}
						else
						{
							strcpy(pIn,FindFileData.cFileName);
							strcat(pIn,"/");
							strcat(pIn,name);
							GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
							urlEncode(pIn1);
							strcat(sz,pIn1);
						}
					}
					else
					{
						strcpy(sz,"<tr><td><a href=\"");
						if(m_type == 1)
						{
							strcat(sz,FindFileData.cFileName);
						}
						else
						{
							strcpy(pIn,FindFileData.cFileName);
							GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
							urlEncode(pIn1);
							strcat(sz,pIn1);
						}
					}
					strcat(sz,"\">");
				}
				strcat(sz,FindFileData.cFileName);
				strcat(sz,"</a></td><td>");
				if(ntype == 0)
				{
					strcat(sz,strsize.GetBuffer(1));
					strcat(sz,"KB</td><td>");
				}
				else
				{
					strcat(sz,"文件夹");
					strcat(sz,"</td><td>");
				}
				strcat(sz,strdate.GetBuffer(1));
				strcat(sz,"</td><td>");
				strcat(sz,strtime.GetBuffer(1));
				strcat(sz,"</td></tr>\r\n");
				_write(fh, sz, lstrlen(sz));

                if(ntype == 1)
				{
					strcpy(sz,dir);
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"\\");
					if(!Create_DEEP_HTML_Sub(sz,name,check,m_type))
					{
						_close(fh);
						DeleteFile(szName1);
						FindClose(hFind);
						return 0;
					}
				}
			}
		}while(FindNextFile(hFind,&FindFileData));
		strcpy(sz,"</table>\r\n<p>&nbsp;&nbsp;请设使用IE浏览器<p>\r\n</html>");
		_write(fh, sz, lstrlen(sz));
        _close(fh);

		FindClose(hFind);
		return 1;
	}

}


int Create_DEEP_SELECT_Sub( char dir[],char name[],char select[],BOOL check,int m_type)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[2000];
	int ntype;
	char szName1[2000];
	char pIn[2000];
	char pIn1[2000];
	strcpy(szName,dir);
	strcat(szName,"*.*");


	strcpy(szName1,dir);
	strcat(szName1,name);
	TCHAR sz[2000] = "<html>\r\n<table align=\"center\" width=\"100%%\" cellspacing=\"0\" border=\"1\">\r\n<tr bgcolor=\"#EEEEEE\"><td align=\"center\"><b>文件名/文件夹名</b></td><td align=\"center\"><b>文件说明</b></td><td align=\"center\"><b>修改日期</b></td><td align=\"center\"><b>修改时间</b></td></tr>\r\n";
	int fh;
	fh = _creat(szName1, _S_IWRITE);
	_write(fh, sz, lstrlen(sz));

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		_close(fh);
		return 0;
	} 
	else 
	{
        //创建dirs
		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".") ==0)
				continue;

			CString strsize;
			double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
			strsize.Format("%.1f",fsize);
			SYSTEMTIME stUTC, lpSystemTime;
			FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
			CString strdate;
			strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
			CString strtime;
			strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

			ntype = 0;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				ntype = 1; //文件夹

            if(ntype == 1)
			{
				strcpy(sz,"<tr><td><a href=\"");
				if(m_type == 1)
				{
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"/");
					strcat(sz,name);
				}
				else
				{
					strcpy(pIn,FindFileData.cFileName);
					strcat(pIn,"/");
					strcat(pIn,name);
					GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
					urlEncode(pIn1);
					strcat(sz,pIn1);
				}
				strcat(sz,"\">");
				strcat(sz,FindFileData.cFileName);
				strcat(sz,"</a></td><td>");
				if(strcmp(FindFileData.cFileName,"..") ==0)
				{
					strcat(sz,"返回上一级目录");
				}
				else
				{
					strcat(sz,"文件夹");
				}
				strcat(sz,"</td><td>");
				strcat(sz,strdate.GetBuffer(1));
				strcat(sz,"</td><td>");
				strcat(sz,strtime.GetBuffer(1));
				strcat(sz,"</td></tr>\r\n");
				_write(fh, sz, lstrlen(sz));

				if(strcmp(FindFileData.cFileName,"..") != 0)
				{
					strcpy(sz,dir);
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"\\");

					if(!Create_DEEP_SELECT_Sub(sz,name,select,check,m_type))
					{
						_close(fh);
						DeleteFile(szName1);
						FindClose(hFind);
						return 0;
					}
				}
			}
		}while(FindNextFile(hFind,&FindFileData));
		
		FindClose(hFind);
	}


	strcpy(szName,dir);
	strcat(szName,select);
	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		_close(fh);
		return 0;
	} 
	else 
	{
		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".") ==0)
				continue;

			CString strsize;
			double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
			strsize.Format("%.1f",fsize);
			SYSTEMTIME stUTC, lpSystemTime;
			FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
			CString strdate;
			strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
			CString strtime;
			strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

			ntype = 0;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				ntype = 1; //文件夹

			if(ntype == 0)
			{
				strcpy(sz,"<tr><td>");
				if(!check)
				{
					strcat(sz,"<a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
						strcat(sz,"/");
						strcat(sz,name);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						strcat(pIn,"/");
						strcat(pIn,name);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
					strcat(sz,"\">");
				}
				strcat(sz,FindFileData.cFileName);
				strcat(sz,"</a></td><td>");
				strcat(sz,strsize.GetBuffer(1));
				strcat(sz,"KB</td><td>");
				strcat(sz,strdate.GetBuffer(1));
				strcat(sz,"</td><td>");
				strcat(sz,strtime.GetBuffer(1));
				strcat(sz,"</td></tr>\r\n");
				_write(fh, sz, lstrlen(sz));
			}
		}while(FindNextFile(hFind,&FindFileData));
		strcpy(sz,"</table>\r\n<p>&nbsp;&nbsp;请设使用IE浏览器<p>\r\n</html>");
		_write(fh, sz, lstrlen(sz));
        _close(fh);
		
		FindClose(hFind);

        return 1;
	}

}

int Create_DEEP_SELECT(char dir[],char name[],char select[],BOOL check,int m_type)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[2000];
	int ntype;
	char szName1[2000];
	char pIn[2000];
	char pIn1[2000];
	strcpy(szName,dir);
	strcat(szName,"*.*");
	strcpy(szName1,dir);
	strcat(szName1,name);

	int fh;
	fh = _creat(szName1, _S_IWRITE);
	TCHAR sz[2000] = "<html>\r\n<table align=\"center\" width=\"100%%\" cellspacing=\"0\" border=\"1\">\r\n<tr bgcolor=\"#EEEEEE\"><td align=\"center\"><b>文件名/文件夹名</b></td><td align=\"center\"><b>文件说明</b></td><td align=\"center\"><b>修改日期</b></td><td align=\"center\"><b>修改时间</b></td></tr>\r\n";
	_write(fh, sz, lstrlen(sz));

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		_close(fh);
		return 0;
	} 
	else 
	{
        //创建dirs
		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0)
			{
				CString strsize;
				double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
				strsize.Format("%.1f",fsize);
				SYSTEMTIME stUTC, lpSystemTime;
				FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
				CString strdate;
				strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
				CString strtime;
				strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

				ntype = 0;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					ntype = 1; //文件夹

                if(ntype == 1)
				{
					strcpy(sz,"<tr><td><a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
						strcat(sz,"/");
						strcat(sz,name);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						strcat(pIn,"/");
						strcat(pIn,name);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
					strcat(sz,"\">");
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"</a></td><td>");
					strcat(sz,"文件夹");
					strcat(sz,"</td><td>");
					strcat(sz,strdate.GetBuffer(1));
					strcat(sz,"</td><td>");
					strcat(sz,strtime.GetBuffer(1));
					strcat(sz,"</td></tr>\r\n");
					_write(fh, sz, lstrlen(sz));

					strcpy(sz,dir);
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"\\");

					if(!Create_DEEP_SELECT_Sub(sz,name,select,check,m_type))
					{
						_close(fh);
						DeleteFile(szName1);
						FindClose(hFind);
						return 0;
					}
				}
			}
		}while(FindNextFile(hFind,&FindFileData));
		
		FindClose(hFind);
	}


	strcpy(szName,dir);
	strcat(szName,select);
	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		_close(fh);
		return 0;
	} 
	else 
	{
		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0)
			{
				CString strsize;
				double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
				strsize.Format("%.1f",fsize);
				SYSTEMTIME stUTC, lpSystemTime;
				FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
				CString strdate;
				strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
				CString strtime;
				strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

				ntype = 0;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					ntype = 1; //文件夹

                if(ntype == 0)
				{
					strcpy(sz,"<tr><td>");
					if(!check)
					{
						strcat(sz,"<a href=\"");
						if(m_type == 1)
						{
							strcat(sz,FindFileData.cFileName);
						}
						else
						{
							strcpy(pIn,FindFileData.cFileName);
							GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
							urlEncode(pIn1);
							strcat(sz,pIn1);
						}
						strcat(sz,"\">");
					}
					strcat(sz,FindFileData.cFileName);
					strcat(sz,"</a></td><td>");
					strcat(sz,strsize.GetBuffer(1));
					strcat(sz,"KB</td><td>");
  				    strcat(sz,strdate.GetBuffer(1));
					strcat(sz,"</td><td>");
					strcat(sz,strtime.GetBuffer(1));
					strcat(sz,"</td></tr>\r\n");
					_write(fh, sz, lstrlen(sz));
				}

			}
		}while(FindNextFile(hFind,&FindFileData));
		strcpy(sz,"</table>\r\n<p>&nbsp;&nbsp;请设使用IE浏览器<p>\r\n</html>");
		_write(fh, sz, lstrlen(sz));
        _close(fh);
		
		FindClose(hFind);
        return 1;
	}

}

int Create_DEEP_HTML(char dir[],char name[],char select[],BOOL check,int m_type)
{
	if(strcmp(select,"*.*"))
	{
		return Create_DEEP_SELECT(dir,name,select,check,m_type);
	}
	else
	{
		return Create_DEEP_HTML_ALL(dir,name,check,m_type);
	}

}

int Create_HTML(char dir[],char name[],char select[],BOOL check,int m_type)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[20000];
	strcpy(szName,dir);
	strcat(szName,select);

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	} 
	else 
	{
        //创建dirs
		int ntype;
		char szName1[2000];
		strcpy(szName1,dir);
		strcat(szName1,name);

		int fh;
		char pIn[2000];
		char pIn1[2000];
		fh = _creat(szName1, _S_IWRITE);
		TCHAR sz[2000] = "<html>\r\n<table align=\"center\" width=\"100%%\" cellspacing=\"0\" border=\"1\">\r\n<tr bgcolor=\"#EEEEEE\"><td align=\"center\"><b>文件名/文件夹名</b></td><td align=\"center\"><b>文件说明</b></td><td align=\"center\"><b>修改日期</b></td><td align=\"center\"><b>修改时间</b></td></tr>\r\n";
		_write(fh, sz, lstrlen(sz));

		do
		{
			if(strcmp(FindFileData.cFileName,name) == 0)
				continue;
			if(strcmp(FindFileData.cFileName,".") ==0)
				continue;
			if(strcmp(FindFileData.cFileName,".")!=0 && strcmp(FindFileData.cFileName,"..")!=0)
			{
				CString strsize;
				double fsize = ((double)((FindFileData.nFileSizeHigh * (MAXDWORD+1)) + FindFileData.nFileSizeLow))/1024;
				strsize.Format("%.1f",fsize);
				SYSTEMTIME stUTC, lpSystemTime;
				FileTimeToSystemTime(&(FindFileData.ftLastWriteTime),&stUTC);
				SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &lpSystemTime);
				CString strdate;
				strdate.Format("%d-%d-%d",lpSystemTime.wYear,lpSystemTime.wMonth,lpSystemTime.wDay);
				CString strtime;
				strtime.Format("%d:%d:%d",lpSystemTime.wHour,lpSystemTime.wMinute,lpSystemTime.wSecond);

				ntype = 0;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
					ntype = 1; //文件夹


				if(check)
				{
					strcpy(sz,"<tr><td>");
					if(ntype == 1)
					{
						strcat(sz,"<a href=\"");
                        if(m_type == 1)
						{
							strcat(sz,FindFileData.cFileName);
						}
						else
						{
							strcpy(pIn,FindFileData.cFileName);
							GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
							urlEncode(pIn1);
							strcat(sz,pIn1);
						}
						strcat(sz,"\">");
					}
				}
				else
				{
					strcpy(sz,"<tr><td><a href=\"");
					if(m_type == 1)
					{
						strcat(sz,FindFileData.cFileName);
					}
					else
					{
						strcpy(pIn,FindFileData.cFileName);
						GB2312ToUTF_8(pIn1,pIn,strlen(pIn));
						urlEncode(pIn1);
						strcat(sz,pIn1);
					}
					strcat(sz,"\">");
				}
				strcat(sz,FindFileData.cFileName);
				strcat(sz,"</a></td><td>");
				if(ntype == 0)
				{
					strcat(sz,strsize.GetBuffer(1));
					strcat(sz,"KB</td><td>");
				}
				else
				{
					if(strcmp(FindFileData.cFileName,"..") ==0)
					{
						strcat(sz,"返回上一级目录");
					}
					else
					{
						strcat(sz,"文件夹");
					}
					strcat(sz,"</td><td>");
				}
				strcat(sz,strdate.GetBuffer(1));
				strcat(sz,"</td><td>");
				strcat(sz,strtime.GetBuffer(1));
				strcat(sz,"</td></tr>\r\n");
				_write(fh, sz, lstrlen(sz));

			}
		}while(FindNextFile(hFind,&FindFileData));
		strcpy(sz,"</table>\r\n<p>&nbsp;&nbsp;请设使用IE浏览器<p>\r\n</html>");
		_write(fh, sz, lstrlen(sz));
        _close(fh);

		FindClose(hFind);
		return 1;
	}

}

int CreateHTML( char dir[],char name[],int deep,BOOL check,char select[],int m_type)
{
	if(deep == 0)
		return Create_HTML(dir,name,select,check,m_type);
	else
		return Create_DEEP_HTML(dir,name,select,check,m_type);
}




int Delete_HTML(char dir[],char name[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[20000];
	strcpy(szName,dir);
	strcat(szName,name);

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	} 
	else 
	{

		if(!DeleteFile(szName))
		{
			FindClose(hFind);
			return 0;
		}
		FindClose(hFind);
		return 1;
	}
}


int Delete_DEEP_HTML(char dir[],char name[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char szName[20000];
	char szName1[20000];
	strcpy(szName,dir);
	strcat(szName,"*.*");

	hFind = FindFirstFile(szName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return 0;
	} 
	else 
	{
		int ntype;
		do
		{
			if(strcmp(FindFileData.cFileName,".")==0 || strcmp(FindFileData.cFileName,"..") == 0)
				continue;
			ntype = 0;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				ntype = 1; //文件夹
            if(ntype == 0)
			{
				if(strcmp(FindFileData.cFileName,name) == 0)
				{
					strcpy(szName1,dir);
					strcat(szName1,name);
					if(!DeleteFile(szName1))
					{
						FindClose(hFind);
						return 0;
					}
				}
			}
			else
			{
				strcpy(szName1,dir);
				strcat(szName1,FindFileData.cFileName);
				strcat(szName1,"\\");
				if(!Delete_DEEP_HTML(szName1,name))
				{
					FindClose(hFind);
					return 0;
				}
			}
		}
		while(FindNextFile(hFind,&FindFileData));

		FindClose(hFind);
		return 1;
	}
}


int DeleteHTML(char dir[],char name[],int deep)
{
	if(deep == 0)
		return Delete_HTML(dir,name);
	else
		return Delete_DEEP_HTML(dir,name);
}








class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPer_Dir2HtmlDlg dialog

CPer_Dir2HtmlDlg::CPer_Dir2HtmlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPer_Dir2HtmlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPer_Dir2HtmlDlg)
	m_path = _T("C:\\Documents and Settings\\Administrator\\桌面");
	m_selectname = _T("*.*");
	m_deep = 0;
	m_check = FALSE;
	m_name = _T("dirs");
	m_type = 0;
	m_deldeep = 0;
	m_delname = _T("dirs");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPer_Dir2HtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPer_Dir2HtmlDlg)
	DDX_Text(pDX, IDC_PATH, m_path);
	DDV_MaxChars(pDX, m_path, 2000);
	DDX_Text(pDX, IDC_SELECTNAME, m_selectname);
	DDV_MaxChars(pDX, m_selectname, 2000);
	DDX_Radio(pDX, IDC_DEEP0, m_deep);
	DDX_Check(pDX, IDC_CHECK, m_check);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDV_MaxChars(pDX, m_name, 100);
	DDX_Radio(pDX, IDC_TYPE0, m_type);
	DDX_Radio(pDX, IDC_RADIO1, m_deldeep);
	DDX_Text(pDX, IDC_EDIT2, m_delname);
	DDV_MaxChars(pDX, m_delname, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPer_Dir2HtmlDlg, CDialog)
	//{{AFX_MSG_MAP(CPer_Dir2HtmlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	ON_BN_CLICKED(IDC_SEE, OnSee)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPer_Dir2HtmlDlg message handlers

BOOL CPer_Dir2HtmlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPer_Dir2HtmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPer_Dir2HtmlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPer_Dir2HtmlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPer_Dir2HtmlDlg::OnCreate() 
{
	// TODO: Add your control notification handler code here
		
	UpdateData();
	CWnd* pWnd = GetDlgItem(IDC_SELECTNAME);
	pWnd->GetWindowText(m_selectname);
	pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->GetWindowText(m_name);

    m_name += ".html";
	m_path += "\\";
	if(CreateHTML(m_path.GetBuffer(1),m_name.GetBuffer(1),m_deep,m_check,m_selectname.GetBuffer(1),m_type))
		AfxMessageBox("创建完成!!");
	else
		AfxMessageBox("创建失败!!");
}

void CPer_Dir2HtmlDlg::OnSee() 
{
	// TODO: Add your control notification handler code here

	char m_directory[65535];
	LPMALLOC pMalloc;  
	BROWSEINFO bi;  
	LPITEMIDLIST pidl;    
	::ZeroMemory(m_directory,sizeof(m_directory));  
	::ZeroMemory(&bi,sizeof(bi));  
	if   (::SHGetMalloc(&pMalloc)   ==   NOERROR)  
	{   
		bi.hwndOwner=NULL;  
		bi.pidlRoot=NULL;   //为NULL,则已桌面为根  
		bi.lpszTitle=_T("请选择文件夹");  
		bi.ulFlags=BIF_RETURNONLYFSDIRS;  
		bi.lpfn=NULL;  
		bi.lParam=NULL;  
		bi.pszDisplayName = m_directory;      
		if((pidl  =  ::SHBrowseForFolder(&bi)) != NULL)  
		{  
			if(!::SHGetPathFromIDList(pidl,m_directory))    
				pMalloc->Free(pidl);  
			m_path = m_directory;  
			CWnd* pWnd = GetDlgItem(IDC_PATH);
			pWnd->SetWindowText(m_path);  
		}    
		pMalloc->Release();  
	 }	
}

void CPer_Dir2HtmlDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlg;
	if(dlg.DoModal() == IDOK)
		;
}

void CPer_Dir2HtmlDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CSure dlg;
	if(dlg.DoModal() == IDOK)
	{
		UpdateData();
		CWnd* pWnd = GetDlgItem(IDC_EDIT2);
		pWnd->GetWindowText(m_delname);

		m_delname += ".html";
		m_path += "\\";
		if(DeleteHTML(m_path.GetBuffer(1),m_delname.GetBuffer(1),m_deldeep))
			AfxMessageBox("删除完成!!");
		else
			AfxMessageBox("未找到同名文件!!");
	}
	
}
