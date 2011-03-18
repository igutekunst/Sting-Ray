#pragma once
class RayVector
{
public:
	RayVector(double x, double y, double z);
	~RayVector(void);

	double x;
	double y;
	double z;
	double rho;
	double theta;
	double r;
	double fdif(double a, double b);
public:

};

