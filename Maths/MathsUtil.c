#include "MathsUtil.h"
#include <math.h>

float mathDegToRad(float deg) {
	return (float)(deg / 360 * 2 * M_PI);
}

void mathCrossProduct(const float a[3], const float b[3], float cross[3]) {
	cross[0] = ((a[1] * b[2]) - (a[2] * b[1]));
	cross[1] = -((a[0] * b[2]) - (a[2] * b[0]));
	cross[2] = ((a[0] * b[1]) - (a[1] * b[0]));
}

void mathNormVector(const float v[3], float norm[3]) {
	float length = (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	norm[0] = v[0] / length;
	norm[1] = v[1] / length;
	norm[2] = v[2] / length;	
}
