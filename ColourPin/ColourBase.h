#pragma once
//#include <vector>

class CColourBase
{
public:
	CColourBase(void);
	~CColourBase(void);
public:
	CString RGBto16(DWORD rgb[3]);
public:
	void RGBTurnToList(DWORD rgb[3]);

public:
	DWORD RGBList[9][3];
};

