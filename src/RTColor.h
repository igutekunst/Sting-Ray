#pragma once
class RTColor
{
public:
	double r;
	double g;
	double b;
	
	RTColor  add(RTColor other);
	RTColor  sub(RTColor other );
	RTColor  scale(double scalar);
	
	RTColor(double newR, double newG, double newB);
	
	double magnitude();

	RTColor normal();


	RTColor(void);
	~RTColor(void);
	
};

