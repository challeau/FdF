#include "../../inc/fdf.h"

float	fclampf(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	min(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	max(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
