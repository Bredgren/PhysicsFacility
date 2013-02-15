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

    HDC hDC;

private:
    void reset();

    HWND hWnd_;
    HGLRC hRC_;

};

extern GLContext glcontext;

#endif  // PHYSICSFACILICTYGAME_GLCONTEXT_H_