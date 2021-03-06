
#include "physfacengine.h"

PFEngine::PFEngine(string level_folder) : 
    level_folder_(level_folder),
    current_level_(""),
    time_step_(1.0f / 60.0f),
    init_(false),
    width_(1024),
    height_(768) {
      x = 50;
      y = 50;
      angle = 0;
      horiz = 0;
      vert = 0;
}

PFEngine::~PFEngine() {
  if (init_) {
    glDeleteBuffers(1, &vertexbuffer_);
    glDeleteVertexArrays(1, &VertexArrayID);
    init_ = false;
  }
}

bool PFEngine::Init() {
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
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  //glEnable(GL_MULTISAMPLE);

  if(!shader_.loadProgram()) {
		fprintf(stderr, "Unable to load shader!\n");
		return false;
	}

	//Bind basic shader program
	if (!shader_.bind()) {
    fprintf(stderr, "Unable to bind shader!\n");
    return false;
  }

  //Initialize projection
	shader_.setProjection(glm::ortho<GLfloat>(0, width_, height_, 0, 0, 1));
	shader_.updateProjection();

	//Initialize modelview
	shader_.setModelView(glm::mat4());
	shader_.updateModelView();

  static const GLfloat g_vertex_buffer_data[] = { 
		 -1.0f, -1.0f,
		 -1.0f,  1.0f,
		  1.0f,  1.0f,
      1.0f, -1.0f,
      -25.0f, -25.0f,
	    -25.0f,  25.0f,
       25.0f,  25.0f,
       25.0f, -25.0f,
	};

  GLubyte indices[] = {0, 1, 2, 3, 4, 5, 6, 7};

	glGenBuffers(1, &vertexbuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glGenBuffers(1, &IBO_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  shader_.enableDataPointers();
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_);
  shader_.setVertexPointer(0, reinterpret_cast<void*>(0));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_);
  glBindVertexArray(NULL);

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
  angle += 0.01f;
  x += 0.1f * horiz;
  y += 0.1f * vert;
}

void PFEngine::DrawRect(GLfloat x, GLfloat y,
                        GLfloat scale_x, GLfloat scale_y,
                        GLfloat angle) {
  shader_.setModelView(glm::scale(glm::mat4(), glm::vec3(scale_x, scale_y, 0)));
  shader_.leftMultModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_.leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(x, y, 0.0f)));
	shader_.updateModelView();

  glBindVertexArray(VertexArrayID);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);
}

void PFEngine::DrawTriangleFan(GLuint vao, GLsizei count, GLvoid *start,
                               GLfloat x, GLfloat y,
                               GLfloat scale_x, GLfloat scale_y,
                               GLfloat angle) {
  shader_.setModelView(glm::scale(glm::mat4(), glm::vec3(scale_x, scale_y, 0)));
  shader_.leftMultModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_.leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(x, y, 0.0f)));
	shader_.updateModelView();

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLE_FAN, count, GL_UNSIGNED_BYTE, start);
}

void PFEngine::Draw() {
  if (current_level_ == "") return;

  //shader_.setColor(0.0f, 1.0f, 1.0f);

  DrawRect(100, 100, 50, 50, 0);
  shader_.setColor(1.0f, 1.0f, 1.0f);
  DrawRect(100, 100, 25, 25, 0);
  shader_.setColor(0.0f, 0.0f, 0.0f);
  DrawRect(150, 50, 30, 15, 45);

  DrawRect(x, y, 25, 25, angle);

  DrawTriangleFan(VertexArrayID, 4, (void *)4, 300, 300, 1, 1, 0);

  /*shader_.setModelView(glm::rotate<GLfloat>(glm::mat4(), angle, glm::vec3(0,0,1)));
  shader_.leftMultModelView(glm::translate<GLfloat>(glm::mat4(), glm::vec3(x, y, 0.0f)));
	shader_.updateModelView();

  glBindVertexArray(VertexArrayID);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);*/


  //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_);
	//glVertexAttribPointer(
	//	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	//	2,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);

	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // 3 indices starting at 0 -> 1 triangle

	//glDisableVertexAttribArray(0);
}
  
bool PFEngine::IsLevelComplete() {
  if (current_level_ == "") return false;
  return false;
}
  
void PFEngine::SetActorAction(int8 actor_id, ActorAction action) {
  SetActorAction(actor_id, action, 0, 0);
}

void PFEngine::SetActorAction(int8 actor_id, ActorAction action,
                      GLfloat display_x, GLfloat display_y) {
  if (current_level_ == "") return;
  switch (action) {
  case kMoveForward:
      vert = -1;
    break;
  case kMoveBackward:
    vert = 1;
    break;
  case kMoveStop:
    vert = 0;
    break;
  case kTurnLeft:
    horiz = -1;
    break;
  case kTurnRight:
    horiz = 1;
    break;
  case kTurnStop:
    horiz = 0;
    break;
  case kArmPosition: {
    glm::vec2 mouse = glm::vec2(display_x, display_y);
    glm::vec2 box = glm::vec2(x, y);
    glm::vec2 dir = mouse - box;
    size_t length = dir.length();
    dir = glm::normalize(dir);
    x += dir.x * length/10;
    y += dir.y * length/10;
    break;
  }
  default:
    break;
  }
}

Shader *PFEngine::GetShader() {
  return &shader_;
}