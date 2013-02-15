/*
 * Copyright 2013 Brandon Edgren
 */
#include "stdafx.h"
#include "main_menu.h"

const GLfloat MainMenu::button_width = 75.0f / 2.0f;
const GLfloat MainMenu::button_height = 50.0f / 2.0;

MainMenu::MainMenu() {
  b1.x = 100.0f;
  b1.y = 100.0f;
  b1.selected = false;
  b2.x = 100.0f;
  b2.y = 200.0f;
  b2.selected = false;
}

MainMenu::~MainMenu() {
    glDeleteBuffers(1, &button_background_vertex_buffer_);
}

bool MainMenu::Init(Shader *shader) {
  shader_ = shader;

  InitializeVertexBuffers();

  return true;
}

GameState::State MainMenu::ProcessMouse(bool left_button, 
                                        float display_x, 
                                        float display_y) {
  b1.selected = false;
  b2.selected = false;
  int d1x = display_x - b1.x;
  int d1y = display_y - b1.y;
  int d2x = display_x - b2.x;
  int d2y = display_y - b2.y;
  if (((d1x ^ (d1x >> 31)) - (d1x >> 31)) <= button_width &&
      ((d1y ^ (d1y >> 31)) - (d1y >> 31)) <= button_height) {
    b1.selected = true;
  } else if (((d2x ^ (d2x >> 31)) - (d2x >> 31)) <= button_width &&
             ((d2y ^ (d2y >> 31)) - (d2y >> 31)) <= button_height) {
    b2.selected = true;
  }
  return GameState::kMainMenu;
}

void MainMenu::Draw() {
 // glClear(GL_COLOR_BUFFER_BIT);

  //shader_.setColor(0.0f, 1.0f, 1.0f);

  int angle = 0;
  if (b1.selected) angle = 10;
  shader_->setModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_->leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(b1.x, b1.y, 0.0f)));
	shader_->updateModelView();
	DrawButtonBackground();

  angle = 0;
  if (b2.selected) angle = 10;
  shader_->setModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_->leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(b2.x, b2.y, 0.0f)));
	shader_->updateModelView();
	DrawButtonBackground();
}

void MainMenu::InitializeVertexBuffers() {
  static const GLfloat vertex_buffer_[] = { 
    -button_width,   button_height,
		 button_width,   button_height,
		 button_width,  -button_height,
    -button_width,  -button_height,
	};

  glGenBuffers(1, &button_background_vertex_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, button_background_vertex_buffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_), vertex_buffer_, GL_STATIC_DRAW);
}

void MainMenu::DrawButtonBackground() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, button_background_vertex_buffer_);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // 4 indices starting at 0

	glDisableVertexAttribArray(0);
}