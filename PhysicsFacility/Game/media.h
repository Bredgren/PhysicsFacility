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
    //kOval,

    kPlayButton, kCustomButton, kQuitButton,
    kPlayTriangle, kCustomHammer, kQuitX,

    kLevelButtonBackground,

    kBackButton, kLevelButtonUnlock, kLevelButtonLock,
    kBackTriangle, kLock,

    kEditPencil,
  };

  void LoadMedia(Shader *shader);

  void DrawImage(Images image, GLfloat x, GLfloat y, 
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle);
  void DrawImage(Images image, GLfloat x, GLfloat y, GLfloat angle);
  void DrawImage(Images image, GLfloat x, GLfloat y,
                  GLfloat scale_x, GLfloat scale_y);
  void DrawImage(Images image, GLfloat x, GLfloat y);

 private:
  Shader *shader_;
  GLuint vbo_;
  void *unit_square;
};

extern Media media;

#endif  // PHYSICSFACILICTYGAME_MEDIA_HPP