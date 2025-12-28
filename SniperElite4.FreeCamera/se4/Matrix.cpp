#include "Matrix.h"

Vector Matrix::GetForward()
{
	Vector fwd = forward;
	fwd.Normalise();
	Vector f = CrossProduct(fwd, Vector(0, 1, 0));
	return f;
}

Vector Matrix::GetUp()
{
	return Vector(0, -1, 0);
}

Vector Matrix::GetRight()
{
	Vector side = right;
	side.Normalise();
	Vector r = CrossProduct(side, Vector(0, -1, 0));
	return r;
}