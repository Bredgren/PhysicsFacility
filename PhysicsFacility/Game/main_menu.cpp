/*
 * Copyright 2013 Brandon Edgren
 */
#include "stdafx.h"
#include "main_menu.h"
#include "media.h"

const GLfloat MainMenu::button_width = 64.0f;
const GLfloat MainMenu::button_height = 32.0f;

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

  return true;
}

GameState::State MainMenu::ProcessMouse(bool left_button, 
                                        GLfloat display_x, 
                                        GLfloat display_y) {
  play.ProcessMouse(display_x, display_y);
  custom.ProcessMouse(display_x, display_y);
  quit.ProcessMouse(display_x, display_y);

  if (left_button) {
    if (play.isSelected())
      return GameState::kLevelSelect;
    if (custom.isSelected())
      return GameState::kCustomLevelSelect;
    if (quit.isSelected())
      return GameState::kQuit;
  }

  return GameState::kMainMenu;
}

void MainMenu::Draw() {
  media.DrawImage(media.kPlayButton, play.getX(), play.getY(),
                  button_width, button_height,
                  play.isSelected() ? 10.0f : 0.0f);

  media.DrawImage(media.kCustomButton, custom.getX(), custom.getY(),
                  button_width, button_height,
                  custom.isSelected() ? 10.0f : 0.0f);

  media.DrawImage(media.kQuitButton, quit.getX(), quit.getY(),
                  button_width, button_height,
                  quit.isSelected() ? 10.0f : 0.0f);

  media.DrawImage(media.kRectBlack, 100, 50, 20, 20);
  media.DrawImage(media.kRectWhite, 100, 50, 10, 10);
  //SetupButton(play);
  //DrawPlayButton();
  //shader_->setColor(1.0f, 0.0f, 0.0f);
  //media.DrawImage(media.kRect, 50, 50, 10, 10, 0);

  //SetupButton(custom);
  //DrawCustomButton();

  //SetupButton(quit);
  //DrawQuitButton();
}

//void MainMenu::SetupButton(Button button) {
//  GLfloat angle = 0;
//  if (button.isSelected()) angle = 10.0f;
//  shader_->setModelView(glm::rotate<GLfloat>(glm::mat4(), 
//                        angle, glm::vec3(0,0,1)));
//  shader_->leftMultModelView(glm::translate<GLfloat>(
//           glm::mat4(), glm::vec3(button.getX(), button.getY(), 0.0f)));
//	shader_->updateModelView();
//}
//
//void MainMenu::DrawPlayButton() {
//	DrawButtonBackground(play);
//  //shader_->setColor(1.0f, 0.0f, 0.0f);
//  //DrawPlayTriangle();
//}
//
//void MainMenu::DrawCustomButton() {
//	DrawButtonBackground(custom);
//  shader_->setColor(1.0f, 1.0f, 1.0f);
//  DrawCustomHammer();
//  shader_->setColor(0.0f, 0.0f, 0.0f);
//}
//
//void MainMenu::DrawQuitButton() {
//	DrawButtonBackground(quit);
//  shader_->setColor(1.0f, 1.0f, 1.0f);
//  DrawQuitX();
//  shader_->setColor(0.0f, 0.0f, 0.0f);
//}
//
//void MainMenu::DrawButtonBackground(Button button) {
//  shader_->setColor(0.0f, 0.0f, 0.0f);
//  media.DrawImage(media.kRect, button.getX(), button.getY(),
//                  button_width, button_height,
//                  button.isSelected() ? 10.0f : 0.0f);
//}
//
//void MainMenu::DrawPlayTriangle() {
//  shader_->setColor(1.0f, 1.0f, 1.0f);
//  media.DrawImage(media.kRect, play.getX(), play.getY(),
//                  button_width, button_height,
//                  play.isSelected() ? 10.0f : 0.0f);
//}
//
//void MainMenu::DrawCustomHammer() {
//
//}
//void MainMenu::DrawQuitX() {
//
//}