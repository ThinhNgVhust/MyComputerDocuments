#include "stdafx.h"
#include "Trajectory.h"
#include "math.h"

Trajectory::Trajectory(void)
{
	type =1;
	x0=0.3; y0=-0.1; x1=0; y1=0.2;
	cex=0.2;cey=0.15;ra=0.1;
	speed=1;
	t=0;
	ComputePos();
}
Trajectory::~Trajectory(void)
{}

void Trajectory::SetLine(double px0, double py0, 
						 double px1, double py1, double spd)
{
	x0=px0; y0=py0; x1=px1; y1=py1; speed=spd;
}
void Trajectory::SetCircle(double px, double py, double pra, double spd)
{
	cex=px; cey=py; ra=pra; speed=spd;
}
void Trajectory::SetType(int tp)
{
	type=tp;
}
void Trajectory::SetTime(double time)
{
	t=time;
	ComputePos();
}
double Trajectory::Getx() { return x; }
double Trajectory::Gety() { return y; }

void Trajectory::GetLine(double &px0, double &py0, double &px1, double &py1, double &spd)
{
	px0=x0; py0=y0; px1=x1; py1=y1; spd=speed;
}
void Trajectory::GetCircle(double &px, double &py, double &pra, double &spd)
{
	px=cex; py=cey; pra=ra; spd=speed;
}
void Trajectory::ComputePos()
{
	float u=(sin(speed*t)+1)/2;
	switch (type)
	{
		case 1:
			x=x0+u*(x1-x0);
			y=y0+u*(y1-y0);
			break;
		case 2:
			float phi = u*2*3.14;
			x=cex+ra*cos(phi);
			y=cey+ra*sin(phi);
			break;
	}
}

void Trajectory::DrawTrajectory(CDC *pDC, int zoom, 
								COLORREF crColor, int x_O, int y_O)
{
	pDC->SetBkMode(TRANSPARENT);
	CPen *pPen=new CPen(PS_SOLID,1,crColor);
	pDC->SelectObject(pPen);

	switch (type)
	{
		case 1:
			pDC->MoveTo(x_O+x0*zoom,y_O-y0*zoom);
			pDC->LineTo(x_O+x1*zoom,y_O-y1*zoom);
			break;
		case 2:
			pDC->MoveTo(x_O+(cex+ra)*zoom,y_O-cey*zoom);
			pDC->AngleArc(x_O+cex*zoom,y_O-cey*zoom,ra*zoom,0,360);
			break;
	}

	delete pDC->SelectStockObject(WHITE_PEN);
}
