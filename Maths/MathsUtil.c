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

void mathVector3Add(const float a[3], const float b[3], float c[3]) {
	int i;
	for (i = 0; i < 3; i++) {
		c[i] = a[i] + b[i];
	}
}

void mathVector3Subtract(const float a[3], const float b[3], float c[3]) {
	int i;
	for (i = 0; i < 3; i++) {
		c[i] = a[i] - b[i];
	}
}

void mathVector3MultiplyScalar(const float scalar, const float vector[3], float result[3]) {
	int i;
	for (i = 0; i < 3; i++) {
		result[i] = scalar * vector[i];
	}
}

