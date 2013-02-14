
#ifndef PHYSICSFACILICTYGAME_GLCONTEXT_H_
#define PHYSICSFACILICTYGAME_GLCONTEXT_H_

class GLContext {
public:
    GLContext();

    ~GLContext();

    void init(HWND hWnd);

    void purge();

private:
    void reset();

    HWND mhWnd;
    HDC mhDC;
    HGLRC mhRC;

};

extern GLContext glcontext;

#endif  // PHYSICSFACILICTYGAME_GLCONTEXT_H_