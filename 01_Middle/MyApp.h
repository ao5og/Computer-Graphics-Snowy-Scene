#pragma once

#include <functional>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

#include "gCamera.h"
#include "gShaderProgram.h"
#include "gVertexBuffer.h"
#include "Mesh_OGL3.h"

class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);
protected:
	GLuint GenTexture();

	GLuint m_textureID; 

	void add_triangle(	const glm::vec3 &P1, 
								const glm::vec3 &P2, 
								const glm::vec3 &P3, 
								gVertexBuffer &buffer);

	void gen_prism(float length, float height, float  width, gVertexBuffer& buffer);  // generate prism
	void gen_prism_offsets(float length, float height, float  width, float offSetX, float offSetY, float offSetZ, gVertexBuffer& buffer);  // generate prism

	gCamera			m_camera;
	gShaderProgram	m_program;

	gVertexBuffer	m_vb; // plane
	gVertexBuffer	m_train; // train
	
};

