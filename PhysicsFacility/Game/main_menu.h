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
   // to, this will stay kMainMenu until the user pushes a button.
   //GameState::State Step();

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

   /*void SetupButton(Button button);
   void DrawPlayButton();
   void DrawCustomButton();
   void DrawQuitButton();

   void DrawButtonBackground(Button button);
   void DrawPlayTriangle();
   void DrawCustomHammer();
   void DrawQuitX();*/

   static const GLfloat button_width;
   static const GLfloat button_height;
};

#endif  // PHYSICSFACILICTYGAME_MAINMENU_H_