#pragma once

class Listener
{
public:
    virtual bool MouseMove ( int x, int y ) = 0;
    virtual bool MouseLBDown ( int x, int y ) = 0;
    virtual bool MouseLBUp ( int x, int y ) = 0;
    virtual bool MouseWheel(float detla) = 0;
protected:
    virtual bool MouseInside(int x, int y) = 0;
    bool MouseDown = false;
    float x = 0;
    float y = 0;
};