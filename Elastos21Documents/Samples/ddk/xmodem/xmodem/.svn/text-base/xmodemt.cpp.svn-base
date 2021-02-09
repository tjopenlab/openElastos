/*
 * Copyright (c) 1995 by Edward A. Falk
 */

/**********
 *	XMODEMT - transmit side of xmodem protocol
 *
 *  Caller sets flags defined in xmodem.h as appropriate.
 *  (default is basic xmodem)
 *
 *  This code is designed to be called from inside a larger
 *  program, so it is implemented as a state machine where
 *  practical.
 **********/
#include <stdio.h>
#include <stdlib.h>
#include "xmodem.h"


int CXmodem::XmodemTInit( char *file, UINT Protocol, BOOL Is1k)
{
	if (file == NULL) {
	    return XmErrInt;
	}

    m_Protocol = Protocol;
	if ( (m_Protocol == YMDM) || (m_Protocol == YMDMG) )
	    m_IsYmodem = TRUE;
    else
        m_IsYmodem = FALSE;

	m_State = m_IsYmodem ? X_FILE : X_START;

	strcpy(m_XmFilename, file);
    DBGOUT(printf("XmodemTInit open %s", m_XmFilename));
	if( (m_file = m_pCrf(m_XmFilename, "rb")) == NULL ) {
	    DBGOUT(printf("failed\n"));
	    sendCancel();
	    return XmErrCantOpen;
	}
    DBGOUT(printf("sucess\n"));
	m_PacketId = 1 ;
	m_PacketCount = 0 ;
	m_IsXmodem1k = Is1k;
	m_PktMaxLen = m_IsXmodem1k ? 1024 : 128;

	switch(m_Protocol) {
	    case XMDM :
	        m_XmTimeout = INITTO;
	        break;

	    case XMDMCRC :
            m_XmTimeout = INITTO2;
	        break;

	    case WXMDM :
            m_XmTimeout = INITTO2;
	        break;

	    case YMDM :
	        m_XmTimeout = INITTO;
	        break;

        case YMDMG :
	        m_XmTimeout = INITTO;
	        break;

	    default:
	        m_XmTimeout = INITTO;
	}


	return 0 ;
}


int CXmodem::XmodemTRcv(char c)
{
    int retval;
	if( c == CAN ) {
	    DBGOUT(printf("receive send cancel!\n"));
	    if( m_file != NULL )
	        m_pClsf(m_file);
	    return XmErrCancel;
	}

	switch( m_State ) {
	    case X_FILE:		/* waiting for command, ymodem */
	        switch( c ) {
	            case NAK:
	                m_IsUseCrc = FALSE;
	                return sendFilename();
	            case 'C':
	                m_IsUseCrc = TRUE;
	                return sendFilename();
	            case 'G':
	                m_IsUseCrc = TRUE;
	                return sendFilename();
	        }
	        break;

	    case X_FILEWAIT:	/* waiting for filename ACK */
	        DBGOUT(printf("waiting for filename ACK\n"));
	        switch( c ) {
	            case NAK:
	                return resendPacket();
	            case ACK:
	                m_State = X_START;
	                return 0;
	        }

	    case X_START:		/* waiting for command, data */
	        switch( c ) {
	            case NAK:		/* wants checksums */
		            if( !m_IsYmodem )
		                m_Protocol = XMDM;
		            m_IsUseCrc = FALSE;
		            return sendPacket();

	            case 'C':
	                m_IsUseCrc = TRUE ;
	                return sendPacket();

	            case 'G':
	                m_IsUseCrc = TRUE ;
	                while((retval = sendPacket()) == 0 ) {
	                    if (m_State == X_EOT)
	                        return retval;
	                }
	                return retval;

	            case 'W':
		            if( !m_IsYmodem ) {
		                m_Protocol = WXMDM;
		                m_IsUseCrc = TRUE;
		            /* TODO: WXmodem */
		            }
		            return sendPacket();//myself add,just a dummy
	        }
	        break;


	    case X_WAIT:		/* waiting for ACK */
	        DBGOUT(printf("waiting for ACK\n"));
	        switch( c ) {
	            case ACK:
	                return sendPacket();
	            case NAK:
	                return resendPacket();
	        }
	        break;		/* ignore all other characters */

	    case X_EOT:		/* waiting for ACK after EOT */
	        switch( c ) {
	            case ACK:
	                return XmDone ;
	            case NAK:
	                return sendChr(EOT);
	        }
	        break;

	    case X_ENDWAIT:		/* waiting for filename ACK */
	        DBGOUT(printf("waiting for filename ACK\n"));
	        switch( c ) {
	            case NAK:
	                return resendPacket();
	            case ACK:
	                return XmDone;
	        }
	}
	return 0 ;
}

int CXmodem::sendFilename()
{
	int	 i;
	char *ptr;

	m_PktLen = 128 ;
	/* TODO: protect against long filenames */
	strcpy(m_Packet, m_XmFilename) ;
	ptr = m_Packet + strlen(m_Packet) + 1 ;
	/* TODO: get file info */
	_itoa(m_fileLen, ptr, 10);
	DBGOUT(printf("m_fileLen : %s %d\n", ptr, m_fileLen));
	ptr += strlen(ptr) + 1;
	/* TODO: what if file desc buffer too big? */
    //just now the buffer is enough :-) (my comment)
	if( ptr > m_Packet + 128 )
	    m_PktLen = 1024;
	i = m_PktLen - (ptr - m_Packet);
	memset(ptr, 0, i);
	if (m_Protocol != YMDMG)
	    m_State = X_FILEWAIT;
	else
	    m_State = X_START;
	m_PacketId = 0;

	return buildPacket();
}


int CXmodem::XmodemTFinish()
{
	m_PktLen = 128;
	memset(m_Packet, 0, m_PktLen);
	m_State = X_ENDWAIT;
	m_PacketId = 0;

	return buildPacket();
}



int CXmodem::sendPacket()
{
	int	i ;
	/* This code assumes that a incomplete reads can only happen
	 * after EOF.  This will fail with pipes.
	 * TODO: try to make pipes work.
	 */
	if (m_Protocol != YMDMG)
	    m_State = X_WAIT;

	if( m_buflen > 0 ) {		/* previous incomplete packet */
	    memcpy(m_Packet, m_bufptr, 128);
	    m_bufptr += 128 ;
	    if( m_buflen < 128 )
	        for(i = m_buflen; i < 128; ++i)
	            m_Packet[i] = 0x1A;
	    m_buflen -= 128;
	    m_PktLen = 128;
	    return buildPacket();
	}

	if( (i = m_pRdf(m_Packet, 1, m_PktMaxLen, m_file)) <= 0 ) {	/* EOF */
	    DBGOUT(printf("file read fin\n"));
	    m_State = X_EOT;
	    return sendChr(EOT);
	}
	else if( i == m_PktMaxLen ) {		/* full buffer */
	    m_PktLen = i;
	    return buildPacket();
	}

	m_buflen = i;
	m_bufptr = m_Packet;
	m_PktLen = 128 ;
	return buildPacket();
}

int CXmodem::buildPacket()
{
	int	i;
    DBGOUT(printf("buildPacket\n"));
	m_PktHdr[0] = m_PktLen == 128 ? SOH : STX;
	m_PktHdr[1] = (char)m_PacketId;
	m_PktHdr[2] = (char)(255 - m_PacketId);
	++m_PacketId;

	if( m_IsUseCrc ) {
	    DBGOUT(printf("m_IsUseCrc .....\n"));
	    i = calcrc(m_Packet, m_PktLen);
	    m_PktCrc[0] = (char)(i >> 8);
	    DBGOUT(printf("Crc 0 %02x\n", m_PktCrc[0]));
	    m_PktCrc[1] = (char)(i & 0xff);
	    DBGOUT(printf("Crc 1 %02x\n", m_PktCrc[1]));
	}
	else
	    m_PktCrc[0] = (char)calcChecksum(m_Packet, m_PktLen);

	return resendPacket();
}


int CXmodem::resendPacket()
{
    int i;
	DBGOUT(printf("resendPacket m_PktLen %d\n", m_PktLen));
	i = sendStr(m_PktHdr, 3);
	i |= sendStr(m_Packet, m_PktLen);
	if (m_IsUseCrc) {
	    i |= sendStr(m_PktCrc, 2);
	} else {
	    i |= sendStr(m_PktCrc, 1);
    }
	return i;
}


int CXmodem::XmodemTTimeout()
{
	switch( m_State ) {
	    case X_FILE:
	    case X_START:
	        return XmErrInitTo ;
	    case X_FILEWAIT:
	    case X_WAIT:
	    case X_EOT:
	        return XmErrRcvTo ;
	}
	return 0;
}

int CXmodem::XmodemTAbort()
{
    return sendCancel();
}

void CXmodem::SetHandle(void *pCr, void *pWr, void *pRd, void *pCls, int len)
{
    m_pCrf  = (CreateFunc)pCr;
    m_pWrtf = (WriteFunc)pWr;
    m_pRdf  = (ReadFunc)pRd;
    m_pClsf = (CloseFunc)pCls;
    m_fileLen = len;
}
