#pragma once
class RTColor
{
public:
	double r;
	double g;
	double b;
	
	RTColor  RTColor::add(RTColor other);
	RTColor  RTColor::sub(RTColor other );
	RTColor RTColor::scale(double scalar);
	
	RTColor(double newR, double newG, double newB);
	
	double magnitude();

	RTColor normal();


	RTColor(void);
	~RTColor(void);
	
};

