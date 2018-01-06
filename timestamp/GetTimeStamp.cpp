#include "stdafx.h"
#include "GetTimeStamp.h"
#include <time.h>


CTimeStamp::CTimeStamp(void)
{
	
}


CTimeStamp::~CTimeStamp(void)
{
}



DWORD CTimeStamp::GetNowTimeStamp()
{
// 	time_t curtime = time(NULL);
// 	tm *ptm = localtime(&curtime);
// 	char buf[64];
// 	sprintf(buf, "%d/%02d/%02d %02d:%02d:%02d", ptm->tm_year+1900, ptm->tm_mon+1,
// 		ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	WORD wYear = stTime.wYear;
	WORD wMonth = stTime.wMonth;
	WORD wDay = stTime.wDay;
	WORD wHour = stTime.wHour;
	WORD wMinute = stTime.wMinute;
	WORD wSecond = stTime.wSecond;
	CString m_date;
	//m_date   2017/9/29 11:12:59
	m_date.Format(__T("%4d/%2d/%2d %2d:%2d:%2d"), wYear, wMonth, wDay, wHour, wMinute, wSecond);
	return ConvertTime2TimeStamp(m_date);
}


DWORD CTimeStamp::ConvertTime2TimeStamp(CString strTime)
{
	struct tm stm;  

	int   dwYear=0,
					dwMonth=0,
					dwDay=0,
					dwHour=0,
					dwMinute=0,
					dwSecond =0;
	
	_stscanf(strTime,__T("%d/%d/%d %d:%d:%d"),&dwYear,&dwMonth,&dwDay,&dwHour,&dwMinute,&dwSecond);

	stm.tm_year=dwYear-1900;  
	stm.tm_mon=dwMonth-1;  
	stm.tm_mday=dwDay;  
	stm.tm_hour=dwHour;  
	stm.tm_min=dwMinute;  
	stm.tm_sec=dwSecond;  

	/*printf("%d-%0d-%0d %0d:%0d:%0d\n", iY, iM, iD, iH, iMin, iS);*/   //标准时间格式例如：2016:08:02 12:12:30
	return (DWORD)mktime(&stm);  
}

CString CTimeStamp::ConvertTimeStamp2Time(DWORD dwTimeStamp)
{
	time_t tick = (time_t)dwTimeStamp;
	struct tm tm; 
	char s[100] = {0};

	//tick = time(NULL);
	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y/%m/%d %H:%M:%S", &tm);
	return CString(s);
}