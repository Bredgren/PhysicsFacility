/*
 * Copyright 2013 Brandon Edgren
 */
#include "stdafx.h"
#include "main_menu.h"

const GLfloat MainMenu::button_width = 64.0f / 2.0f;
const GLfloat MainMenu::button_height = 32.0f / 2.0;

MainMenu::MainMenu() :
  play(42.0f, 26.0f, button_width, button_height),
  custom(42.0f, 68.0f, button_width, button_height),
  quit(42.0f, 110.0f, button_width, button_height) {
}

MainMenu::~MainMenu() {
    glDeleteBuffers(1, &vertex_buffer_);
}

bool MainMenu::Init(Shader *shader) {
  shader_ = shader;

  InitializeVertexBuffers();

  return true;
}

GameState::State MainMenu::ProcessMouse(bool left_button, 
                                        GLfloat display_x, 
                                        GLfloat display_y) {
  play.ProcessMouse(display_x, display_y);
  custom.ProcessMouse(display_x, display_y);
  quit.ProcessMouse(display_x, display_y);

  if (left_button && play.isSelected())
    return GameState::kGame;

  return GameState::kMainMenu;
}

void MainMenu::Draw() {
  SetupButton(play);
  DrawPlayButton();

  SetupButton(custom);
  DrawCustomButton();

  SetupButton(quit);
  DrawQuitButton();
}

void MainMenu::SetupButton(Button button) {
  GLfloat angle = 0;
  if (button.isSelected()) angle = 10.0f;
  shader_->setModelView(glm::rotate<GLfloat>(glm::mat4(), 
                        angle, glm::vec3(0,0,1)));
  shader_->leftMultModelView(glm::translate<GLfloat>(
           glm::mat4(), glm::vec3(button.getX(), button.getY(), 0.0f)));
	shader_->updateModelView();
}

void MainMenu::DrawPlayButton() {
	DrawButtonBackground();
  shader_->setColor(1.0f, 1.0f, 1.0f);
  DrawPlayTriangle();
  shader_->setColor(0.0f, 0.0f, 0.0f);
}

void MainMenu::DrawCustomButton() {
	DrawButtonBackground();
  shader_->setColor(1.0f, 1.0f, 1.0f);
  DrawCustomHammer();
  shader_->setColor(0.0f, 0.0f, 0.0f);
}

void MainMenu::DrawQuitButton() {
	DrawButtonBackground();
  shader_->setColor(1.0f, 1.0f, 1.0f);
  DrawQuitX();
  shader_->setColor(0.0f, 0.0f, 0.0f);
}

void MainMenu::InitializeVertexBuffers() {
  GLfloat verticies[] = {
    // Button Background - 0
    -button_width,   button_height,
		 button_width,   button_height,
		 button_width,  -button_height,
    -button_width,  -button_height,

    // Play Triangle - 4
    -button_width/3,  -button_height*3/5,
		 button_width/3,   0,
    -button_width/3,   button_height*3/5,

    // Custom Hammer
    -20.0f, -2.5f,  // Start of handle - 7
     10.0f, -2.5f,
     10.0f,  2.5f,
    -20.0f,  2.5f,
     10.0f, -4.0f,  // Start of top - 11
     18.0f, -4.0f,
     18.0f,  4.0f,
     10.0f,  4.0f,
     12.0f, -12.0f,  // Start of back - 15
     14.0f, -12.0f,
     18.0f, -4.0f,
     15.0f, -4.0f,
     12.0f,  4.0f,  // Start of gap - 19
     16.0f,  4.0f,
     16.0f,  8.0f,
     12.0f,  8.0f,
     10.0f,  8.0f,  // Start of head - 23
     18.0f,  8.0f,
     18.0f,  12.0f,
     10.0f,  12.0f,

    // Quit X
    -7.0f,  -12.0f, // Start of first part - 27
     12.0f,   7.0f,
      7.0f,  12.0f,
    -12.0f,  -7.0f,
      7.0f, -12.0f, // Start of second part - 31
     12.0f,  -7.0f,
     -7.0f,  12.0f,
    -12.0f,   7.0f,
	};

  glGenBuffers(1, &vertex_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
}

void MainMenu::DrawButtonBackground() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
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

void MainMenu::DrawPlayTriangle() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLES, 4, 3);
	glDisableVertexAttribArray(0);
}

void MainMenu::DrawCustomHammer() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 4);
  glDrawArrays(GL_TRIANGLE_FAN, 11, 4);
  glDrawArrays(GL_TRIANGLE_FAN, 15, 4);
  glDrawArrays(GL_TRIANGLE_FAN, 19, 4);
  glDrawArrays(GL_TRIANGLE_FAN, 23, 4);
	glDisableVertexAttribArray(0);
}
void MainMenu::DrawQuitX() {
  glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 4);
  glDrawArrays(GL_TRIANGLE_FAN, 31, 4);
	glDisableVertexAttribArray(0);
}