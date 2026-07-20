/*
	$Header: /7HeartsOnline/Client/Util/CSocket.h 2     04-05-27 8:32p Icarus $
*/
#ifndef	__CSOCKET_H
#define	__CSOCKET_H

#include <winSock.h>

class CSOCKET
{
public:
	static bool Init ();
	static void Free ();
};

int Socket_Error (char *szMsg, int iErr = WSAGetLastError());
#endif
