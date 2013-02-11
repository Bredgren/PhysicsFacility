/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYENGINE_PHYSFACENGINE_H_
#define PHYSICSFACILICTYENGINE_PHYSFACENGINE_H_

#include <string.h>

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
#include <glew/glew.h>

#include "Actor/actor.h"
#include "Shaders/shader.h"

using std::string;

// This class is resposible for managing all aspects of a single level of the
// game. You should always only need one of these at a time and it can only
// work with one level at a time.
class PFEngine {
 public:
  PFEngine(string level_folder);

	~PFEngine();

  // Given the path of the level relative to the level folder given at
  // construction, this function attempts to load and prepare the level.
  // If this function is called more than once before QutiLevel than whatever
  // level was previously running is quit out of and the new one replaces
  // it imediately. If the level could not be loaded, false is returned.
  bool LoadLevel(string level_file);

  // Unloads the current level, if there is no current level than this does
  // nothing. After calling this no other function will do anything until
  // LoadLevel is successfully called. Quiting the level this way does not
  // save the current state of the level.
  void QuitLevel();

  // If save_state is true then the curren state of the level is saved over the
  // old state.
  void QuitLevel(bool save_state);

  // By providing a path the current state of the level is saved as a new level
  // with the given path. The old level is not modified.
  void QuitLevel(bool save_state, string new_path);

  // Starts the current level over from the beginning.
  void ResetLevel();

  // Simulates the level for one time_step_'s worth of seconds.
  void Step();

  // Draws the current state of the level. (Assumes OpenGL context?)
  // TODO determine if this needs a parameter or just a promise
  void Draw(/*whatever needs to be here*/);
  
  // Returns true when the player has completed the level. Be sure to check
  // and handle this.
  bool IsLevelComplete();
  
  // Sets the given action on the given actor. An example of how this might be
  // used is when the user push W key call this with ActorAction.kMoveForward
  // and when the key is released call with ActorAction.kMoveStop.
  void SetActorAction(int8 actor_id, ActorAction action);

  // A version for handling the special action kArmPosition which involves the
  // mouse position, the coordinates of which should be given as x and y
  // relative the display.
  void SetActorAction(int8 actor_id, ActorAction action,
                      float32 display_x, float32 display_y);

  // Sets the time step for the next call to Step.
  void SetTimeStep(float32 time_step) { time_step_ = time_step; }

 private:
   // The folder that should holds all the levels.
   string level_folder_;

   // Path of the current level relative to the level folder.
   string current_level_;

   // The amount of time in seconds so simulate at each all to Step. The
   // default value is 1/60s.
   float32 time_step_;

   GLuint VertexArrayID;
   GLuint programID;
   static const GLfloat g_vertex_buffer_data[];
   GLuint vertexbuffer;
};

#endif  // PHYSICSFACILICTYENGINE_PHYSFACENGINE_H_