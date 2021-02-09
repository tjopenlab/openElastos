#ifndef __XMODEM_H_
#define __XMODEM_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <elastos.h>

#if 0
#include <stdio.h>
#define DBGOUT(s)  s
#else
#define DBGOUT(s)
#endif//if 0

#define __MAX__PATH 260

//define protocol type
#define  XMDM     0 //xmodem
#define  XMDMCRC  1 //xmodem crc
#define  WXMDM    2 //wxmodem
#define  YMDM     3 //ymodem
#define  YMDMG    4 //ymodem G


/*define Xmodem state*/
#define  X_START    0   /* XMIT : waiting to begin */
                        /* RECV : waiting to begin */
#define  X_INIT	    1   /* RECV : sent initial NAK, 'C' or 'W' */
#define  X_WAIT	    2   /* XMIT : sent a packet, waiting for ACK */
                        /* RECV : wait for start of next packet */
#define  X_FILE	    3   /* XMIT : waiting for initial protocol character */
#define  X_FILEWAIT	4   /* XMIT : sent file header, waiting for ACK */
#define  X_PACKET	5   /* RECV : receiving a packet */
#define  X_EOT		6   /* XMIT : sent an EOT, waiting for ACK */
#define  X_ENDWAIT	7   /* XMIT : sent null filename, waiting for ACK */



/* error code definitions */
#define	XmDone		    -1	/* done */
#define	XmErrInt	    -2	/* internal error */
#define	XmErrSys	    -3	/* system error, see errno */
#define	XmErrNotOpen	-4	/* communication channel not open */
#define	XmErrCantOpen	-5	/* can't open file, see errno */
#define	XmErrInitTo	    -10	/* transmitter failed to respond to init req. */
#define	XmErrSequence	-11	/* packet received out of sequence */
#define	XmErrCancel	    -12	/* cancelled by remote end */
#define	XmErrRcvTo	    -13	/* remote end timed out during transfer */


/* INTERNAL */
#define	SOH	    1	/* ^A */
#define	STX	    2	/* ^B */
#define	EOT	    4	/* ^D */
#define	ACK	    6	/* ^F */
#define	DLE	    16	/* ^P */
#define	XON	    17	/* ^Q */
#define	XOFF    19	/* ^S */
#define	NAK	    21	/* ^U */
#define	SYN	    22	/* ^V */
#define	CAN	    24	/* ^X */


#define	MAXERROR	10
#define	INITTO		10	/* initialization timeout, basic xmodem */
                        /*Xmodem, Ymodem, YmodemG*/
#define	INITTO2		3	/* initialization timeout */
                        /*WXmodem, XmodemCRC*/
#define	PKTTO		5	/* in-packet receive timeout */

#define	MAXPACKET	1024	/* max packet length */

typedef ULONG(*CreateFunc)(char *file, char *argv);
typedef int(*WriteFunc)(const char * buffer, size_t size, size_t Cnt, ULONG f);
typedef int(*ReadFunc)(char * buffer, size_t size, size_t Cnt, ULONG f);
typedef int(*CloseFunc)(ULONG f);

class CXmodem {
    public:
        CXmodem();
        ~CXmodem();
        ECode XmDeviceOpen(WString);
        void    XmDeviceCls();
        ECode XmDeviceSet(int cmd);
	    int	XmodemRStart();
	    int	ProcessPacket();
	    int	rejectPacket();
	    int	acceptPacket();
        int	sendFilename();
        int	sendPacket();
        int	buildPacket();
        int	resendPacket();
        void SetHandle(void *pCr, void *pWr, void *pRd, void *pCls, int len);

        int	XmodemRInit(char *path, UINT Protocol); /* start receive protocol */
        int	XmodemRRcv(char c);	                    /* call for each received char. */
        int	XmodemRTimeout();	                    /* call if xmTimeout expires */
        int	XmodemRAbort();	                        /* call to abort protocol */

        int	XmodemTInit(char *path, UINT Protocol, BOOL Is1k); /* start transmit protocol */
        int	XmodemTRcv(char c);	                    /* call for each received char. */
        int	XmodemTTimeout();	                    /* call if xmTimeout expires */
        int	XmodemTAbort();	                        /* call to abort protocol */
        int	XmodemTFinish();	                    /* call after last file sent (ymodem) */

        int	sendCancel();
        int sendFlush(char);
        int sendChr(char);
        int sendStr(char *,int);
        int recvStr(char *, int);
        int	calcrc(char *ptr, int count);
        int	calcChecksum(char *ptr, int count);

    public:
        IDriver *m_IComDev;
        UINT     m_ICnt;

    public:
        BOOL	m_IsXmodem1k;	/* 1k blocks supported */
        BOOL	m_IsYmodem;
        BOOL    m_IsUseCrc;	/* receiver wants crc */

        UINT	m_State;
        UINT    m_Protocol;
        int	    m_XmTimeout;	/* timeout, seconds */

        int		m_ErrorCount, m_ErrorCount2, m_IgnoreCount;
        int		m_EotCount;	/* count EOT's, reject first one */
        int		m_InCount;	  /* characters received this packet */
        int		m_PktLen;	/* length of this packet data */
        int		m_PktHdrLen;	/* id, cmpl, checksum or crc */
        char	m_Packet[MAXPACKET + 5];//recv
        char   *m_optr;
        int		m_PacketId ;	/* id of last received packet */
        int		m_PacketCount ;	/* # packets received */
        int		m_PktMaxLen;
        char	m_PktHdr[3], m_PktCrc[2];
        int     m_buflen;
        char   *m_bufptr;
        WriteFunc  m_pWrtf;
        CreateFunc m_pCrf;
        ReadFunc   m_pRdf;
        CloseFunc  m_pClsf;
//        char	m_Packet[MAXPACKET];//xmit
        int	m_fileLen;//, m_fileDate, m_fileMode;
        char	m_XmDefPath[__MAX__PATH];		/* default location (ymodem) */
        char	m_XmFilename[__MAX__PATH];	/* current filename */
//        BOOL	m_IsfileInfo;	/* ymodem: send file attributes? */
//        FILE  *m_ifile;	/* input file fd */
        ULONG  m_file;	/* output file fd */

};

#endif//_XMODEM_H_


