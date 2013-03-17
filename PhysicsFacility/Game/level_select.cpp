/*
 * Copyright 2013 Brandon Edgren
 */

#include "stdafx.h"
#include "level_select.h"
#include "media.h"

const GLfloat LevelSelect::nav_button_width  = 86.0f;
const GLfloat LevelSelect::nav_button_height = 43.0f;

const GLfloat LevelSelect::level_button_width  = 86.0f;
const GLfloat LevelSelect::level_button_height = 86.0f;

LevelSelect::LevelSelect() :
  back(nav_button_width * 0.5 + 100, 768 - nav_button_height * 0.5 - 10, 
       nav_button_width, nav_button_height), level(0) {
  int padding = 100;
  int columns = (1024 - padding * 2) / level_button_width;
  int rows = (768 - padding * 2) / level_button_width;
  NUM_LEVELS = rows * columns;
  for (int i = 0; i < rows; ++i)
    for (int j = 0; j < columns; ++j)
      levels.push_back(new Button(padding + level_button_width  * (j + 0.5),
                                  padding + level_button_height * (i + 0.5),
                                  level_button_width, level_button_height));
}

LevelSelect::~LevelSelect() {
}

bool LevelSelect::Init(Shader *shader) {
  shader_ = shader;

  progress = 20;

  return true;
}

GameState::State LevelSelect::ProcessMouse(bool left_button, 
                                        GLfloat display_x, 
                                        GLfloat display_y) {
  back.ProcessMouse(display_x, display_y);
  for (int i = 0; i < progress; ++i)
    levels[i]->ProcessMouse(display_x, display_y);

  if (left_button) {
    if (back.isSelected())
      return GameState::kMainMenu;
    for (int i = 0; i < NUM_LEVELS; ++i) {
      if (levels[i]->isSelected()) {
        level = i;
        return GameState::kGame;
      }
    }
  }

  return GameState::kLevelSelect;
}

void LevelSelect::Draw() {
  media.DrawImage(media.kBackButton, back.getX(), back.getY(),
                  nav_button_width, nav_button_height,
                  back.isSelected() ? 10.0f : 0.0f);
  
  for (int i = 0; i < NUM_LEVELS; ++i) {
    GLfloat angle = levels[i]->isSelected() ? 10.0f : 0.0f;
    Media::Images type = i < progress ? media.kLevelButtonUnlock :
                                        media.kLevelButtonLock;
    
    media.DrawImage(type, levels[i]->getX(), levels[i]->getY(),
                    level_button_width, level_button_height, angle, i);
  }
}