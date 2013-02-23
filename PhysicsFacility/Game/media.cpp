/*
 * Copyright 2013 Brandon Edgren
 */

#include "stdafx.h"
#include "media.h"

extern Media media = Media();

Media::~Media() {
  glDeleteVertexArrays(1, &vbo_);
}

//void MainMenu::InitializeVertexBuffers() {
//  GLfloat verticies[] = {
//    // Button Background - 0
//    -button_width,   button_height,
//		 button_width,   button_height,
//		 button_width,  -button_height,
//    -button_width,  -button_height,
//
//    // Play Triangle - 4
//    -button_width/3,  -button_height*3/5,
//		 button_width/3,   0,
//    -button_width/3,   button_height*3/5,
//
//    // Custom Hammer
//    -20.0f, -2.5f,  // Start of handle - 7
//     10.0f, -2.5f,
//     10.0f,  2.5f,
//    -20.0f,  2.5f,
//     10.0f, -4.0f,  // Start of top - 11
//     18.0f, -4.0f,
//     18.0f,  4.0f,
//     10.0f,  4.0f,
//     12.0f, -12.0f,  // Start of back - 15
//     14.0f, -12.0f,
//     18.0f, -4.0f,
//     15.0f, -4.0f,
//     12.0f,  4.0f,  // Start of gap - 19
//     16.0f,  4.0f,
//     16.0f,  8.0f,
//     12.0f,  8.0f,
//     10.0f,  8.0f,  // Start of head - 23
//     18.0f,  8.0f,
//     18.0f,  12.0f,
//     10.0f,  12.0f,
//
//    // Quit X
//    -7.0f,  -12.0f, // Start of first part - 27
//     12.0f,   7.0f,
//      7.0f,  12.0f,
//    -12.0f,  -7.0f,
//      7.0f, -12.0f, // Start of second part - 31
//     12.0f,  -7.0f,
//     -7.0f,  12.0f,
//    -12.0f,   7.0f,
//	};
//
//  glGenBuffers(1, &vertex_buffer_);
//	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
//}

void Media::LoadMedia(Shader *shader) {
  shader_ = shader;

  // Set up locations of elements
  unit_square = 0;

  GLuint vertexbuffer;
  GLuint indexbuffer;
  static const GLfloat vertex_buffer_data[] = {
    // Unit Square
    -0.5f, -0.5f,
    -0.5f,  0.5f,
     0.5f,  0.5f,
     0.5f, -0.5f,
	};

  GLubyte indices[] = {0, 1, 2, 3};

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
                  GLfloat scale_x, GLfloat scale_y, GLfloat angle) {
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
  //kOval,

  case kPlayButton:
    break;
  case kCustomButton:
    break;
  case kQuitButton:
    break;
  case kPlayTriangle:
    break;
  case kCustomHammer:
    break;
  case kQuitX:
    break;

  case kLevelButtonBackground:
    break;

  case kBackButton:
    break;
  case kLevelButtonUnlock:
    break;
  case kLevelButtonLock:
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
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y, GLfloat angle) {
  DrawImage(image, x, y, 1, 1, angle);
}

void Media::DrawImage(Images image, GLfloat x, GLfloat y,
                  GLfloat scale_x, GLfloat scale_y) {
  DrawImage(image, x, y, scale_x, scale_y, 0);
}
void Media::DrawImage(Images image, GLfloat x, GLfloat y) {
  DrawImage(image, x, y, 1, 1, 0);
}