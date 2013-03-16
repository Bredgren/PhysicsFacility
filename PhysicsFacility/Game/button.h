/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_BUTTON_H_
#define PHYSICSFACILICTYGAME_BUTTON_H_

#include <GL/glew.h>

class Button {
 public:
   Button(GLfloat x, GLfloat y, GLfloat width, GLfloat height) :
     x_(x), y_(y), width_(width/2.0f), height_(height/2.0f), selected_(false) {}

   virtual ~Button() {}

   GLfloat getX() const { return x_; }
   GLfloat getY() const { return y_; }
   bool isSelected() const { return selected_; }

   void ProcessMouse(GLfloat display_x, GLfloat display_y);

 private:
   GLfloat x_, y_, width_, height_;
   bool selected_;
};

#endif  // PHYSICSFACILICTYGAME_BUTTON_H_