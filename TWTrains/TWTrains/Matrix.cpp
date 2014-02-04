#include "StdAfx.h"
#include "Matrix.h"

const int DefaultModulo = 9973;
CMatrix::CMatrix( int nVexnum ):
m_lModulo(DefaultModulo),
m_ppMatrix(NULL)
{
	m_nVexNum = nVexnum;
	m_ppMatrix = new int*[m_nVexNum];
	for ( int n = 0 ;n < m_nVexNum; n++ )
	{
		m_ppMatrix[n] = new int[m_nVexNum];
		for ( int m = 0; m < m_nVexNum; m++ )
		{
			m_ppMatrix[n][m] = 0;
		}
	}
}

CMatrix::CMatrix( const CMatrix &other )
{
	m_nVexNum  = other.m_nVexNum;
	m_ppMatrix = new int* [m_nVexNum];
	m_lModulo  = other.m_lModulo;
	for ( int n = 0 ;n < m_nVexNum; n++ )
	{
		m_ppMatrix[n] = new int[m_nVexNum];
		for ( int m = 0; m < m_nVexNum; m++ )
		{
			m_ppMatrix[n][m] = other.m_ppMatrix[n][m];
		}
	}
}

CMatrix CMatrix::operator +(const CMatrix & other)
{
	CMatrix res(m_nVexNum);
	for( int n = 0; n < m_nVexNum; n++ )
		for( int m = 0; m < m_nVexNum; m++)
			res.m_ppMatrix[n][m]=(this->m_ppMatrix[n][m]+other.m_ppMatrix[n][m]) % m_lModulo;

	return res;
}

CMatrix::~CMatrix(void)
{
	int m;
	for ( m = 0;m < m_nVexNum;m++ )
	{
		delete [] m_ppMatrix[m];
		m_ppMatrix[m] = NULL;

	}
	delete []m_ppMatrix;
	m_ppMatrix = NULL;
}

CMatrix CMatrix::operator*( CMatrix param)
{
	CMatrix product(m_nVexNum);
	product.setModulo(DefaultModulo);
	for (int i=0; i<m_nVexNum; i++)
	{
		for (int j=0; j<m_nVexNum; j++)
		{
			for (int k=0; k<m_nVexNum; k++)
			{
				product.m_ppMatrix[i][j]+=m_ppMatrix[i][k]*param.m_ppMatrix[k][j];
				product.m_ppMatrix[i][j]%=m_lModulo;
			}
		}
	}
	
	return product;
}

CMatrix CMatrix::power( int exp)
{
	CMatrix tmp(m_nVexNum);
	tmp = (*this) * (*this);
	if (exp==1) return *this;
	else if (exp & 1) return tmp.power(exp/2) * (*this);
	else return tmp.power(exp/2);
}

void CMatrix::setModulo( int nModulo)
{
	m_lModulo = nModulo;
}

CMatrix CMatrix::powerAccumulation( int nFrequency )
{
	if( nFrequency==1) 
		return *this;
	
	int nMid = nFrequency / 2;
	if (nFrequency % 2 == 1)
	{
		nMid++;
	}

	CMatrix tmp = powerAccumulation( nFrequency / 2 );
	CMatrix fac = power(nMid);

	CMatrix res = fac * tmp + tmp;
	if (nFrequency % 2 == 1)
	{
		res  = res + fac;
	}

	return res;
}

CMatrix CMatrix::operator=( const CMatrix & other )
{
	this->m_lModulo = other.m_lModulo;
	for (int n = 0 ; n < m_nVexNum;n++)
	{
		for ( int m = 0; m < m_nVexNum;m++ )
		{
			this->m_ppMatrix[n][m] = other.m_ppMatrix[n][m];
		}
	}
	return *this;
}
