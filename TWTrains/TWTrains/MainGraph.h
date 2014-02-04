/* /////////////////////////////////////////////////////////////////////////
* File:        TrainDataDef.h
* Purpose:     The Data's define which used in Train solution
* Created:     May 28,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */
#ifndef _MainGraph_H_ 
#define _MainGraph_H_ 
#include "TrainDataDef.h"
class CMainGraph
{
public:
	VexMap        vexMap;           //顶点映射坐标
	ReversVexMap  reversVexMap;     //坐标映射顶点
	AdjMatrix     ppArcs;           //领接矩阵
	int           nVexnum;          //图当前的顶点数
	int           arcnum;           //弧数	
	VertexAdj **  ppDistancMatrix;  //存放路径长度
	bool      *** pppPathMatrix;    //存放路径，P[0][1][]表示顶点0到顶点1的路径，经过哪个点P[0][1][i]就是TRUE      
	CMainGraph( TCHAR  arrVex[],int vexNum ,VertexAdj  arrVexAdj[] ,int nVexAdjNum );
	~CMainGraph(void);
private:
	void initDistanceMatrix();
	void unInitDistanceMatrix();
	void initPathMatrix();
	void unInitPathMatrix();
	CMainGraph& operator = (const tag_MGraph&);
	CMainGraph(const tag_MGraph&); 
};
#endif
