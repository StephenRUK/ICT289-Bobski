#ifndef MATHSUTIL_H
#define MATHSUTIL_H

#define M_PI 3.1415926535897932384626433832795

float mathDegToRad(float deg);

void mathCrossProduct(const float a[3], const float b[3], float cross[3]);

void mathNormVector(const float v[3], float normed[3]);

void mathVector3Add(const float a[3], const float b[3], float c[3]);

void mathVector3Subtract(const float a[3], const float b[3], float c[3]);

void mathVector3MultiplyScalar(const float scalar, const float vector[3], float result[3]);

#endif