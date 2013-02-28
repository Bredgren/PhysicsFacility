/*
 * Copyright 2013 Brandon Edgren
 */

#ifndef PHYSICSFACILICTYENGINE_SHADER_HPP
#define PHYSICSFACILICTYENGINE_SHADER_HPP

#include <string>
#include <stdio.h>
#include <string>

#include <GL/glew.h>
#include <glm.hpp>

// This class is for managing the shaders. Only one set of shaders is
// used because that is all that this project needs.
class Shader {
	public:
    Shader();
    ~Shader();
    // TODO: capitalize methods
		bool loadProgram();
		void freeProgram();

		bool bind();
		void unbind();

		GLuint getProgramID();
    //GLuint getMVPHandle();

    void enableDataPointers();
    void disableDataPointers();

    void setVertexPointer(GLsizei stride, const GLvoid *data);
    // Sets the color of the shader. Default is black.
    void setColor(GLfloat r, GLfloat g, GLfloat b);

    void setProjection(glm::mat4 matrix);
		void setModelView(glm::mat4 matrix);
    glm::mat4 getModelView();
		void leftMultProjection(glm::mat4 matrix);
		void leftMultModelView(glm::mat4 matrix);
		void updateProjection();
		void updateModelView();


	protected:
		void printProgramLog(GLuint program);
		void printShaderLog(GLuint shader);

    GLuint loadShaderFromFile(const char * vertex_file_path,const char * fragment_file_path);
		GLuint programID_;

    // Locations of shader uniforms
    GLint vertexPosLocation_;
    GLint colorLocation_;

		glm::mat4 projectionMatrix_;
		GLint projectionMatrixLocation_;

		glm::mat4 modelViewMatrix_;
		GLint modelViewMatrixLocation_;
};

#endif  // PHYSICSFACILICTYENGINE_SHADER_HPP
