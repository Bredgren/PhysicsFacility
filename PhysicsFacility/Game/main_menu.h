/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_MAINMENU_H_
#define PHYSICSFACILICTYGAME_MAINMENU_H_

#include <glm.hpp>

#include <GL/glew.h>
#include "game_state.h"
#include <Shaders/shader.h>

class MainMenu {
 public:
   MainMenu();
   ~MainMenu();

   bool Init(Shader *shader);

   // Updates the state of the buttons. Returns which game state to change
   // to, this will stay kMainMenu until the user pushes a button.
   //GameState::State Step();

   // Updates the state of the buttons. Returns which game state to change
   // to, which will be kMainMenu if the user does not push a button.
   GameState::State ProcessMouse(bool left_button, float display_x, 
                                                   float display_y);

   void Draw();

 private:
   struct Button {
     GLfloat x, y;
     bool selected;
   };

   GLuint button_background_vertex_buffer_;
   Shader *shader_;

   Button b1;
   Button b2;

   void InitializeVertexBuffers();
   void DrawButtonBackground();

   static const GLfloat button_width;
   static const GLfloat button_height;
};

#endif  // PHYSICSFACILICTYGAME_MAINMENU_H_