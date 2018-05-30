#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "LoadPng.h"
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
	void Prectice(float time);
	void drawSmile();
	void Lecture8(float time);
	void drawBMP();
	void textureAnimation();
	void drawParticleTrail(float start_x, float start_y, float end_x, float end_y, float time);
	void drawBrick();
	void Lecture9();
	void Lecture10();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void FlagPointSetting();
	void ParticleSettring();
	GLuint CreatePngTexture(char * filePath);

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
	GLuint m_VBOSmileTexture = 0;
	GLuint m_VBO_PosTex = 0;
	GLuint gShaderProgram = 0;
	//lecture6
	GLuint m_VBOPosTex = 0;
	GLuint m_TexCheckerboard;
	//lecture7
	GLuint gTextureID = 0;
	GLuint gTextureID1 = 0;
	GLuint gTextureID2 = 0;
	GLuint gTextureID3 = 0;
	GLuint gTextureID4 = 0;
	GLuint gTextureID5 = 0;
	GLuint VBO_PosTex = 0;

	GLuint VBO_PosTexAnimation = 0;
	GLuint gTextureIDTotal = 0;

	//lecture8
	GLuint m_Texboy = 0;
	GLuint m_Texgirl = 0;
	GLuint m_Texbrick = 0;

	//lecture 9
	GLuint m_Texparticle = 0;
	GLuint m_VBO_DummyMesh = 0;
	int    gDummyVertexCount = 0;

	float time = 0;
	float gTimeStamp = 0;
	int pointCount;
	bool timeflag;

	//lecture 10
	int gParticleVertexCount = 0;
	GLuint VBO_ParticleMesh = 0;
	GLuint gParticleTextureID = 0;


	//shader
	GLuint m_STParticleShader = 0;
	GLuint m_TestShader = 0;
	GLuint m_WaveEffectShader = 0;
	GLuint m_RaderShader = 0;
	GLuint m_FillAllShader = 0;
	GLuint m_TextureShader = 0;
	GLuint m_PrecticeShader = 0;
	GLuint m_SmileShader = 0;
	GLuint m_AnimationTextureShader = 0;
	GLuint m_BMPShader = 0;
	GLuint m_BrickPattonShader = 0;
	GLuint m_Lecture9Shader = 0;
	GLuint m_Lecture10Shader = 0;
};

