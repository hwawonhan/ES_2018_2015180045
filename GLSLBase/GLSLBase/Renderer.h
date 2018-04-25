#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void Test();

	void Lecture2();
	void Lecture4();
	void Lecture5();
	void FragmentShaderAnimation();
	void WaveEffect(float* points, float time);
	void Rader(float* points, float time);
	void DrawTexture();
	void filAll(float r, float g, float b, float a);

	void drawParticleTrail(float start_x, float start_y, float end_x, float end_y, float time);
private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);


	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBOLine = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_VBOPositionColor;
	GLuint m_VBOCenterPoint = 0;
	GLuint m_VBOLecture2 = 0;
	GLuint m_VBOLecture3 = 0;
	GLuint m_VBOLecture3_Scale = 0;
	GLuint m_VBOLecture3_Color = 0;
	GLuint m_VBOCircle = 0;
	GLuint m_VBOLecture5Points = 0;
	GLuint m_VBOFillRect = 0;
	GLuint m_VBOTextureRect = 0;

	//lecture6
	GLuint m_VBOPosTex = 0;
	GLuint m_TexCheckerboard;

	float time = 0;
	int pointCount;
	bool timeflag;

	GLuint m_STParticleShader = 0;
	GLuint m_TestShader = 0;
	GLuint m_WaveEffectShader = 0;
	GLuint m_RaderShader = 0;
	GLuint m_FillAllShader = 0;
	GLuint m_TextureShader = 0;
};

