#ifndef _MATRIX_H
#define _MATRIX_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

typedef struct
{
    GLfloat m[4][4];
} Matrix;

void Scale(Matrix *result, GLfloat sx, GLfloat sy, GLfloat sz);
void Translate(Matrix *result, GLfloat tx, GLfloat ty, GLfloat tz);
void Rotate(Matrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void Frustum(Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void Perspective(Matrix *result, float fovy, float aspect, float nearZ, float farZ);
void Ortho(Matrix *result, float left, float right, float bottom, float top, float nearZ, float farZ);
void MatrixMultiply(Matrix *result, Matrix *srcA, Matrix *srcB);
void MatrixLoadIdentity(Matrix *result);

#endif
