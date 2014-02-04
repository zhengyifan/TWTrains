/* /////////////////////////////////////////////////////////////////////////
* File:        TrainDataDef.h
* Purpose:     The Data's define which used in Train solution
* Created:     May 28,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */
#ifndef _TRAINDATADEF_H_ 
#define _TRAINDATADEF_H_ 

#include <map>
#include <string>
#include <vector>
using namespace std;

const int INF = 0x3F3F3F3F;
typedef struct tag_ArcCell {
	int nAdj;
}ArcCell,**AdjMatrix;

typedef std::map< TCHAR,int > VexMap;
typedef std::map< int ,TCHAR> ReversVexMap;
typedef struct tag_vertexAdj
{
	int   adj;
	bool  bFinal;    //�Ƿ������·��
	TCHAR szSrc;     //Դ��
	TCHAR szDes;     //Ŀ��
	tag_vertexAdj()
	{	
		adj    = INF;
		bFinal = 0;
	}
}VertexAdj,*pVertexAdj;

typedef struct tag_MGraph 
{
	VexMap        vexMap;           //����ӳ������
	ReversVexMap  reversVexMap;     //����ӳ�䶥��
	AdjMatrix     ppArcs;           //��Ӿ���
	int           nVexnum;          //ͼ��ǰ�Ķ�����
	int           arcnum;           //����	
	VertexAdj **  ppDistancMatrix;  //���·������
	bool      *** pppPathMatrix;    //���·����P[0][1][]��ʾ����0������1��·���������ĸ���P[0][1][i]����TRUE      

    tag_MGraph( TCHAR  arrVex[],int vexNum ,VertexAdj  arrVexAdj[] ,int nVexAdjNum )
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
				//if (j == i)
				//{
				//	ppArcs[i][j].nAdj = 0;
				//}
				//else
				{
					ppArcs[i][j].nAdj = INF;
				}

			}
		}
		for ( int nIndex = 0; nIndex < nVexAdjNum; nIndex++ )
		{
			int vLocation = vexMap[arrVexAdj[nIndex].szSrc];
			int hLocation = vexMap[arrVexAdj[nIndex].szDes];
			ppArcs[vLocation][hLocation].nAdj = arrVexAdj[nIndex].adj;
		}	

		ppDistancMatrix = new VertexAdj*[nVexnum];
		pppPathMatrix   = new bool**[nVexnum];
		for ( int n = 0; n < nVexnum; n++ )
		{
			ppDistancMatrix[n] = new VertexAdj[nVexnum];
			pppPathMatrix[n]   = new bool*[nVexnum];

			for (int m = 0; m < nVexnum; m++)
			{
				//��ʼ��
				ppDistancMatrix[n][m].adj = ppArcs[n][m].nAdj;
				if (ppDistancMatrix[n][m].adj == 0)
				{
					ppDistancMatrix[n][m].adj = 0;
					ppDistancMatrix[n][m].bFinal = 1;
				}

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
	~tag_MGraph()
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
		
		for ( m = 0;m < nVexnum;m++ )
		{
			delete [] ppDistancMatrix[m];
			ppDistancMatrix[m] = NULL;
		}
		delete []ppDistancMatrix;
		ppDistancMatrix = NULL;

		for ( m = 0 ;m < nVexnum;m++ )
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
private:
	tag_MGraph& operator = (const tag_MGraph&);
	tag_MGraph(const tag_MGraph&); 
	void initArcs();

}MGraph,*pMGraph;

#endif