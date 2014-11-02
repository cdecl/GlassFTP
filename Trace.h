
#ifndef __TRACE_H_BY_CDECL__
#define __TRACE_H_BY_CDECL__

#include <cstdio>
#include <windows.h>

namespace GLASS 
{

	// printf 포맷을 이용하는 OutputDebugString 함수
	inline void Trace(LPCTSTR szFormat, ...)
	{
		enum { BUFF_SIZE = 2048 };
		
		TCHAR szTempBuf[BUFF_SIZE] ;
		va_list vlMarker ;
		
		va_start(vlMarker,szFormat) ;
		_vstprintf(szTempBuf,szFormat,vlMarker) ;
		va_end(vlMarker) ;
		
		OutputDebugString(szTempBuf) ;
	}

}

#endif 