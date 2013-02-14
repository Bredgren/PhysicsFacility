
#include "physfacengine.h"

PFEngine::PFEngine(string level_folder) : 
    level_folder_(level_folder),
    current_level_(""),
    time_step_(1.0f / 60.0f),
    init_(false),
    width_(1024),
    height_(768) {
}

PFEngine::~PFEngine() {
  if (init_) {
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
  }
}

bool PFEngine::init() {
  // Initialize GLEW
	glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}

  // Setup OpenGL for 2D display
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glOrtho (0, width_, height_, 0, 0, 1);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
  glDisable(GL_DEPTH_TEST);
  glClearColor(1.0f, 1.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

  //programID = LoadShaders( "transform.glvs", "color.glfs" );
  if(!shader_.loadProgram()) {
		fprintf(stderr, "Unable to load shader!\n");
		return false;
	}

	//Bind basic shader program
	shader_.bind();

  //Initialize projection
	shader_.setProjection(glm::ortho<GLfloat>(0, width_, height_, 0, 0, 1));
	shader_.updateProjection();

	//Initialize modelview
	shader_.setModelView(glm::mat4());
	shader_.updateModelView();

  static const GLfloat g_vertex_buffer_data[] = { 
		 0.0f,  0.0f,
		 100.0f, 50.0f,
		 50.0f,  100.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  init_ = true;
  return true;
}

bool PFEngine::LoadLevel(string level_file) {
  current_level_ = level_file;
  return true;
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

  glClear(GL_COLOR_BUFFER_BIT);

  shader_.setColor(0.0f, 0.0f, 1.0f);

  //glUniform3f(1, 1.0f, 0.0f, 0.0f);
  shader_.setModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(500, 500, 0.0f)));
	shader_.updateModelView();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
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