#include "MyApp.h"
#include "GLUtils.hpp"

#include <GL/GLU.h>
#include <math.h>

#include "ObjParser_OGL3.h"

CMyApp::CMyApp(void)
{
	m_textureID = 0;
}


CMyApp::~CMyApp(void)
{
}


GLuint CMyApp::GenTexture()
{
	unsigned char tex[256][256][3];

	for (int i = 0; i < 256; ++i)
		for (int j = 0; j < 256; ++j)
		{
			tex[i][j][0] = rand() % 256;
			tex[i][j][1] = rand() % 256;
			tex[i][j][2] = rand() % 256;
		}

	GLuint tmpID;

	glGenTextures(1, &tmpID);
	glBindTexture(GL_TEXTURE_2D, tmpID);
	gluBuild2DMipmaps(GL_TEXTURE_2D,
		GL_RGB8, 256, 256,			// define storage on the GPU: RGB, 8bits per channel, 256x256 texture
		GL_RGB, GL_UNSIGNED_BYTE,	// define storate in RAM: RGB layout, unsigned bytes for each channel
		tex);						//						  and source pointer
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// bilinear filter on min and mag
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return tmpID;
}





void CMyApp::add_triangle(
	const glm::vec3& P1,
	const glm::vec3& P2,
	const glm::vec3& P3,
	gVertexBuffer& buffer) {

	buffer.AddData(0, P1.x, P1.y, P1.z); // P1
	buffer.AddData(0, P2.x, P2.y, P2.z); // P2
	buffer.AddData(0, P3.x, P3.y, P3.z); // P3

	glm::vec3 V1 = P2 - P1; //P2-P1
	glm::vec3 V2 = P3 - P1; //P3-P1
	glm::vec3 normal = glm::normalize(glm::cross(V1, V2));

	//normals
	buffer.AddData(1, normal.x, normal.y, normal.z);
	buffer.AddData(1, normal.x, normal.y, normal.z);
	buffer.AddData(1, normal.x, normal.y, normal.z);

	//texture coordinates
	buffer.AddData(2, 0, 0);
	buffer.AddData(2, 0, 0);
	buffer.AddData(2, 0, 0);
}


void CMyApp::gen_prism_offsets(float length, float height, float  width, float offSetX, float offSetY, float offSetZ, gVertexBuffer& buffer) {
	float frontX = length / 2 + offSetX; 
	float rearX = -length / 2 + offSetX; 
	float topY = height / 2 + offSetY;
	float bottomY = -height / 2 + offSetY;  
	float leftZ = -width / 2 + offSetZ; 
	float rightZ = width / 2 + offSetZ;

	//top 
	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(rearX, topY, leftZ),
		buffer
	);

	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(rearX, topY, rightZ),
		buffer
	);

	//bottom 
	add_triangle(
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);

	add_triangle(
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, leftZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);

	//front
	add_triangle(
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);


	add_triangle(
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);


	//rear
	add_triangle(
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(rearX, topY, rightZ),
		buffer
	);


	add_triangle(
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(rearX, topY, rightZ),
		glm::vec3(rearX, topY, leftZ),
		buffer
	);

	// right side

	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, topY, rightZ),
		glm::vec3(rearX, bottomY, rightZ),
		buffer
	);


	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);

	// left side

	add_triangle(
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);


	add_triangle(
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		glm::vec3(rearX, bottomY, leftZ),
		buffer
	);
}



void CMyApp::gen_prism(float length, float height, float  width, gVertexBuffer& buffer) {


	float frontX = length / 2;  // 0.75
	float rearX = -length / 2;  // -0.75
	float topY = height / 2;	// 0.25
	float bottomY = - height / 2; // -0.25
	float leftZ = -width / 2; // -0.5f
	float rightZ = width / 2;  // 0.5f


	//top 
	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(rearX, topY, leftZ),
		buffer
	);

	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(rearX, topY, rightZ),
		buffer
	); 

	//bottom 
	add_triangle(
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);

	add_triangle(
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, leftZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);

	//front
	add_triangle(
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);


	add_triangle(
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);


	//rear
	add_triangle(
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(rearX, topY, rightZ),
		buffer
	);

	 
	add_triangle(
		glm::vec3(rearX, bottomY, leftZ),
		glm::vec3(rearX, topY, rightZ),
		glm::vec3(rearX, topY, leftZ),
		buffer
	);

	// right side

	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, topY, rightZ),
		glm::vec3(rearX, bottomY, rightZ),
		buffer
	);


	add_triangle(
		glm::vec3(frontX, topY, rightZ),
		glm::vec3(rearX, bottomY, rightZ),
		glm::vec3(frontX, bottomY, rightZ),
		buffer
	);

	// left side

	add_triangle(
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(frontX, topY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		buffer
	);


	add_triangle(
		glm::vec3(rearX, topY, leftZ),
		glm::vec3(frontX, bottomY, leftZ),
		glm::vec3(rearX, bottomY, leftZ),
		buffer
	);
}

bool CMyApp::Init()
{
	// background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	// set cullface and z-buffer ON, cull backfaces
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	//
	// create the geometry
	//



	 /// 40 by 40 grid

	m_vb.AddAttribute(0, 3); //positions
	m_vb.AddAttribute(1, 3); //normals 
	m_vb.AddAttribute(2, 2); // tex coords

	//positions


	// grid 
	// id , x, y, z
	int side = 40;
	float unit = 0.2f;
	float startX = -4.0f;
	float startZ = -4.0f;
	int currInd = 0;
	//int gridVertInd = side*side; // 16 
	int i1, i2, i3, i4;
	int drawInd;
	float texElem = 1.0 / side;

	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {

			//currInd = i * side + j;	 // index we are at
			m_vb.AddData(0, startX + j * unit, 0, startZ + i * unit); // add vertex to grid
			m_vb.AddData(1, 0, 1, 0);  // normal
			m_vb.AddData(2, i* texElem, j * texElem);   // tex coord
			currInd++;
			if (i != side - 1 && j != side - 1) {		// indeces to draw
				i1 = i * side + j;
				i2 = i * side + j+1;
				i3 = (i+1) * side + j+1;
				i4 = (i + 1) * side + j;
				m_vb.AddIndex(i2, i1, i4);
				m_vb.AddIndex(i2, i4, i3);
			}
		}
	}
	m_vb.InitBuffers();


	///*******************//

	// TRAIN
	// prism attributes
	m_train.AddAttribute(0, 3); //positions
	m_train.AddAttribute(1, 3); //normals 
	m_train.AddAttribute(2, 2); // tex coords

	// build lower prism 
	// sides of prism coordinates
	float lengthLow = 1.5f;
	float heightLow = 0.5f;
	float widthLow = 1.0f;

	gen_prism(lengthLow, heightLow, widthLow, m_train); 

	// build top prism 
	float lengthTop = 0.5f;
	float heightTop = 0.25f;
	float widthTop = 1.0f;
	float offsetX = (lengthLow - lengthTop) / 2;
	float offsetY = (heightLow + heightTop) / 2; 
	float offsetZ = 0.0f;

	gen_prism_offsets(lengthTop, heightTop, widthTop, offsetX, offsetY, offsetZ ,  m_train);


	m_train.InitBuffers();




	//
	// load shaders	
	//
	m_program.AttachShader(GL_VERTEX_SHADER, "shader.vert");
	m_program.AttachShader(GL_FRAGMENT_SHADER, "shader.frag");

	m_program.BindAttribLoc(0, "vs_in_pos");
	m_program.BindAttribLoc(1, "vs_in_normal");
	m_program.BindAttribLoc(2, "vs_in_tex0");

	if (!m_program.LinkProgram())
	{
		return false;
	}

	//
	// misc init
	//

	m_camera.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	m_textureID = TextureFromFile("snowytrail.jpg");


	return true;
}

void CMyApp::Clean()
{
	glDeleteTextures(1, &m_textureID);

	m_program.Clean();
}

void CMyApp::Update()
{
	static Uint32 last_time = SDL_GetTicks();
	float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;

	m_camera.Update(delta_time);

	last_time = SDL_GetTicks();
}


void CMyApp::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw square

	m_program.On();

	glm::mat4 matWorld = glm::mat4(1.0f);
	glm::mat4 matWorldIT = glm::transpose(glm::inverse(matWorld));
	glm::mat4 mvp = m_camera.GetViewProj() * matWorld;

	m_program.SetUniform("world", matWorld);
	m_program.SetUniform("worldIT", matWorldIT);
	m_program.SetUniform("MVP", mvp);
	m_program.SetUniform("eye_pos", m_camera.GetEye());

	m_program.SetTexture("texImage", 0, m_textureID);

	// draw with VAO
	 
	m_program.SetUniform("ground_id", 1);
	m_vb.On();
	m_vb.DrawIndexed(GL_TRIANGLES, 0, 9126, 0); //IB
	m_vb.Off();
	m_program.SetUniform("ground_id", -1);
	
	
	
	// draw with VAO
	m_program.SetUniform("train_id", 1);
	m_train.On();
	m_train.Draw(GL_TRIANGLES, 0, 36 * 2);
	m_train.Off();
	m_program.SetUniform("train_id", -1);
	
	





	m_program.Off();

}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardDown(key);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
	m_camera.KeyboardUp(key);
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	m_camera.MouseMove(mouse);
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h);

	m_camera.Resize(_w, _h);
}
