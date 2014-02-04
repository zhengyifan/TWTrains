/* /////////////////////////////////////////////////////////////////////////
* File:        Train.h
* Purpose:     The Main Class
* Created:     May 29,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */
#ifndef _TRAIN_H
#define _TRAIN_H

#include "TrainDataDef.h"
class CTrain
{
public:
	CTrain(void);
	~CTrain(void);
public:
	/*
		求两点间最短路径
	*/
	ErrorCode ShortRoute( 
		      TCHAR szSrc,				//[IN]开始点
			  TCHAR szDes,              //[IN]结束点
			  MGraph * pMGraph ,		//[IN]图
			  wstring &strTrip,         //[OUT]沿途经过的路
			  int &nShortPath			//[OUT]沿途长度
			  );
	/*
		设定一个经过的站点数量最大值，求两点间的路径数量
	*/
	ErrorCode RouteNumWithMaxStops( 
		      TCHAR szSrc,				//[IN]开始点
			  TCHAR szDes,				//[IN]结束点
			  MGraph * pMGraph,			//[IN]图
			  int nMaxStops,			//[IN]经过的最大站点数量
			  int &nNums				//[OUT]路径数量
			  );
	/*
		设定一个经过的站点数量固定值，求两点间的路径数量
	*/
	ErrorCode RouteNumWithExactStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nExactStops,int &nNums);
	/*
		指定路径长度
	*/
	ErrorCode RouteLength( 
	          const TCHAR szTrack[],	//[IN]路径中节点集合
			  int         nStopNum,		//[IN]节点数量
			  int    &    nLength,		//[OUT]路径长度
			  MGraph *    pMGraph		//[IN]图
		);
	typedef vector<int>  Path;
	typedef vector<Path> PathArray;
	/*
		设定一个经过的边的权值的最大值，求两点间的路径数量
	*/
	ErrorCode SearchAllPath( 
		      TCHAR szSrc,					  //[IN]开始点
			  TCHAR szDes,					  //[IN]结束点
			  const MGraph * pMGraph ,		  //[IN]图
			  int nMaxRight,				  //[IN]所有边的最大权值
			  vector<wstring> & arrStrAllPath //[OUT]所有路径
			  );
private:
	/*
		DFS简单路径的遍历搜索算法
	*/
	ErrorCode DFSAllSimplePath( 
		      int nSrc,                       //[IN]开始点横坐标
			  int nDes,						  //[IN]结束点横坐标
			  const MGraph * pMGraph ,
			  Path &path,					  //[OUT]当前路径
			  bool * &Visited,                //[OUT]是否访问的标志位
			  PathArray & arrPath			  //[OUT]所有路径
			  );
	/*
		DFS所有路径的遍历搜索算法
	*/
	ErrorCode DFSAllPath( 
		      int nSrc,						  //[IN]开始点横坐标
			  int nDes,						  //[IN]结束点横坐标
			  const MGraph * pMGraph ,		  //[IN]图
			  int nCurrentRight,			  //[IN]当前的所有边权值之和
			  int nMaxRight,				  //[IN]所有边的最大权值
			  Path &path,					  //[OUT]当前路径
			  PathArray & arrPath             //[OUT]所有路径
			  );
	/*
		输出最短路径
	*/
	ErrorCode OutPutShortRoute( 
		      int nSrc,						  //[IN]开始点横坐标
			  int nDst,						  //[IN]结束点横坐标
			  const MGraph * pMGraph ,		  //[IN]图
			  wstring &strTrip,				  //[OUT]沿途经过的路
			  int &nShortPath				  //[OUT]沿途长度
			  );
	/*
		输出所有路径
	*/
	ErrorCode OutPutAllRoute( 
		      const PathArray &arrPath,      //[IN]所有路径序号
		      vector<wstring> &arrStrTrip,   //[OUT]所有的路径
		      const MGraph * pMGraph         //[IN]图 
		      );
	/*
		检查开始点是否有出边，结束点是否有入边
	*/
	ErrorCode SimpleCheckNoRoute( 
		      TCHAR szSrc,					 //[IN]开始点
			  TCHAR szDes ,					 //[IN]结束点
			  const MGraph *pMGraph ,		 //[IN]图
			  bool &bNoRoute				 //[OUT]是否有路径
			  );
};

#endif