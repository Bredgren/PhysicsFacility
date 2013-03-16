/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_LEVELSELECT_H_
#define PHYSICSFACILICTYGAME_LEVELSELECT_H_

#include <glm.hpp>
#include <vector>

#include <GL/glew.h>
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

 private:
   int progress;

   Shader *shader_;

   Button back;

   //static const int NUM_LEVELS = 5;
   int NUM_LEVELS;
   std::vector<Button*> levels;

   static const GLfloat nav_button_width;
   static const GLfloat nav_button_height;

   static const GLfloat level_button_width;
   static const GLfloat level_button_height;
};

#endif  // PHYSICSFACILICTYGAME_LEVELSELECT_H_