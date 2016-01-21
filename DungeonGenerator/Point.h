#pragma once

typedef class Point Size;

class Point{

protected:
	float		x;
	float		y;
	float		z;

public:
				Point(float xArg, float yArg, float zArg);
				~Point();

	float		GetX() const{ return x; };
	float		GetY() const{ return y; };
	float		GetZ() const{ return z; };

	void		Set(float xNew, float yNew, float zNew){ SetX(xNew); SetY(yNew); SetZ(zNew); };
	void		SetX(float xNew){ x = xNew; };
	void		SetY(float yNew){ y = yNew; };
	void		SetZ(float zNew){ z = zNew; };

};



