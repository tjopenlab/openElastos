/*
 * Copyright (c) 1995 by Edward A. Falk
 */

/**********
 *	XMODEMR - receiver side of xmodem/ymodem protocol
 *
 *	Caller sets flags defined in xmodem.h as appropriate.
 *	(default is basic xmodem)
 *
 *	This code is designed to be called from inside a larger
 *	program, so it is implemented as a state machine where
 *	practical.
 **********/

#include "xmodem.h"

CXmodem::CXmodem()
{
	m_State = X_START;
	m_ErrorCount = 0;
	m_IgnoreCount = 0;
	m_XmTimeout = 0;
	m_IComDev = NULL;
	m_IsUseCrc = TRUE;
	m_pWrtf = NULL;
	m_pCrf = NULL;
	m_pRdf = NULL;
	m_pClsf = NULL;
	m_buflen = 0;
	m_file = 0;
}

CXmodem::~CXmodem()
{
	m_ErrorCount = 0;
	m_IgnoreCount = 0;
	m_XmTimeout = 0;
	m_IComDev = NULL;
}

ECode CXmodem::XmDeviceOpen(WString DeviceDesc)
{
    ECode ec;
    ec = CSystem::FindRunningObject( DeviceDesc, (IInterface **)&m_IComDev);
    if (FAILED(ec)) {
        DBGOUT(printf("ERROR: Can't find Service: timer, ec = 0x%08x\n", ec));
        goto __Exit;
    }
__Exit:
    return ec;
}

void CXmodem::XmDeviceCls()
{
    if (m_IComDev) {
        m_IComDev->Release();
    }
}

ECode CXmodem::XmDeviceSet(int CMD)
{
    BufferOf_<Byte, 1> Tmp;
    ECode ec = NOERROR;
    if (m_IComDev) {
        ec = m_IComDev->Control(CMD, Tmp, Tmp, NULL);
    }
    else {
        ec = E_DOES_NOT_EXIST;
    }
    return ec;
}

int CXmodem::XmodemRInit(char *path, UINT Protocol )
{
	int	err;
	if (path == NULL) {
	    return XmErrInt;
	}
	m_State = X_START;
    m_Protocol = Protocol;
	if ( (m_Protocol == YMDM) || (m_Protocol == YMDMG) )
	    m_IsYmodem = TRUE;
    else
        m_IsYmodem = FALSE;

	if ( m_IsYmodem )
	    strcpy(m_XmDefPath, path);
	else
	    strcpy(m_XmFilename, path);

	m_EotCount = m_ErrorCount = m_ErrorCount2 = 0;
    err = XmodemRStart();
	if( err )
	  return err;
    DBGOUT(printf("XmodemRStart Success!\n"));

	m_State = X_INIT;
	m_PacketId = m_IsYmodem ? 255 : 0;
	m_PktHdrLen = (m_Protocol == XMDM) ? 3 : 4;
	m_PacketCount = 0;

	return 0 ;
}


/* send startup character */
int CXmodem::XmodemRStart()
{
	int	err;
	char c;
	switch(m_Protocol) {
	    case XMDM :
	        c = NAK;
	        m_IsUseCrc = FALSE;
	        m_XmTimeout = INITTO;
	        break;

	    case XMDMCRC :
	        c = 'C';
            m_XmTimeout = INITTO2;
	        break;

	    case WXMDM :
	        c = 'W';
            m_XmTimeout = INITTO2;
	        break;

	    case YMDM :
	        c = 'C';
	        m_XmTimeout = INITTO;
	        break;

        case YMDMG :
	        c = 'G';
	        m_XmTimeout = INITTO;
	        break;

	    default:
	        m_Protocol = XMDM;
	        c = NAK;
	        m_XmTimeout = INITTO;
	}
	err = sendFlush(c);
	if( err )
	  return err;
	return 0;
}

#include <stdio.h>
int CXmodem::XmodemRRcv(char c)
{
    int RetVal = 0;
	m_ErrorCount = 0;
	switch( m_State ) {
	    case X_START :		/* shouldn't happen, ignore */
	        if( c == CAN )
	            return XmErrCancel;
	        break;

	    case X_INIT :		/* waiting */
	    case X_WAIT :
	        switch( c ) {
    	        case SOH :
    	        case STX :
            		m_PktLen = (c == STX) ? 1024 : 128 ;
            		m_InCount = 0;
            		m_optr = m_Packet;
            		m_State = X_PACKET;
            		m_XmTimeout = PKTTO;
            		break;

	            case EOT :
            		if( ++m_EotCount > 1 ) {
            		    sendFlush(ACK);
            		    if( m_IsYmodem ) {
            		        RetVal = XmodemRInit(m_XmDefPath, m_Protocol);
            		        DBGOUT(printf("restart protocol"));
            		        return  RetVal;/* restart protocol */
            		    }
            		    else
            		        return XmDone;
            		} else {
            		    RetVal = rejectPacket();	/* make xmitter try again */
            		    return RetVal;
                    }
                    break;

            	case CAN :
            	    return XmErrCancel;

	            default :		/* ignore all others */
		            if( ++m_IgnoreCount > 1030 ) {
		                m_IgnoreCount = 0;
		                RetVal = sendFlush(NAK);
		                return RetVal;
		            }
		            break ;
	        }/*end switch(c)*/
	        break ;/*break X_WAIT*/

    	case X_PACKET :		/* mid packet */
    	    *m_optr++ = c ;
    	    if( ++m_InCount >= m_PktLen + m_PktHdrLen )
    	        RetVal = ProcessPacket();
    	    break;
    }/*end switch(m_State)*/
	return RetVal ;
}


int CXmodem::XmodemRTimeout()
{
    int RetVal;
	if( ++m_ErrorCount > MAXERROR ) {
	    RetVal = (m_State == X_INIT) ? XmErrInitTo : XmErrRcvTo;
	    return RetVal;
    }
	switch( m_State ) {
	    case X_START :
	        return -1;		/* shouldn't happen */
	    case X_INIT :
	        if( ++m_ErrorCount2 >= 3 )
	            switch( m_Protocol ) {
		            case WXMDM :
		                m_Protocol = XMDMCRC;
		                m_ErrorCount2 = 0;
		                break;
		            case XMDMCRC :
		                m_Protocol = XMDM;
		                m_PktHdrLen = 3 ;
		                break ;
	            }
	      RetVal = XmodemRStart();
	      return RetVal;

	    case X_WAIT :			/* timeout while waiting */
	    case X_PACKET :			/* timeout in mid packet */
	        if (m_Protocol != YMDMG)
	            RetVal = rejectPacket();
	        else
	            RetVal = sendFlush('G');
	      return RetVal;
	    default:
	        return XmErrInt;
	}
}

int CXmodem::XmodemRAbort()
{
    return sendCancel() ;
}


int CXmodem::ProcessPacket()
{
	int	id  = (UCHAR)m_Packet[0];
	int	idc = (UCHAR)m_Packet[1];
	int	i, csum = 0;
	char *p = NULL;
	if ( idc != (255 - id) )
	    return rejectPacket();

	if ( id == m_PacketId )		/* duplicate */
	    return acceptPacket();

	if( id != ((m_PacketId + 1) % 256) ) {	/* out of sequence */
	    sendCancel();
	    return XmErrSequence;
	}


	if (m_IsUseCrc) {
	    int crc0 = ((UCHAR)m_Packet[m_PktLen + 2] << 8) | ((UCHAR)m_Packet[m_PktLen + 3]);
	    int crc1 = calcrc(m_Packet + 2, m_PktLen);
	    if( crc0 != crc1 )
	        return rejectPacket();
	}
	else {
	    /* compute checksum */
	    csum = calcChecksum(m_Packet + 2, m_PktLen);
	    if( csum != (UCHAR)m_Packet[2 + m_PktLen] )
	        return rejectPacket();
	}
	/* it's a good packet */
	m_PacketId = (m_PacketId + 1) % 256;


	/* is this the first packet? */
	if( m_PacketCount == 0 ) {
	    if( m_IsYmodem ) {
	        DBGOUT(printf("Process Packet Ymodem\n"));
	        if( m_Packet[2] == '\0' )	{/* last file */
	            DBGOUT(printf("last file\n"));
	            acceptPacket();
	            return XmDone;
	        }

    	    if( m_Packet[2] == '/' )
    	        strcpy(m_XmFilename, m_Packet + 2);
    	    else {
    	        strcpy(m_XmFilename, m_XmDefPath);
    	        strcat(m_XmFilename, m_Packet + 2);
    	    }

    	    m_fileLen = 0 ;
            p = m_XmFilename;
            while(*p)
                p++;
            p = m_Packet + 2 + (p - m_XmFilename - 1);
    	    while(*p && *p >= '0' && *p <= '9') {
    	        m_fileLen *= 10;
    	        m_fileLen += (*p -'0');
    	        p++;
    	    }
	        DBGOUT(printf("%d\n", m_fileLen));
	    }
	    if( (m_file = m_pCrf(m_XmFilename, "wb")) == NULL ) {
	        DBGOUT(printf("create file failed!\n"));
	        sendCancel();
	        return XmErrCantOpen;
        }

	    if( m_IsYmodem ) {
	        m_PacketCount = 1;
	        acceptPacket();
	        if (m_Protocol != YMDMG)
	            return sendFlush('C');
	        else
	            return sendFlush('G');
	    }
	    else
	        m_State = X_PACKET;
	}

	++m_PacketCount;

	/* TODO: ymodem: if this is last packet, truncate it */
	if (m_IsYmodem) {
    	if (m_fileLen < m_PktLen) {
    	    DBGOUT(printf("truncate the padding NULL char\n"));
    	    m_PktLen = m_fileLen;
    	}
    	m_fileLen -= m_PktLen;
	}

	i = m_pWrtf(m_Packet + 2, 1, m_PktLen, m_file);
	if( i != m_PktLen ) {
	    DBGOUT(printf("write file failed!\n"));
	    sendCancel();
	    return XmErrSys;
	}
	else {
	    DBGOUT(printf("remain %d bytes to receive!\n", m_fileLen));
	    return acceptPacket() ;
    }
}


int CXmodem::rejectPacket()
{
	m_State = X_WAIT;
	m_XmTimeout = INITTO ;
	return sendFlush(NAK) ;
}

int CXmodem::acceptPacket()
{
    m_State = X_WAIT;
    m_XmTimeout = INITTO;
    if (m_Protocol != YMDMG)
        return sendFlush(ACK);
    return 0;
}
