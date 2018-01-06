#pragma once


#pragma once


class CTimeStamp
{
public:
	 CTimeStamp(void);
	 ~CTimeStamp(void);
public:
	DWORD GetNowTimeStamp();
	DWORD ConvertTime2TimeStamp(CString strTime);
	CString ConvertTimeStamp2Time(DWORD dwTimeStamp);

};
	