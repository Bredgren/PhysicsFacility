/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYGAME_GAMESTATE_H_
#define PHYSICSFACILICTYGAME_GAMESTATE_H_

struct GameState {
 public:
  enum State {
    kMainMenu,
    kGame,
    kLevelSelect,
    kCustomLevelSelect,
    kEditor,
    kQuit,
  };
  State current_state;
};

#endif  // PHYSICSFACILICTYGAME_GAMESTATE_H_