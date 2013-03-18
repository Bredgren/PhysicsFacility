/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_LEVELSELECT_H_
#define PHYSICSFACILICTYGAME_LEVELSELECT_H_

#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <glm.hpp>
#include <Shaders/shader.h>

#include "button.h"
#include "game_state.h"

class LevelSelect {
 public:
   LevelSelect();
   ~LevelSelect();

   bool Init(Shader *shader);

   // Updates the state of the buttons. Returns which game state to change
   // to, which will be kMainMenu if the user does not push a button.
   GameState::State ProcessMouse(bool left_button, GLfloat display_x, 
                                                   GLfloat display_y);

   void Draw();

   void IncrementProgress();

 private:
   int progress;
   int level;

   Shader *shader_;

   Button back;

   int NUM_LEVELS;  // 54 (0 - 53)
   std::vector<Button*> levels;

   static const GLfloat nav_button_width;
   static const GLfloat nav_button_height;

   static const GLfloat level_button_width;
   static const GLfloat level_button_height;
};

#endif  // PHYSICSFACILICTYGAME_LEVELSELECT_H_