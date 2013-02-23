/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_GLCONTEXT_H_
#define PHYSICSFACILICTYGAME_GLCONTEXT_H_

class GLContext {
public:
    GLContext();

    ~GLContext();

    void Init(HWND hWnd);

    void Purge();

    HDC getHDC() { return hDC_; }
    HWND getHWND() { return hWnd_; }

private:
    void reset();

    HDC hDC_;
    HWND hWnd_;
    HGLRC hRC_;

};

extern GLContext glcontext;

#endif  // PHYSICSFACILICTYGAME_GLCONTEXT_H_