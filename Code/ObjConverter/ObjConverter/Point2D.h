#pragma once

struct Point2D
{
	float X, Y;

	Point2D(): X(0), Y(0)
	{
	}

	Point2D(float x, float y): X(x), Y(y)
	{
	}

	bool operator==(Point2D& ref)
	{
		if(this->X == ref.X && this->Y == ref.Y) return true;
		else return false;
	}

	bool operator!=(Point2D& ref)
	{
		if(this->X == ref.X && this->Y == ref.Y) return false;
		else return true;
	}
};