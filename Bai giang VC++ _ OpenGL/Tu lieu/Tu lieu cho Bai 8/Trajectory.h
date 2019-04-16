#pragma once
class Trajectory
{
public:
	Trajectory(void);
	~Trajectory(void);
protected:
	int type;
	double x0,y0,x1,y1;
	double cex,cey,ra;
	double speed;
	double t, x, y;
public:
	void SetLine(double px0, double py0, double px1, double py1, double spd);
	void SetCircle(double px, double py, double pra, double spd);
	void SetType(int tp);
	void SetTime(double time);
	double Getx(); double Gety();
	void GetLine(double &px0, double &py0, double &px1, double &py1, double &spd);
	void GetCircle(double &px, double &py, double &pra, double &spd);
	void DrawTrajectory(CDC *pDC, int zoom, COLORREF crColor, int x_O, int y_O);
protected:
	void ComputePos();
};

