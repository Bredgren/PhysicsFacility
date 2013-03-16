/*
 * Copyright 2013 Brandon Edgren
 */

#include "stdafx.h"
#include "media.h"

extern Media media = Media();

Media::~Media() {
  glDeleteVertexArrays(1, &vbo_);
}

void Media::LoadMedia(Shader *shader) {
  shader_ = shader;

  // Set up locations of elements
  unit_square = (void *) 0;
  unit_triangle = (void *) 4;

  // For scaling the hammer from its original coordinates so that it is
  // on a common size with everything else, i.e., it looks right when it is
  // scaled by the same amount as the button.
  float xscale = 60.0f;
  float yscale = 30.0f;

  GLuint vertexbuffer;
  GLuint indexbuffer;
  static const GLfloat vertex_buffer_data[] = {
    // Unit Square
    -0.5f, -0.5f,
    -0.5f,  0.5f,
     0.5f,  0.5f,
     0.5f, -0.5f,

    // Unit Triangle
    -0.5f,  -0.5f,
		 0.5f,   0.0f,
    -0.5f,   0.5f,

    // Custom Hammer
    -20.0f/xscale, -2.5f/yscale,  // Start of handle - 7
     10.0f/xscale, -2.5f/yscale,
     10.0f/xscale,  2.5f/yscale,
    -20.0f/xscale,  2.5f/yscale,
     10.0f/xscale, -4.0f/yscale,  // Start of top - 11
     18.0f/xscale, -4.0f/yscale,
     18.0f/xscale,  4.0f/yscale,
     10.0f/xscale,  4.0f/yscale,
     12.0f/xscale, -12.0f/yscale,  // Start of back - 15
     14.0f/xscale, -12.0f/yscale,
 //    18.0f/xscale, -4.0f/yscale, // same as 12
     15.0f/xscale, -4.0f/yscale,
     12.0f/xscale,  4.0f/yscale,  // Start of gap - 19
     16.0f/xscale,  4.0f/yscale,
     16.0f/xscale,  8.0f/yscale,
     12.0f/xscale,  8.0f/yscale,
     10.0f/xscale,  8.0f/yscale,  // Start of head - 23
     18.0f/xscale,  8.0f/yscale,
     18.0f/xscale,  12.0f/yscale,
     10.0f/xscale,  12.0f/yscale,
	};

  GLubyte indices[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                       15, 16, 12, 17, 18, 19, 20, 21, 22, 23, 24, 25};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
  
  glGenBuffers(1, &indexbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vbo_);
  glBindVertexArray(vbo_);
  shader_->enableDataPointers();
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  shader_->setVertexPointer(0, reinterpret_cast<void*>(0));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
  glBindVertexArray(NULL);
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y, 
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle, int num) {
  glm::mat4 matrix = shader_->getModelView();  // save
  shader_->setModelView(glm::scale<GLfloat>(glm::mat4(), glm::vec3(scale_x, scale_y, 0)));
  shader_->leftMultModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_->leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(x, y, 0.0f)));
	shader_->updateModelView();

  glBindVertexArray(vbo_);
  switch (image) {
  case kRectBlack:
    shader_->setColor(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, unit_square);
    break;
  case kRectWhite:
    shader_->setColor(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, unit_square);
    break;
  case kTriangleBlack:
    shader_->setColor(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, unit_triangle);
    break;
  case kTriangleWhite:
    shader_->setColor(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, unit_triangle);
    break;
  //kOval,

  case kPlayButton: {
    float width  = scale_x * 0.375f;
    float height = scale_y * 0.714f;
    DrawImage(kRectBlack, x, y, scale_x, scale_y, angle);
    DrawImage(kTriangleWhite, x, y, width, height, angle);
    break;
  }
  case kCustomButton: {
    DrawImage(kRectBlack, x, y, scale_x, scale_y, angle);
    shader_->setColor(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, (void*)7);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, (void*)11);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, (void*)15);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, (void*)19);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, (void*)23);
    break;
  }
  case kQuitButton: {
    float width  = scale_x * 0.4f;
    float height = scale_y * 0.2f;
    DrawImage(kRectBlack, x, y, scale_x, scale_y, angle);
    DrawImage(kRectWhite, x, y, width, height, angle+45);
    DrawImage(kRectWhite, x, y, width, height, angle-45);
    break;
  }
  case kLevelButtonBackground:
    break;

  case kBackButton: {
    DrawImage(kPlayButton, x, y, scale_x, scale_y, angle + 180);
    break;
  }
  case kLevelButtonUnlock:
    DrawImage(kRectBlack, x, y, scale_x, scale_y, angle);
    DrawImage(kRectWhite, x, y, scale_x * 0.9f, scale_y * 0.9f, angle);
    DrawNumberBlack(1, x, y, scale_y * 0.5, angle);
    break;
  case kLevelButtonLock:
    DrawImage(kRectWhite, x, y, scale_x, scale_y, angle);
    DrawImage(kRectBlack, x, y, scale_x * 0.9f, scale_y * 0.9f, angle);
    DrawNumberWhite(1, x, y - 0.25f * scale_y, scale_y * 0.3f, angle);
    // Draw lock
    DrawImage(kRectWhite, x, y + 0.25f * scale_y, scale_x * 0.22f, scale_y * 0.18f, angle);
    DrawImage(kRectWhite, x, y + 0.1f * scale_y, scale_x * 0.18f, scale_y * 0.12f, angle);
    DrawImage(kRectBlack, x, y + 0.11f * scale_y, scale_x * 0.14f, scale_y * 0.10f, angle);
    DrawImage(kRectBlack, x, y + 0.23f * scale_y, scale_x * 0.04f, scale_y * 0.04f, angle);
    DrawImage(kRectBlack, x, y + 0.26f * scale_y, scale_x * 0.02f, scale_y * 0.06f, angle);
    break;
  case kBackTriangle:
    break;
  case kLock:
    break;

  case kEditPencil:
    break;

  default:
    break;
  }

  shader_->setModelView(matrix);  // restore
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y, 
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle) {
  DrawImage(image, x, y, scale_x, scale_y, angle, 0);
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y, GLfloat angle) {
  DrawImage(image, x, y, 1, 1, angle, 0);
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y,
                  GLfloat scale_x, GLfloat scale_y) {
  DrawImage(image, x, y, scale_x, scale_y, 0, 0);
}
void Media::DrawImage(Images image, GLfloat x, GLfloat y) {
  DrawImage(image, x, y, 1, 1, 0, 0);
}

void Media::DrawNumber(int num, GLfloat x, GLfloat y, GLfloat scale,
                       GLfloat angle, bool black) {
  if (black)
    Draw0to9Black(num, x, y, scale, angle);
  else
    Draw0to9White(num, x, y, scale, angle);
}

void Media::DrawNumberBlack(int num, GLfloat x, GLfloat y, 
                            GLfloat scale, GLfloat angle) {
  DrawNumber(num, x, y, scale, angle, true);
}

void Media::DrawNumberWhite(int num, GLfloat x, GLfloat y, 
                            GLfloat scale, GLfloat angle) {
  DrawNumber(num, x, y, scale, angle, false);
}

void Media::Draw0to9(int num, GLfloat x, GLfloat y, GLfloat scale,
                     GLfloat angle, bool black) {
  GLfloat width = scale * 0.5f;
  GLfloat height = scale;
  if (black)
    DrawImage(kRectBlack, x, y, width, height, angle);
  else
    DrawImage(kRectWhite, x, y, width, height, angle);

  switch (num) {
  case 0:
    if (black)
      DrawImage(kRectWhite, x, y, width * 0.5f, height * 0.6f, angle);
    else
      DrawImage(kRectBlack, x, y, width * 0.5f, height * 0.6f, angle);
    break;
  case 1:
    if (black)
      DrawImage(kRectWhite, x - width * 0.3f, y, width * 0.6f, height, angle);
    else
      DrawImage(kRectBlack, x - width * 0.3f, y, width * 0.6f, height, angle);
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    break;
  case 9:
    break;
  default:
    break;
  }
}

void Media::Draw0to9Black(int num, GLfloat x, GLfloat y, 
                     GLfloat scale, GLfloat angle) {
  Draw0to9(num, x, y, scale, angle, true);
}
void Media::Draw0to9White(int num, GLfloat x, GLfloat y, 
                     GLfloat scale, GLfloat angle) {
  Draw0to9(num, x, y, scale, angle, false);
}