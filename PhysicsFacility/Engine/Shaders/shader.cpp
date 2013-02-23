
#include "shader.h"
#include <fstream>
#include <vector>

Shader::Shader() {
	programID_ = NULL;
}

Shader::~Shader() {
    freeProgram();
}

void Shader::freeProgram() {
  if (programID_ != NULL)
    glDeleteProgram(programID_);
}

bool Shader::bind() {
	glUseProgram(programID_);

  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    const GLubyte *b = gluErrorString(error);
    printf("Error binding shader! %s\n", b);
    printProgramLog(programID_);
    return false;
  }

	return true;
}

void Shader::unbind() {
  //Use default program
	glUseProgram(NULL);
}

GLuint Shader::getProgramID() {
  return programID_;
}

//GLuint Shader::getMVPHandle() {
//  return glGetUniformLocation(programID_, "MVP");
//}

bool Shader::loadProgram() {
	programID_ = glCreateProgram();
  if (!loadShaderFromFile("../../../Engine/Shaders/transform.glvs",
                          "../../../Engine/Shaders/color.glfs"))
    return false;
  
  //Get variable locations
  vertexPosLocation_ = glGetAttribLocation(programID_, "vertexPos2D");
	if(vertexPosLocation_ == -1) {
		printf("%s is not a valid glsl program variable!\n", "vertexPos2D");
	}

  colorLocation_ = glGetUniformLocation(programID_, "color");
	if(colorLocation_ == -1) {
		printf("%s is not a valid glsl program variable!\n", "color");
	}

	projectionMatrixLocation_ = glGetUniformLocation(programID_, 
                                                   "projectionMatrix");
	if(projectionMatrixLocation_ == -1) {
		printf("%s is not a valid glsl program variable!\n",
           "projectionMatrix");
	}

	modelViewMatrixLocation_ = glGetUniformLocation(programID_, 
                                                  "modelViewMatrix");
	if(modelViewMatrixLocation_ == -1) {
		printf("%s is not a valid glsl program variable!\n",
            "modelViewMatrix" );
	}

	return true;
}

void Shader::enableDataPointers() {
  glEnableVertexAttribArray(vertexPosLocation_);
}

void Shader::disableDataPointers() {
  //glDisableVertexAttribArray(colorLocation_);
  glDisableVertexAttribArray(vertexPosLocation_);
}

void Shader::setVertexPointer(GLsizei stride, const GLvoid *data) {
  glVertexAttribPointer(vertexPosLocation_, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setColor(GLfloat r, GLfloat g, GLfloat b) {
	glUniform3f(colorLocation_, r, g, b);
}

void Shader::setProjection(glm::mat4 matrix) {
	projectionMatrix_ = matrix;
}

void Shader::setModelView(glm::mat4 matrix) {
	modelViewMatrix_ = matrix;
}

void Shader::leftMultProjection(glm::mat4 matrix) {
	projectionMatrix_ = matrix * projectionMatrix_;
}

void Shader::leftMultModelView(glm::mat4 matrix) {
	modelViewMatrix_ = matrix * modelViewMatrix_;
}

void Shader::updateProjection() {
	glUniformMatrix4fv(projectionMatrixLocation_, 1, GL_FALSE, 
                     glm::value_ptr(projectionMatrix_));
}

void Shader::updateModelView() {
	glUniformMatrix4fv(modelViewMatrixLocation_, 1, GL_FALSE, 
                     glm::value_ptr(modelViewMatrix_));
}

GLuint Shader::loadShaderFromFile(const char * vertex_file_path, 
                                  const char * fragment_file_path) {
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, 
                       &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, 
                       &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	//GLuint ProgramID = glCreateProgram();
	glAttachShader(programID_, VertexShaderID);
	glAttachShader(programID_, FragmentShaderID);
	glLinkProgram(programID_);

	// Check the program
	glGetProgramiv(programID_, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID_, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programID_, InfoLogLength, NULL, 
                        &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return true;
}

void Shader::printProgramLog(GLuint program) {
	if (glIsProgram(program)) {
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = new char[maxLength];

		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			printf("%s\n", infoLog);
		}

		delete[] infoLog;
	} else {
		printf("Name %d is not a program\n", program);
	}
}

void Shader::printShaderLog(GLuint shader) {
	if (glIsShader(shader)) {
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		char* infoLog = new char[maxLength];

    glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			printf("%s\n", infoLog);
		}

		delete[] infoLog;
	} else {
		printf("Name %d is not a shader\n", shader);
	}
}