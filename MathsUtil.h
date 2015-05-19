#ifndef MATHSUTIL_H
#define MATHSUTIL_H

#define M_PI 3.1415926535897932384626433832795

float mathDegToRad(float deg);

void mathCrossProduct(const float a[3], const float b[3], float cross[3]);

void mathNormVector(const float v[3], float normed[3]);

#endif