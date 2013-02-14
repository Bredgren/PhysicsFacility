
#ifndef PHYSICSFACILICTYENGINE_SHADER_HPP
#define PHYSICSFACILICTYENGINE_SHADER_HPP

#include <string>
#include <stdio.h>
#include <string>

#include <GL/glew.h>
#include <glm.hpp>

// Function for loading shaders from files.
//GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

class Shader {
	public:
    Shader();

    ~Shader();

		bool loadProgram();

		void freeProgram();

		bool bind();

		void unbind();

    void setColor(GLfloat r, GLfloat g, GLfloat b);

		GLuint getProgramID();
    GLuint getMVPHandle();

    void setProjection(glm::mat4 matrix);
		void setModelView(glm::mat4 matrix);
		void leftMultProjection(glm::mat4 matrix);
		void leftMultModelView(glm::mat4 matrix);
		void updateProjection();
		void updateModelView();

	protected:
		void printProgramLog(GLuint program);
		void printShaderLog(GLuint shader);

    GLuint loadShaderFromFile(const char * vertex_file_path,const char * fragment_file_path);
		GLuint programID_;

    GLint colorLocation_;

		glm::mat4 projectionMatrix_;
		GLint projectionMatrixLocation_;

		glm::mat4 modelViewMatrix_;
		GLint modelViewMatrixLocation_;
};

#endif  // PHYSICSFACILICTYENGINE_SHADER_HPP
