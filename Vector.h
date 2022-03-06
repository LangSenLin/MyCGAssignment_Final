#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>                   

/*
 *   类名称：Vector3
 *   类功能：自己实现的一个三维向量类，包含计算长度、正则化、点积和叉积等功能
 */
class Vector3
{
public:
    Vector3() { x = 0.0; y = 0.0; z = 0.0; }
    Vector3(float xx, float yy, float zz)
    {
        x = xx;
        y = yy;
        z = zz;
    }
    Vector3(const Vector3& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    inline float length();                       
    Vector3 normalize();                         
    float dotProduct(const Vector3& v);          
    Vector3 crossProduct(const Vector3& v);      

    Vector3 operator + (const Vector3& v);
    Vector3 operator - (const Vector3& v);
    Vector3 operator * (float scale);
    Vector3 operator / (float scale);
    Vector3 operator - ();

public:
    float x, y, z;

};

#endif 
