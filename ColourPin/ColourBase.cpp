#include "StdAfx.h"
#include "ColourBase.h"


CColourBase::CColourBase(void)
{
	memset(RGBList,0,sizeof(RGBList));
}


CColourBase::~CColourBase(void)
{
	
}


CString CColourBase::RGBto16(DWORD rgb[3])
{
	TCHAR szR[3]={0},szG[3]={0},szB[3]={0};
	_itot(rgb[0],szR,16);
	_itot(rgb[1],szG,16);
	_itot(rgb[2],szB,16);
	CString strHEX;
	strHEX.Format(_T("0x%s%s%s"),szR,szG,szB);
	return strHEX;
}

void CColourBase::RGBTurnToList(DWORD rgb[3])
{
	memset(RGBList,0,sizeof(RGBList));
	for (int i = 0;i <4;i++)
	{
		int R = rgb[0] - 5*(4-i);
		int G = rgb[1];// - 5*(4-i);
		int B = rgb[2] - 5*(4-i);
		if (R < 0 ||  B <0)
		{
			if (i == 0)
			{
				RGBList[i][0] =rgb[0];
				RGBList[i][1] = rgb[1];
				RGBList[i][2] = rgb[2];
			}
			else
			{
				RGBList[i][0] = RGBList[i-1][0];
				RGBList[i][1] = RGBList[i-1][1];
				RGBList[i][2] = RGBList[i-1][2];
			}
		}
		else
		{
			RGBList[i][0] = R;
			RGBList[i][1] = G;
			RGBList[i][2] = B;
		}
	}
	for (int i = 5;i <9;i++)
	{
		int R = rgb[0] + 5*(i-4);
		int G = rgb[1];// + 5*(i-4);
		int B = rgb[2] + 5*(i-4);
		if (R > 255 || B >255)
		{
			if (i ==5)
			{
				RGBList[i][0] =rgb[0];
				RGBList[i][1] = rgb[1];
				RGBList[i][2] = rgb[2];
			}
			else{
				RGBList[i][0] = RGBList[i-1][0];
				RGBList[i][1] = RGBList[i-1][1];
				RGBList[i][2] = RGBList[i-1][2];
			}
		}
		else
		{		
			RGBList[i][0] = R;
			RGBList[i][1] = G;
			RGBList[i][2] = B;
		}

	}
	RGBList[4][0]= rgb[0];
	RGBList[4][1]= rgb[1];
	RGBList[4][2]= rgb[2];
}