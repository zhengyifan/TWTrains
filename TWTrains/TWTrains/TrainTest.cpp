#include "StdAfx.h"
#include "TrainTest.h"
#include "Train.h"

CTrainTest::CTrainTest(void)
{
}

CTrainTest::~CTrainTest(void)
{
}

void CTrainTest::TestCreateMGraph( MGraph *& pMGraph )
{
	for (VexMap::iterator iter=pMGraph->vexMap.begin( ); iter != pMGraph->vexMap.end( ); ++iter)
	{
		wcout << (*iter).first << _T("   ");
	}
	wcout<<endl;
	
	for ( int n = 0; n < pMGraph->nVexnum;n++ )
	{
		for ( int m = 0; m < pMGraph->nVexnum;m++ )
		{
			if ( pMGraph->ppArcs[n][m].nAdj == INF )
			{
				wcout << -1 << _T("  ");
			}
			else
			{	
				wcout << pMGraph->ppArcs[n][m].nAdj << _T("   ");
			}
			
		}
		wcout<<endl;
	}
}

void CTrainTest::TestShortRouteFunction( TCHAR szSrc,TCHAR szDes ,MGraph * pMGraph ,wstring &strTrip,int &nShortPath )
{
	CTrain obj;
	ErrorCode errcode = obj.ShortRoute(szSrc,szDes,pMGraph,strTrip,nShortPath);
	if (errcode == TS_ERROR_MGRAPH_NOTCREATE)
	{
		wcout<<_T("The MGraph not create!");
		wcout<<endl;
		return;
	}
	if (nShortPath == INF)
	{
		wcout << szSrc << _T(" TO ")<< szDes << _T(" Short distance: ") << _T("NO_SUCH_ROUTE");
		wcout << endl;
		return;
	}
	
	wcout << szSrc << _T(" TO ")<< szDes << _T(" Short distance: ") << nShortPath <<_T("  ") << _T("The Stops:") << strTrip;
	wcout << endl;
}

void CTrainTest::TestRoutePath( TCHAR  szTrack[] ,int nStopNum,int &nLength,MGraph * pMGraph )
{
	CTrain obj;
	ErrorCode errcode = obj.RouteLength(szTrack,nStopNum,nLength,pMGraph);
	if (errcode == TS_ERROR_MGRAPH_NOTCREATE)
	{
		wcout<<_T("The MGraph not create!");
		wcout << endl;
		return;
	}
	if ( nLength == INF )
	{
		wcout <<szTrack<<_T(":  ")<< _T("NO_SUCH_ROUTE");
		wcout << endl;
		return;
	}
	wcout<<szTrack<<_T(":  ")<<nLength <<endl;
	wcout << endl;
}

void CTrainTest::TestRouteNumUnderMaxStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nMaxStops )
{
	CTrain obj;
	int nNums;
	ErrorCode errcode = obj.RouteNumWithMaxStops(szSrc,szDes,pMGraph,nMaxStops,nNums);
	if (errcode == TS_ERROR_MGRAPH_NOTCREATE)
	{
		wcout<<_T("The MGraph not create!");
		wcout << endl;
		return;
	}

	wcout<<_T("The number of trips starting at ")<<szSrc<<_T(" and ending at ")<<szDes<<_T(" with a maximum of ")<<nMaxStops<<_T(": ")<<nNums <<endl;
}

void CTrainTest::TestRouteNumWithExactStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nExactStops )
{
	CTrain obj;
	int nNums;
	ErrorCode errcode = obj.RouteNumWithExactStops(szSrc,szDes,pMGraph,nExactStops,nNums);
	if (errcode == TS_ERROR_MGRAPH_NOTCREATE)
	{
		wcout<<_T("The MGraph not create!");
		wcout << endl;
		return;
	}

	wcout<<_T("The number of trips starting at ")<<szSrc<<_T(" and ending at ")<<szDes<<_T(" with exactly ")<<nExactStops<<_T( " stops: ")<<nNums <<endl;
}

void CTrainTest::TestSearchAllPath( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nMaxRight )
{
	CTrain obj;
	vector<wstring> arrAllPath;
	ErrorCode errcode = obj.SearchAllPath(szSrc,szDes,pMGraph,nMaxRight,arrAllPath);
	if (errcode == TS_ERROR_MGRAPH_NOTCREATE)
	{
		wcout<<_T("The MGraph not create!");
		wcout << endl;
		return;
	}
	wcout<<_T("The number of different routes from ")<<szSrc<<_T(" To ")<<szDes<<_T(" with a distance of less than ")<<nMaxRight<<_T(": ")<<arrAllPath.size() <<endl;
	wcout<<_T("The all routes is : ")<<endl;
	for (vector<wstring>::size_type n = 0; n < arrAllPath.size();n++)
	{
		wcout<<arrAllPath.at(n)<<endl;
	}
}