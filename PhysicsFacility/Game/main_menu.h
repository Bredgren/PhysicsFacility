/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_MAINMENU_H_
#define PHYSICSFACILICTYGAME_MAINMENU_H_

#include <glm.hpp>

#include <GL/glew.h>
#include <Shaders/shader.h>

#include "button.h"
#include "game_state.h"

class MainMenu {
 public:
   MainMenu();
   ~MainMenu();

   bool Init(Shader *shader);

   // Updates the state of the buttons. Returns which game state to change
   // to, which will be kMainMenu if the user does not push a button.
   GameState::State ProcessMouse(bool left_button, GLfloat display_x, 
                                                   GLfloat display_y);

   void Draw();

 private:
   GLuint vertex_buffer_;
   Shader *shader_;

   Button play;
   Button custom;
   Button quit;

   static const GLfloat button_width;
   static const GLfloat button_height;
};

#endif  // PHYSICSFACILICTYGAME_MAINMENU_H_