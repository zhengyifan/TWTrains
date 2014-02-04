/* /////////////////////////////////////////////////////////////////////////
* File:        TrainTest.h
* Purpose:     Test the TrainClass
* Created:     May 28,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */
#ifndef _TRAINTEST_H
#define _TRAINTEST_H

#include "TrainDataDef.h"
#include <iostream>
#include <string>

class CTrainTest
{
public:
	CTrainTest(void);
	~CTrainTest(void);
public:
	void TestCreateMGraph( MGraph *& pMGraph );
	void TestShortRouteFunction(  TCHAR szSrc,TCHAR szDes ,MGraph * pMGraph ,wstring &strTrip,int &nShortPath );
	void TestRoutePath( TCHAR  szTrack[] ,int nStopNum,int &nLength,MGraph * pMGraph );
	void TestRouteNumUnderMaxStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nMaxStops);
	void TestRouteNumWithExactStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nExactStops);
	void TestSearchAllPath( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nMaxRight);
};
#endif