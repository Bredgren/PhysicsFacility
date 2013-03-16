/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_MEDIA_HPP
#define PHYSICSFACILICTYGAME_MEDIA_HPP

#include <GL/glew.h>
#include <glm.hpp>

#include <Shaders/shader.h>

class Media {
 public:
  Media() {}
  ~Media();

  enum Images {
    kRectBlack, kRectWhite,
    kTriangleBlack, kTriangleWhite,
    //kOval,

    kPlayButton, kCustomButton, kQuitButton,

    kLevelButtonBackground,

    kBackButton, kLevelButtonUnlock, kLevelButtonLock,
    kBackTriangle, kLock,

    kEditPencil,
  };

  void LoadMedia(Shader *shader);

  void DrawImage(Images image, GLfloat x, GLfloat y, 
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle, int num);
  void DrawImage(Images image, GLfloat x, GLfloat y, 
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle);
  void DrawImage(Images image, GLfloat x, GLfloat y, GLfloat angle);
  void DrawImage(Images image, GLfloat x, GLfloat y,
                  GLfloat scale_x, GLfloat scale_y);
  void DrawImage(Images image, GLfloat x, GLfloat y);

  void DrawNumberBlack(int num, GLfloat x, GLfloat y, 
                       GLfloat scale, GLfloat angle);
  void DrawNumberWhite(int num, GLfloat x, GLfloat y, 
                       GLfloat scale, GLfloat angle);

  void Draw0to9Black(int num, GLfloat x, GLfloat y, 
                     GLfloat scale, GLfloat angle);
  void Draw0to9White(int num, GLfloat x, GLfloat y, 
                     GLfloat scale, GLfloat angle);

 private:
  Shader *shader_;
  GLuint vbo_;
  void *unit_square;
  void *unit_triangle;

  void DrawNumber(int num,  GLfloat x, GLfloat y, 
                  GLfloat scale, GLfloat angle, bool black);
  void Draw0to9(int num, GLfloat x, GLfloat y, 
                GLfloat scale, GLfloat angle, bool black);
};

extern Media media;

#endif  // PHYSICSFACILICTYGAME_MEDIA_HPP