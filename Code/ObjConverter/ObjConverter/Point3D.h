#pragma once

struct Point3D
{
	float X, Y, Z;

	Point3D(): X(0), Y(0), Z(0)
	{
	}

	Point3D(float x, float y, float z): X(x), Y(y), Z(z)
	{
	}

	bool operator==(Point3D& ref)
	{
		if(this->X == ref.X && this->Y == ref.Y && this->Z == ref.Z) return true;
		else return false;
	}

	bool operator!=(Point3D& ref)
	{
		if(this->X == ref.X && this->Y == ref.Y && this->Z == ref.Z) return false;
		else return true;
	}
};