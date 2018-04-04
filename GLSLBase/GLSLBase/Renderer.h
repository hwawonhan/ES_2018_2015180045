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

	GLuint m_VBORect = 0;
	GLuint m_VBOLine = 0;
	GLuint m_SolidRectShader = 0;

	GLuint m_VBOPositionColor;

	GLuint m_VBOLecture2 = 0;
	GLuint m_VBOLecture3 = 0;
	GLuint m_VBOLecture3_Scale = 0;
	GLuint m_VBOLecture3_Color = 0;
	GLuint m_VBOCircle = 0;
	GLuint m_VBOLecture5Points = 0;
	GLuint m_VBOLecture5Rect = 0;

	float time = 0;
	int pointCount;
};

