#include "RTMatrix.h"


RTMatrix::RTMatrix(double x0, double y0, double z0, double w0,  
				   double x1, double y1, double z1, double w1,
				   double x2, double y2, double z2, double w2,
				   double x3, double y3, double z3, double w3)
{
	mat[0][0] = x0; mat[0][1]=y0; mat[0][2]=z0; mat[0][3]=w0;
	mat[1][0] = x1; mat[1][1]=y1; mat[1][2]=z1; mat[1][3]=w1;
	mat[2][0] = x2; mat[2][1]=y2; mat[2][2]=z2; mat[2][3]=w2;
	mat[3][0] = x3; mat[3][1]=y3; mat[3][2]=z3; mat[3][3]=w3;
}

//construct a transformation matrix from the three axis of the target space
RTMatrix::RTMatrix(RTVector xAxis, RTVector yAxis, RTVector zAxis,RTVector newOrigin){
	mat[0][0] = xAxis.x;	 mat[0][1]=xAxis.y;		mat[0][2]=xAxis.z;	   mat[0][3]=0;
	mat[1][0] = yAxis.x;	 mat[1][1]=yAxis.y;		mat[1][2]=yAxis.z;	   mat[1][3]=0;
	mat[2][0] = zAxis.x;	 mat[2][1]=zAxis.y;		mat[2][2]=zAxis.z;	   mat[2][3]=0;
	mat[3][0] = newOrigin.x; mat[3][1]=newOrigin.y; mat[3][2]=newOrigin.z; mat[3][3]=1;
}

/*


	mat[0][0] = xAxis.x;	 mat[0][1]=yAxis.x;		mat[0][2]=zAxis.x;	   mat[0][3]=0;
	mat[1][0] = xAxis.y;	 mat[1][1]=yAxis.y;		mat[1][2]=zAxis.y;	   mat[1][3]=0;
	mat[2][0] = xAxis.z;	 mat[2][1]=yAxis.z;		mat[2][2]=zAxis.z;	   mat[2][3]=0;
	mat[3][0] = newOrigin.x; mat[3][1]=newOrigin.y; mat[3][2]=newOrigin.z; mat[3][3]=1;
*/
RTMatrix::RTMatrix(void)
{
	
}


RTMatrix::~RTMatrix(void)
{
}

void RTMatrix::swapRows(int i, int j)
{
	double temp;
	for(int x =0; x<4;x++)
	{
		temp = mat[i][x];
		mat[i][x] = mat[j][x];
		mat[j][x] = temp;
	}
	
	
	
}

void RTMatrix::swapColumns(int i, int j)
{
	double temp;
	for(int row =0; row<4;row++)
	{
		temp = mat[row][i];
		mat[row][i] = mat[row][j];
		mat[row][j]= temp;
	}
	
	
	
}

void RTMatrix::flip()
{
	swapRows(1,2);
	swapRows(0,3);
	swapColumns(1,2);
	swapColumns(0,3);

}

void RTMatrix::transpose()
{
	RTMatrix tranpose = *this;
	double temp;
	for(int i =0; i<4; i++)
	{
		for (int j =0; j<4; j++)
		{
			temp = mat[i][j];
			mat[j][i] = mat[i][j];
			mat[i][j] = temp;
		}
	}
}


void RTMatrix::scaleRow(int row , double scalar)
{
	for(int i=0; i<4;i++){
		mat[row][i] *=scalar;
	}
}


RTMatrix RTMatrix::inverse(){
	//make a local copy for now
	RTMatrix inv = *this;
	RTMatrix id = RTMatrix(1,0,0,0,
						   0,1,0,0,
						   0,0,1,0,
						   0,0,0,1);
	//  j 0	1	2		i
	// x0	y0	z0	|	0
	// x1	y1	z1	|	1	
	// x2	y2	z2	|	2


	//keepign two || matrices, one being 4x4 identity
	

	int i=1;
	int j=0;
	while( i < 4 && j<4){
		if(	inv.mat[i-1][i-1]==0)
		{
			//need to swap some rows
			for(int k=i;k<4;k++)
			{
				if(inv.mat[k][i-1]!=0)
				{
					inv.swapRows(i-1,k);
					 id.swapRows(i-1,k);
					break;
				}
				if(k==3)
				{
					
				}
			}
		}
		//else replace row with ithrow - ( (xi/x0) * row above it from (i-1)th row) )
		for(int k = i; k<4;k++){
			if(inv.mat[k][i-1]!=0)
			{
				double scalar = inv.mat[k][i-1] /  inv.mat[i-1][i-1];
			
					for(int j =0; j<4;j++)
					{
						inv.mat[k][j] -= inv.mat[i-1][j] * scalar;
						 id.mat[k][j] -=  id.mat[i-1][j] * scalar;
				}
				
			
			}
		}
	 i++;	
	}
	
	
	i=2;
	j=3;
	while( i >= 0 ){
		if(	inv.mat[i+1][i+1]==0)
		{
			//need to swap some rows
			for(int k=i;k>4;k--)
			{
				if(inv.mat[k][i+1]!=0)
				{
					inv.swapRows(i+1,k);
					 id.swapRows(i+1,k);
					break;
				}
				if(k==0)
				{
					
				}
			}
		}
		//else replace row with ithrow - ( (xi/x0) * row above it from (i-1)th row) )
		for(int k = i; k>=0;k--){
			if(inv.mat[k][i+1]!=0)
			{
 				double scalar = inv.mat[k][i+1] /  inv.mat[i+1][i+1];
			
					for(int j =4; j>=0;j--)
					{
						inv.mat[k][j] -= inv.mat[i+1][j] * scalar;
						 id.mat[k][j] -=  id.mat[i+1][j] * scalar;
				}
				
			
			}
		}
	 i--;	
	}


	for(int i=0; i<4; i++)
	{
		double scalar = 1/inv.mat[i][i];

			inv.scaleRow(i,scalar);
			id.scaleRow(i,scalar);
		
	}
	return id;
}

 
