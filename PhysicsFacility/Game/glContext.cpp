/*
 * Copyright 2013 Brandon Edgren
 */

#include "stdafx.h"

extern GLContext glcontext = GLContext();

GLContext::GLContext(void) {
	reset();
}


GLContext::~GLContext(void) {
	Purge();
}

void GLContext::Init(HWND hWnd) {
    // remember the window handle (HWND)
    hWnd_ = hWnd;

    // get the device context (DC)
    hDC = GetDC(hWnd_);

    // set the pixel format for the DC
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int format = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, format, &pfd);

    // create the render context (RC)
    hRC_ = wglCreateContext(hDC);

    // make it the current render context
    wglMakeCurrent(hDC, hRC_);
}

void GLContext::Purge() {
    if (hRC_) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hRC_);
    }

    if (hWnd_ && hDC)
        ReleaseDC(hWnd_, hDC);

    reset();
}

void GLContext::reset(){
  hDC = NULL;
	hWnd_ = NULL;
	hRC_ = NULL;
}