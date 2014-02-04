#include "StdAfx.h"
#include "Train.h"
#include "TrainDataDef.h"
#include "Matrix.h"
CTrain::CTrain(void)
{

}

CTrain::~CTrain(void)
{

}

ErrorCode CTrain::ShortRoute( TCHAR szSrc,TCHAR szDes ,MGraph * pMGraph ,wstring &strTrip,int &nShortPath )
{
	ErrorCode errcode = TS_ERROR_SUCCESS;
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	nShortPath = INF;
	strTrip = _T("");
	//��������Ƿ����ͨ·
	bool bNoRoute = true;
    errcode = SimpleCheckNoRoute(szSrc,szDes,pMGraph,bNoRoute);
	if (errcode == TS_ERROR_SUCCESS)
	{
		if (bNoRoute)
		{
			return TS_ERROR_SUCCESS;
		}
	}

	int nSrcLocation = pMGraph->vexMap[szSrc];
	int nDstLocation = pMGraph->vexMap[szDes];

	//1)����õ��Ѿ�������·�������
	if ( 1 == pMGraph->ppDistancMatrix[nSrcLocation][nDstLocation].bFinal )
	{
		nShortPath = pMGraph->ppDistancMatrix[nSrcLocation][nDstLocation].adj;
		return OutPutShortRoute(nSrcLocation,nDstLocation,pMGraph,strTrip,nShortPath);
	}
	//DIJKSTRA�㷨
	for ( int i = 1; i < pMGraph->nVexnum; i++)
	{
		int min = INF;
		int v  = nDstLocation;
		int w  = 0;
		for (w = 0 ; w < pMGraph->nVexnum; w++ )
		{
			if ( !pMGraph->ppDistancMatrix[nSrcLocation][w].bFinal )
			{
				if ( pMGraph->ppDistancMatrix[nSrcLocation][w].adj < min )
				{
				   v = w;
				   min = pMGraph->ppDistancMatrix[nSrcLocation][w].adj;
				}
			}
		}

		pMGraph->ppDistancMatrix[nSrcLocation][v].bFinal = 1;
		for ( w = 0; w < pMGraph->nVexnum; w++ )
		{
			if ( !pMGraph->ppDistancMatrix[nSrcLocation][w].bFinal && (min + pMGraph->ppArcs[v][w].nAdj < pMGraph->ppDistancMatrix[nSrcLocation][w].adj))//��Ҫ�������������
			{
				pMGraph->ppDistancMatrix[nSrcLocation][w].adj = min + pMGraph->ppArcs[v][w].nAdj;
				for (int j = 0; j < pMGraph->nVexnum;j++)
				{
					pMGraph->pppPathMatrix[nSrcLocation][w][j] = pMGraph->pppPathMatrix[nSrcLocation][v][j];
				}
				pMGraph->pppPathMatrix[nSrcLocation][w][w] = 1;
			}
		}
		//�����ǰ�ڵ��ǽ����㣬�򷵻ؽ���������ٱ�����ȥ
		if (v == nDstLocation)
		{
			nShortPath = pMGraph->ppDistancMatrix[nSrcLocation][v].adj;
			return OutPutShortRoute(nSrcLocation,nDstLocation,pMGraph,strTrip,nShortPath);
		}
        
	}

	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::RouteLength( const TCHAR szTrack[] ,int nStopNum,int &nLength,MGraph * pMGraph)
{
	if ( pMGraph == NULL )
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	if ( nStopNum == 0 || szTrack == NULL )
	{
		return TS_ERROR_INPUT_TRACK_ERR;
	}

	nLength = 0;
	TCHAR szPre = szTrack[0];
	TCHAR szNext = szTrack[0];
	for ( int n = 0; n < nStopNum; n++ )
	{
		if ( n + 1 == nStopNum)
		{
			return TS_ERROR_SUCCESS;
			
		}
		szNext = szTrack[n+1];
		int i = pMGraph->vexMap[szPre];
		int j = pMGraph->vexMap[szNext];
		if (pMGraph->ppArcs[i][j].nAdj == INF)
		{
			nLength = INF;
			return TS_ERROR_SUCCESS;
		}
		nLength += pMGraph->ppArcs[i][j].nAdj;

		szPre = szNext;
	}
	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::OutPutShortRoute( int nSrcLocation,int nDstLocation,const MGraph * pMGraph ,wstring &strTrip,int &nShortPath )
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}

	nShortPath = pMGraph->ppDistancMatrix[nSrcLocation][nDstLocation].adj;
	if (nShortPath == INF)
	{
		return TS_ERROR_SUCCESS;
	}

	TCHAR *pTrip = new TCHAR[pMGraph->nVexnum + 1];
	memset(pTrip,0,sizeof(TCHAR)*(pMGraph->nVexnum + 1));
	int m = 0;
	Path path;
	
	for (int n = 0;n < pMGraph->nVexnum;n++)
	{
		bool bStop = pMGraph->pppPathMatrix[nSrcLocation][nDstLocation][n];
		if (bStop)
		{
			//����ߺͽڵ��ַ�һһ��Ӧ
			ReversVexMap::const_iterator resIter = pMGraph->reversVexMap.find(n);
			pTrip[m++] = resIter->second;
		}
	}
	strTrip = pTrip;
	delete [] pTrip;
	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::RouteNumWithMaxStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nMaxStops,int &nNums )
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	nNums = 0;
	//��������Ƿ����ͨ·
	bool bNoRoute = true;
	ErrorCode errcode = SimpleCheckNoRoute(szSrc,szDes,pMGraph,bNoRoute);
	if (errcode == TS_ERROR_SUCCESS)
	{
		if (bNoRoute)
		{
			return TS_ERROR_SUCCESS;
		}
	}

	//������A + A^2 + A^3 + ... + A^k֮�ͣ��ҵ���Ӧ�ķ���������nMaxStops����Ӧ��·������,ͼ�۶���
	CMatrix matrix(pMGraph->nVexnum);
	for (int n = 0;n < pMGraph->nVexnum;n++)
	{
		for ( int m = 0; m < pMGraph->nVexnum;m++ )
		{
			if ( (pMGraph->ppArcs[n][m].nAdj != INF) && (n != m))
			{
				matrix.m_ppMatrix[n][m] = 1;
			}
			else
			{
				matrix.m_ppMatrix[n][m] = 0;
			}
		}
	}

	CMatrix tmp(pMGraph->nVexnum);
	tmp = matrix.powerAccumulation(nMaxStops);

	int nHlocation = pMGraph->vexMap[szSrc];
	int nVlocation = pMGraph->vexMap[szDes];
	nNums = tmp.m_ppMatrix[nHlocation][nVlocation];

	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::RouteNumWithExactStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nExactStops,int &nNums)
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	//������k���ݣ��ҵ���Ӧ�ķ���������nExactStops����Ӧ��·������
	CMatrix matrix(pMGraph->nVexnum);
	for (int n = 0;n < pMGraph->nVexnum;n++)
	{
		for ( int m = 0; m < pMGraph->nVexnum;m++ )
		{
			if ( (pMGraph->ppArcs[n][m].nAdj != INF) && (n != m))
			{
				matrix.m_ppMatrix[n][m] = 1;
			}
			else
			{
				matrix.m_ppMatrix[n][m] = 0;
			}
		}
	}
	CMatrix tmp(pMGraph->nVexnum);
	tmp = matrix.power(nExactStops);

	int nHlocation = pMGraph->vexMap[szSrc];
	int nVlocation = pMGraph->vexMap[szDes];
	nNums = tmp.m_ppMatrix[nHlocation][nVlocation];
	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::DFSAllSimplePath( int nSrc,int nDes,const MGraph * pMGraph ,Path &path,bool * &Visited,PathArray & arrPath)
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}

	if (Visited[nSrc])   
		return TS_ERROR_SUCCESS; 

	path.push_back(nSrc);
	if( nSrc == nDes)   
	{ 
		arrPath.push_back(path);
	}   
	else   
	{ 
		Visited[nSrc] = true; 
		for( int i = 0;i < pMGraph->nVexnum;i++ )   
		{
			if   (pMGraph->ppArcs[nSrc][i].nAdj != INF && !Visited[i])  
			{                                 
				DFSAllSimplePath( i,nDes,pMGraph,path,Visited,arrPath ); 
			} 
		}	
		Visited[nSrc]   =   false; 
	}

	Path::iterator iter = path.end() - 1;
	path.erase(iter);
	return TS_ERROR_SUCCESS; 
}
ErrorCode CTrain::DFSAllPath( int nSrc,int nDes,const MGraph * pMGraph ,int nCurrentRight,int nMaxRight ,Path &path,PathArray & arrPath)
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}

	if (nCurrentRight > nMaxRight)
	{
		return TS_ERROR_SUCCESS;
	}

	path.push_back(nSrc);
	if( nSrc == nDes)   
	{ 
		//���⿪ʼ��ͽ�������ͬʱ����ʼ��ֱ��������
		if (nCurrentRight > 0)
		{
			arrPath.push_back(path);
		}
	}
	for( int i = 0;i < pMGraph->nVexnum;i++ )   
	{
		if   (pMGraph->ppArcs[nSrc][i].nAdj != INF )  
		{                                 
			if ( nCurrentRight + pMGraph->ppArcs[nSrc][i].nAdj < nMaxRight )
			{
				nCurrentRight += pMGraph->ppArcs[nSrc][i].nAdj;
				DFSAllPath( i,nDes,pMGraph,nCurrentRight,nMaxRight,path,arrPath ); 
				nCurrentRight -= pMGraph->ppArcs[nSrc][i].nAdj;
			}

		} 
	}	
	//�˳���ǰѭ����path����
	Path::iterator iter = path.end() - 1;
	path.erase(iter);
	return TS_ERROR_SUCCESS; 
}
ErrorCode CTrain::SearchAllPath( TCHAR szSrc,TCHAR szDes,const MGraph * pMGraph ,int nMaxRight ,vector<wstring> & arrStrAllPath )
{	
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	arrStrAllPath.clear();

	//��������Ƿ����ͨ·
	bool bNoRoute = true;
	ErrorCode errcode = SimpleCheckNoRoute(szSrc,szDes,pMGraph,bNoRoute);
	if (errcode == TS_ERROR_SUCCESS)
	{
		if (bNoRoute)
		{
			return TS_ERROR_SUCCESS;
		}
	}

	VexMap::const_iterator iter ;
	iter = pMGraph->vexMap.find(szSrc);
	int nSrcLocation = iter->second;
	iter = pMGraph->vexMap.find(szDes);
	int nDstLocation = iter->second;

	PathArray  arrPath;
	arrPath.clear();
	Path path;
	path.clear();
	int nCurrentRight    = 0;

    errcode = DFSAllPath(nSrcLocation,nDstLocation,pMGraph,nCurrentRight,nMaxRight,path,arrPath);	
	if (errcode == TS_ERROR_SUCCESS)
	{
		OutPutAllRoute(arrPath,arrStrAllPath,pMGraph);
	}
	return errcode;
}

ErrorCode CTrain::SimpleCheckNoRoute( TCHAR szSrc,TCHAR szDes ,const MGraph *pMGraph ,bool &bNoRoute)
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}
	VexMap::const_iterator iter ;
	iter = pMGraph->vexMap.find(szSrc);
	int nSrcLocation = iter->second;
	iter = pMGraph->vexMap.find(szDes);
	int nDstLocation = iter->second;

	bNoRoute = true; 
	//��ʼ��û�г��ȣ�������㶼û��·
	for ( int n = 0;n < pMGraph->nVexnum;n++ )
	{
		if ( pMGraph->ppArcs[nSrcLocation][n].nAdj != INF )
		{
			bNoRoute = false;
			return TS_ERROR_SUCCESS;
		}
	}
	//������û����ȣ���Զ�����ܵ���
	for ( int n = 0;n < pMGraph->nVexnum;n++ )
	{
		if ( pMGraph->ppArcs[n][nDstLocation].nAdj != INF )
		{
			bNoRoute = false;
			return TS_ERROR_SUCCESS;
		}
	}

	return TS_ERROR_SUCCESS;
}

ErrorCode CTrain::OutPutAllRoute( const PathArray &arrPath,vector<wstring> &arrStrTrip ,const MGraph * pMGraph)
{
	if (pMGraph == NULL)
	{
		return TS_ERROR_MGRAPH_NOTCREATE;
	}

	for (PathArray::size_type n = 0; n < arrPath.size();n++)
	{
		TCHAR *pTrip = new TCHAR[arrPath.at(n).size() + 1];
		memset(pTrip,0,sizeof(TCHAR)*(arrPath.at(n).size() + 1));
		int t = 0;
		for (Path::size_type m = 0;m < arrPath.at(n).size();m++)
		{
			//����ߺͽڵ��ַ�һһ��Ӧ
			ReversVexMap::const_iterator resIter = pMGraph->reversVexMap.find(arrPath.at(n).at(m));
			pTrip[t++] = resIter->second;
		}
		wstring strTrip = pTrip;
		arrStrTrip.push_back(strTrip);
		delete [] pTrip;
	}

	return TS_ERROR_SUCCESS;
}