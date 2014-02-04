// TWTrains.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "TrainDataDef.h"
#include "MainGraph.h"
#include "TrainTest.h"
#include "Train.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CTrainTest Test;

	//测试创建MGraph
	TCHAR arrVex[] = { _T('A'),_T('B'),_T('C'),_T('D'),_T('E')};
	int nVexNum  = 5;

	int nVexAdjNum = 9;
	VertexAdj arrVexAdj[9];

	arrVexAdj[0].szSrc = _T('A');
	arrVexAdj[0].szDes = _T('B');
	arrVexAdj[0].adj   = 5;

	arrVexAdj[1].szSrc = _T('A');
	arrVexAdj[1].szDes = _T('E');
	arrVexAdj[1].adj   = 7;

	arrVexAdj[2].szSrc = _T('A');
	arrVexAdj[2].szDes = _T('D');
	arrVexAdj[2].adj   = 5;

	arrVexAdj[3].szSrc = _T('B');
	arrVexAdj[3].szDes = _T('C');
	arrVexAdj[3].adj   = 4;

	arrVexAdj[4].szSrc = _T('C');
	arrVexAdj[4].szDes = _T('D');
	arrVexAdj[4].adj   = 8;

	arrVexAdj[5].szSrc = _T('C');
	arrVexAdj[5].szDes = _T('E');
	arrVexAdj[5].adj   = 2;

	arrVexAdj[6].szSrc = _T('D');
	arrVexAdj[6].szDes = _T('E');
	arrVexAdj[6].adj   = 6;

	arrVexAdj[7].szSrc = _T('D');
	arrVexAdj[7].szDes = _T('C');
	arrVexAdj[7].adj   = 8;

	arrVexAdj[8].szSrc = _T('E');
	arrVexAdj[8].szDes = _T('B');
	arrVexAdj[8].adj   = 3;
	MGraph * pMGraph = new MGraph(arrVex,nVexNum,arrVexAdj,nVexAdjNum);
	wcout<<_T("------------------------------------Graph---------------------------------------");
	Test.TestCreateMGraph(pMGraph);
	wcout<<endl;
	wcout<<endl;
	CMainGraph *pMainGraph = new CMainGraph(arrVex,nVexNum,arrVexAdj,nVexAdjNum);
	wcout<<_T("------------------------------------Graph---------------------------------------");
	Test.TestCreateMGraph(pMGraph);
	wcout<<endl;
	wcout<<endl;

	//---------------------------------测试指定路径--------------------------------------------
	TCHAR  szTrack[] = {_T('A'),_T('A'),_T('C'),_T('\0')};
	int nStopNum     = 3;
	int nLength;
	wcout<<_T("---------------------------------Certain route----------------------------------");
	Test.TestRoutePath(szTrack,nStopNum,nLength,pMGraph);
	wcout<<endl;
	wcout<<endl;
	//-----------------------------------------------------------------------------------------

	//-----------------------------------测试最短路径------------------------------------------
	wcout<<_T("---------------------------------Shortest route---------------------------------");
	wstring strTrip;
	int nShortPath;
	TCHAR szSrc = _T('A');
	TCHAR szDes = _T('C');
	for ( int n = 0; n < nVexNum;n++)
	{
		szSrc = arrVex[n];
		for (int m = 0;m< nVexNum;m++)
		{
		nShortPath = INF;
		szDes = arrVex[m];
		Test.TestShortRouteFunction(szSrc,szDes,pMGraph,strTrip,nShortPath);
		}
	}
	wcout<<endl;
	wcout<<endl;
	//----------------------------------------------------------------------------------------

	//-----------------------------测试两点间经过指定站数量的路径数量-------------------------
	wcout<<_T("-----------------------The number of trips with exactly stops-------------------");
	szSrc = _T('C');
	szDes = _T('C');
	int nExactStops = 1;
	Test.TestRouteNumWithExactStops(szSrc,szDes,pMGraph,nExactStops);

	szSrc = _T('C');
	szDes = _T('C');
	nExactStops = 2;
	Test.TestRouteNumWithExactStops(szSrc,szDes,pMGraph,nExactStops);

	szSrc = _T('C');
	szDes = _T('C');
	nExactStops = 3;
	Test.TestRouteNumWithExactStops(szSrc,szDes,pMGraph,nExactStops);
	wcout<<endl;
	wcout<<endl;
	//-----------------------------------------------------------------------------------------




	//-----------------------------测试两点间的路径数量，指定经过站数量的最大值----------------
	wcout<<_T("----------------------The number of trips with maximum stops--------------------");
	szSrc = _T('C');
	szDes = _T('C');
	int nMaxStops = 3;
	Test.TestRouteNumUnderMaxStops(szSrc,szDes,pMGraph,nMaxStops);
	wcout<<endl;
	wcout<<endl;
	//-----------------------------------------------------------------------------------------


	wcout<<_T("----------------------The number of different routes----------------------------");
	szSrc = _T('C');
	szDes = _T('C');
	int nMaxRight = 30;
	Test.TestSearchAllPath(szSrc,szDes,pMGraph,nMaxRight);

	for ( int n = 0; n < nVexNum;n++)
	{
		szSrc = arrVex[n];
		for (int m = 0;m< nVexNum;m++)
		{
			szDes = arrVex[m];
			Test.TestSearchAllPath(szSrc,szDes,pMGraph,nMaxRight);
		}
	}
	wcout<<endl;
	wcout<<endl;
	delete pMGraph;
	return 0;
}

