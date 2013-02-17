/*
 * Copyright 2013 Brandon Edgren
 */

#include "stdafx.h"
#include "button.h"

#define abs(x) ((x ^ (x >> 31)) - (x >> 31))

void Button::ProcessMouse(GLfloat display_x, GLfloat display_y) {
  selected_ = false;
  int dx = (int)(display_x - x_);
  int dy = (int)(display_y - y_);
  if (abs(dx) <= width_ && abs(dy) <= height_)
    selected_ = true;
}