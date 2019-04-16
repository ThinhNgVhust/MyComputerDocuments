#pragma once
class Robot
{
public:
	Robot(void);
	~Robot(void);
protected:
	double l1,l2;
	double q1,q2;
	double x,y;

public:
	void Setconfig(double par1, double par2);
	void Setjoints(double par1, double par2);
	void Setpos(double par1, double par2);
	double Getx(); double Gety();
	double Getq1(); double Getq2();
	void Getconfig(double &par1, double &par2);
	void DrawRobot(CDC *pDC, int zoom, COLORREF crColor, int x_O, int y_O);
protected:
	void FwdKin();
	void InvKin();
};

