#include "stdafx.h"
#include "Robot.h"
#include "math.h"

Robot::Robot(void)
{
	l1=0.25;
	l2=0.15;
	q1=0; q2=0;
	FwdKin();
}

Robot::~Robot(void)
{
}

void Robot::FwdKin()
{
	x=l1*cos(q1)+l2*cos(q1+q2);
	y=l1*sin(q1)+l2*sin(q1+q2);
}
void Robot::InvKin()
{
	q2=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
	q1=atan2(y,x)-atan2(l2*sin(q2),l1+l2*cos(q2));
}

void Robot::Setconfig(double par1, double par2)
{
	l1=par1; l2=par2;
	FwdKin();
}
void Robot::Setjoints(double par1, double par2)
{
	q1=par1; q2=par2;
	FwdKin();
}
void Robot::Setpos(double par1, double par2)
{
	x=par1; y=par2;
	InvKin();
}
double Robot::Getx() { return x; }
double Robot::Gety() { return y; }
double Robot::Getq1() { return q1;}
double Robot::Getq2() { return q2;}

void Robot::Getconfig(double &par1, double &par2)
{
	par1=l1; par2=l2;
}
void Robot::DrawRobot(CDC *pDC, int zoom, COLORREF crColor, int x_O, int y_O)
{
	pDC->SetBkMode(TRANSPARENT);
	CPen *pPen=new CPen(PS_SOLID,3,crColor);
    CBrush *pBrush=new CBrush(crColor);
	pDC->SelectObject(pPen);
	pDC->SelectObject(pBrush);
	
	pDC->MoveTo(x_O,y_O);
	int x_j = x_O+l1*cos(q1)*zoom; int y_j = y_O-l1*sin(q1)*zoom;
	pDC->LineTo(x_j,y_j);
	int x_e = x_O+x*zoom; int y_e = y_O-y*zoom;
	pDC->LineTo(x_e,y_e);

	pDC->Ellipse(x_O-8,y_O-8,x_O+8,y_O+8);
	pDC->Ellipse(x_j-8,y_j-8,x_j+8,y_j+8);
	pDC->Ellipse(x_e-8,y_e-8,x_e+8,y_e+8);
	CRect rect(x_O-20, y_O, x_O+20, y_O+20);
	pDC->FrameRect(rect,pBrush);

	delete pDC->SelectStockObject(WHITE_PEN);
	delete pDC->SelectStockObject(WHITE_BRUSH);
}
