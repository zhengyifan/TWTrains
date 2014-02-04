#include "StdAfx.h"
#include "MainGraph.h"

CMainGraph::CMainGraph( TCHAR arrVex[],int vexNum ,VertexAdj arrVexAdj[] ,int nVexAdjNum )
{
	nVexnum         = vexNum;
	arcnum          = nVexAdjNum;
	ppArcs          = new ArcCell*[nVexnum];
	for (int i = 0; i < nVexnum;i++)
	{
		vexMap.insert(pair<TCHAR,int>(arrVex[i],i));
		reversVexMap.insert(pair<int,TCHAR>(i,arrVex[i]));
		ppArcs[i]   = new ArcCell[nVexnum];
		for (int j = 0; j < nVexnum;j++)
		{
				ppArcs[i][j].nAdj = INF;
		}
	}
	for ( int nIndex = 0; nIndex < nVexAdjNum; nIndex++ )
	{
		int vLocation = vexMap[arrVexAdj[nIndex].szSrc];
		int hLocation = vexMap[arrVexAdj[nIndex].szDes];
		ppArcs[vLocation][hLocation].nAdj = arrVexAdj[nIndex].adj;
	}
	initDistanceMatrix();
	initPathMatrix();
}


CMainGraph::~CMainGraph( void )
{
	vexMap.clear();
	reversVexMap.clear();
	int m = 0;
	for ( m = 0;m < nVexnum;m++ )
	{
		delete [] ppArcs[m];
		ppArcs[m] = NULL;

	}
	delete []ppArcs;
	ppArcs = NULL;

	unInitDistanceMatrix();
	unInitPathMatrix();
}

void CMainGraph::initDistanceMatrix()
{
	ppDistancMatrix = new VertexAdj*[nVexnum];
	for ( int n = 0; n < nVexnum; n++ )
	{
		ppDistancMatrix[n] = new VertexAdj[nVexnum];
		for (int m = 0; m < nVexnum; m++)
		{
			//³õÊ¼»¯
			ppDistancMatrix[n][m].adj = ppArcs[n][m].nAdj;
			if (ppDistancMatrix[n][m].adj == 0)
			{
				ppDistancMatrix[n][m].adj = 0;
				ppDistancMatrix[n][m].bFinal = 1;
			}
		}
	}
}

void CMainGraph::unInitDistanceMatrix()
{
	for (int m = 0;m < nVexnum;m++ )
	{
		delete [] ppDistancMatrix[m];
		ppDistancMatrix[m] = NULL;
	}
	delete []ppDistancMatrix;
	ppDistancMatrix = NULL;
}

void CMainGraph::initPathMatrix()
{
	pppPathMatrix   = new bool**[nVexnum];
	for ( int n = 0; n < nVexnum; n++ )
	{
		pppPathMatrix[n]   = new bool*[nVexnum];

		for (int m = 0; m < nVexnum; m++)
		{
			pppPathMatrix[n][m] = new bool[nVexnum]; 
			for (int k = 0; k < nVexnum;k++)
			{
				pppPathMatrix[n][m][k] = 0;
			}
			if ( ppDistancMatrix[n][m].adj < INF )
			{
				pppPathMatrix[n][m][n]  = 1;
				pppPathMatrix[n][m][m]  = 1;
			}

		}
	}
}

void CMainGraph::unInitPathMatrix()
{
	for ( int m = 0 ;m < nVexnum;m++ )
	{
		for ( int n = 0; n < nVexnum; n++ )
		{
			delete [] pppPathMatrix[m][n];
			pppPathMatrix[m][n] = NULL;
		}
		delete [] pppPathMatrix[m];
		pppPathMatrix[m] = NULL;
	}
	delete [] pppPathMatrix;
	pppPathMatrix = NULL;
}
