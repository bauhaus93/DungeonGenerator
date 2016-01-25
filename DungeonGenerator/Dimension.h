#pragma once

#include <stdexcept>

#include "Defs.h"

typedef class Dimension Size;
typedef class Dimension Rotation;


class Dimension{

private:
	float		dim[3];

public:
				Dimension(float x, float y, float z);
				Dimension();
				~Dimension();

	float		GetX() const{ return dim[0]; };
	float		GetY() const{ return dim[1]; };
	float		GetZ() const{ return dim[2]; };

	void		SetX(float x){ dim[0] = x; };
	void		SetY(float y){ dim[1] = y; };
	void		SetZ(float z){ dim[2] = z; };

	void		ModX(float x){ dim[0] += x; };
	void		ModY(float y){ dim[1] += y; };
	void		ModZ(float z){ dim[2] += z; };

	float&			operator[](Dim index);
	const float&	operator[](Dim index) const;

};

inline float& Dimension::operator[](Dim index){
		return dim[static_cast<size_t>(index)];
}

inline const float& Dimension::operator[](Dim index) const{
	return dim[static_cast<size_t>(index)];
}

