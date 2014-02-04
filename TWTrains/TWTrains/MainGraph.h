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
	VexMap        vexMap;           //����ӳ������
	ReversVexMap  reversVexMap;     //����ӳ�䶥��
	AdjMatrix     ppArcs;           //��Ӿ���
	int           nVexnum;          //ͼ��ǰ�Ķ�����
	int           arcnum;           //����	
	VertexAdj **  ppDistancMatrix;  //���·������
	bool      *** pppPathMatrix;    //���·����P[0][1][]��ʾ����0������1��·���������ĸ���P[0][1][i]����TRUE      
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
