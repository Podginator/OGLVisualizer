#pragma once


#include <Windows.h>
#include <gl/GL.h>
#include <stdio.h>
#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

//This is an abstract class
//It cannot be instantiated without being inherited by a concrete class
class Renderable
{
    public:

        //this is a pure virtual function
        virtual void Render() = 0;
        virtual void CenterRotate(float deg) = 0;
        virtual void Rotate(float deg) = 0;
        virtual void Scale(float scale) = 0;
};