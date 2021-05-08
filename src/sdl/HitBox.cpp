#include "HitBox.h"



hitBox::hitBox(const int& x1, const int& x2, const int& y1, const int& y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

}

hitBox::hitBox()
{
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

int hitBox::getLargeur()const
{
	return x2 - x1;

}

int hitBox::getHauteur()const
{
	return y2 - y1;
}

bool hitBox::is_in(const int x, const int y)const
{
	if (x >= x1 && x <= x2 && y >= y1 && y <= y2) return true;
	return false;
}
void hitBox::reset()
{
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}