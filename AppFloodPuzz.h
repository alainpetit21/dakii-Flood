#ifndef _TEST_APP_H
#define _TEST_APP_H

#include "dfcApp.h"


#define CTX_TITLE	0
#define CTX_GAME	1
#define CTX_SCORE	2
#define MAX_CTX		3

class CAppFloodPuzz : public CApp
{
public:
	CAppFloodPuzz();
	virtual ~CAppFloodPuzz(){};

	virtual void OnPostCreate(void);

	int m_curLevel;

	//Scoring Purpose
	int			m_nbUseBucket[16];
	int			m_nbSeconds;
};

extern CAppFloodPuzz *g_TheAppFloodPuzz;

#endif //_TEST_APP_H
