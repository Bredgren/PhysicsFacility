/*
 * Copyright 2013 Brandon Edgren
 */
#include "stdafx.h"
#include "main_menu.h"
#include "media.h"

const GLfloat MainMenu::button_width  = 86.0f;
const GLfloat MainMenu::button_height = 43.0f;

MainMenu::MainMenu() :
  play(button_width * 0.5 + 10, button_height * 0.5 + 10, button_width, button_height),
  custom(button_width * 0.5 + 10, button_height * 1.5 + 20, button_width, button_height),
  quit(button_width * 0.5 + 10, button_height * 2.5 + 30, button_width, button_height) {
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
}