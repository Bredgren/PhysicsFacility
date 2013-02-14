
#ifndef PHYSICSFACILICTYGAME_GLCONTEXT_H_
#define PHYSICSFACILICTYGAME_GLCONTEXT_H_

class GLContext {
public:
    GLContext();

    ~GLContext();

    void init(HWND hWnd);

    void purge();

    HDC hDC;

private:
    void reset();

    HWND hWnd_;
    HGLRC hRC_;

};

extern GLContext glcontext;

#endif  // PHYSICSFACILICTYGAME_GLCONTEXT_H_