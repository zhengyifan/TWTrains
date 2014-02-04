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
		����������·��
	*/
	ErrorCode ShortRoute( 
		      TCHAR szSrc,				//[IN]��ʼ��
			  TCHAR szDes,              //[IN]������
			  MGraph * pMGraph ,		//[IN]ͼ
			  wstring &strTrip,         //[OUT]��;������·
			  int &nShortPath			//[OUT]��;����
			  );
	/*
		�趨һ��������վ���������ֵ����������·������
	*/
	ErrorCode RouteNumWithMaxStops( 
		      TCHAR szSrc,				//[IN]��ʼ��
			  TCHAR szDes,				//[IN]������
			  MGraph * pMGraph,			//[IN]ͼ
			  int nMaxStops,			//[IN]���������վ������
			  int &nNums				//[OUT]·������
			  );
	/*
		�趨һ��������վ�������̶�ֵ����������·������
	*/
	ErrorCode RouteNumWithExactStops( TCHAR szSrc,TCHAR szDes,MGraph * pMGraph ,int nExactStops,int &nNums);
	/*
		ָ��·������
	*/
	ErrorCode RouteLength( 
	          const TCHAR szTrack[],	//[IN]·���нڵ㼯��
			  int         nStopNum,		//[IN]�ڵ�����
			  int    &    nLength,		//[OUT]·������
			  MGraph *    pMGraph		//[IN]ͼ
		);
	typedef vector<int>  Path;
	typedef vector<Path> PathArray;
	/*
		�趨һ�������ıߵ�Ȩֵ�����ֵ����������·������
	*/
	ErrorCode SearchAllPath( 
		      TCHAR szSrc,					  //[IN]��ʼ��
			  TCHAR szDes,					  //[IN]������
			  const MGraph * pMGraph ,		  //[IN]ͼ
			  int nMaxRight,				  //[IN]���бߵ����Ȩֵ
			  vector<wstring> & arrStrAllPath //[OUT]����·��
			  );
private:
	/*
		DFS��·���ı��������㷨
	*/
	ErrorCode DFSAllSimplePath( 
		      int nSrc,                       //[IN]��ʼ�������
			  int nDes,						  //[IN]�����������
			  const MGraph * pMGraph ,
			  Path &path,					  //[OUT]��ǰ·��
			  bool * &Visited,                //[OUT]�Ƿ���ʵı�־λ
			  PathArray & arrPath			  //[OUT]����·��
			  );
	/*
		DFS����·���ı��������㷨
	*/
	ErrorCode DFSAllPath( 
		      int nSrc,						  //[IN]��ʼ�������
			  int nDes,						  //[IN]�����������
			  const MGraph * pMGraph ,		  //[IN]ͼ
			  int nCurrentRight,			  //[IN]��ǰ�����б�Ȩֵ֮��
			  int nMaxRight,				  //[IN]���бߵ����Ȩֵ
			  Path &path,					  //[OUT]��ǰ·��
			  PathArray & arrPath             //[OUT]����·��
			  );
	/*
		������·��
	*/
	ErrorCode OutPutShortRoute( 
		      int nSrc,						  //[IN]��ʼ�������
			  int nDst,						  //[IN]�����������
			  const MGraph * pMGraph ,		  //[IN]ͼ
			  wstring &strTrip,				  //[OUT]��;������·
			  int &nShortPath				  //[OUT]��;����
			  );
	/*
		�������·��
	*/
	ErrorCode OutPutAllRoute( 
		      const PathArray &arrPath,      //[IN]����·�����
		      vector<wstring> &arrStrTrip,   //[OUT]���е�·��
		      const MGraph * pMGraph         //[IN]ͼ 
		      );
	/*
		��鿪ʼ���Ƿ��г��ߣ��������Ƿ������
	*/
	ErrorCode SimpleCheckNoRoute( 
		      TCHAR szSrc,					 //[IN]��ʼ��
			  TCHAR szDes ,					 //[IN]������
			  const MGraph *pMGraph ,		 //[IN]ͼ
			  bool &bNoRoute				 //[OUT]�Ƿ���·��
			  );
};

#endif