#pragma once
#include <math.h>

float FLerp(float v0, float v1, float t)
{
	return v0+(v1-v0)*t;
}

float FRound(float val, int figures)
{
	return floorf(val * 10 * figures) / (10 * figures);
}
