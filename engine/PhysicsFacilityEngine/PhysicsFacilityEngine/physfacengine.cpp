
#include "physfacengine.h"

PFEngine::PFEngine(string level_folder) : 
    level_folder_(level_folder),
    current_level_(""),
    time_step_(1.0f / 60.0f) {

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

  programID = LoadShaders( "transform.glvs", "color.glfs" );

  static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

PFEngine::~PFEngine() {
  glDeleteBuffers(1, &vertexbuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
}

bool PFEngine::LoadLevel(string level_file) {
  return false;
}

void PFEngine::QuitLevel() {
  QuitLevel(false, current_level_);
}

void PFEngine::QuitLevel(bool save_state) {
  QuitLevel(save_state, current_level_);
}

void PFEngine::QuitLevel(bool save_state, string new_path) {
  if (current_level_ == "") return;

  if (save_state) {

  } else {
    
  }
  current_level_ = "";
  return;
}

void PFEngine::ResetLevel() {
  LoadLevel(current_level_);
}

void PFEngine::Step() {
  if (current_level_ == "") return;
}

void PFEngine::Draw(/*whatever needs to be here*/) {
  if (current_level_ == "") return;

  glClear( GL_COLOR_BUFFER_BIT );

	// Use our shader
	glUseProgram(programID);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
}
  
bool PFEngine::IsLevelComplete() {
  if (current_level_ == "") return false;
  return false;
}
  
void PFEngine::SetActorAction(int8 actor_id, ActorAction action) {
  SetActorAction(actor_id, action, 0, 0);
}

void PFEngine::SetActorAction(int8 actor_id, ActorAction action,
                      float32 display_x, float32 display_y) {
  if (current_level_ == "") return;
}