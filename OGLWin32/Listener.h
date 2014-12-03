#pragma once

class Listener
{
public:
    static bool keys[256];
    virtual bool MouseMove ( int x, int y ) = 0;
    virtual bool MouseLBDown ( int x, int y ) = 0;
    virtual bool MouseLBUp ( int x, int y ) = 0;
    virtual bool MouseWheel(float delta) = 0;
protected:
    virtual bool MouseInside(int x, int y) = 0;
    bool MouseDown = false;
	bool MouseIn = false;
    float x = 0;
    float y = 0;
    float scale = 1;
};