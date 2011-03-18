#pragma once
#include "RTVector.h"
class RTMatrix
{
public:
	double mat[4][4];
	RTMatrix(void);
	
	~RTMatrix(void);
	
	RTMatrix(double a0, double a1, double a2, double a3,  
		     double b0, double b1, double b2, double b3,
			 double c0, double c1, double c2, double c3,
			 double d0, double d1, double d2, double d3);
	//construct a transformation matrix from the three axis of the target space
	RTMatrix::RTMatrix(RTVector xAxis, RTVector yAxis, RTVector zAxis,RTVector newOrigin);

	// transformation of position vector
	static RTVector multiply_m_v(RTMatrix & m, RTVector & v);
	RTMatrix RTMatrix::inverse();
	// transformation of direction vector (i.e., no translation)
	static RTVector multiply_m_v_dir(RTMatrix & m, RTVector & vdir);
	void swapRows(int i, int j);
	void addToRow(int row, double rowToAdd[4]);
	void subFromRow(int row, double rowToSub[4]);
	void scaleRow(int row, double scalar);
	void swapColumns(int i, int j);
	void flip();
	void transpose();
};