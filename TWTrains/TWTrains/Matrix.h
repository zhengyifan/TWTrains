/* /////////////////////////////////////////////////////////////////////////
* File:        Matrix.h
* Purpose:     Matrix Class
* Created:     May 31,2011
* Author :     Evan Zheng
* Email  :     zheng_yifan@hotmail.com
* ///////////////////////////////////////////////////////////////////////// */
#ifndef _TRAINMATRIX_H_ 
#define _TRAINMATRIX_H_ 

class CMatrix
{
public:
	CMatrix( int nVexnum );
	~CMatrix(void);
	CMatrix(const CMatrix &other);
	CMatrix operator* (CMatrix);
	CMatrix operator + (const CMatrix & other);
	CMatrix operator =(const CMatrix & other);
	CMatrix power(int);            //A^k
	void    setModulo(int);        //设置矩阵模
	CMatrix powerAccumulation(int);//A + A^2 + A^3 + ... + A^k
public:
	int ** m_ppMatrix;//初始化矩阵
private:
	long m_lModulo;
	int  m_nVexNum;
};

#endif