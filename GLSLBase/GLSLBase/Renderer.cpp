#include "stdafx.h"
#include "Renderer.h"


unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight)
{
	printf("Reading image %s\n", imagepath);
	outWidth = -1;
	outHeight = -1;
	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = NULL;
	fopen_s(&file, imagepath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n");
		return NULL;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1E]) != 0)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	if (*(int*)&(header[0x1C]) != 24)
	{
		printf("Not a correct BMP file\n");
		return NULL;
	}

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	outWidth = *(int*)&(header[0x12]);
	outHeight = *(int*)&(header[0x16]);

	if (imageSize == 0)
		imageSize = outWidth*outHeight * 3;

	if (dataPos == 0)
		dataPos = 54;

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);

	fclose(file);

	return data;
}


Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_STParticleShader = CompileShaders("./Shaders/STParticle.vs", "./Shaders/STParticle.fs");
	m_TestShader = CompileShaders("./Shaders/Test.vs", "./Shaders/Test.fs");
	m_WaveEffectShader = CompileShaders("./Shaders/WaveEffect.vs", "./Shaders/WaveEffect.fs");
	m_RaderShader = CompileShaders("./Shaders/Rader.vs", "./Shaders/Rader.fs");
	m_FillAllShader = CompileShaders("./Shaders/FillAll.vs", "./Shaders/FillAll.fs");
	m_TextureShader = CompileShaders("./Shaders/TexturedRect.vs", "./Shaders/TexturedRect.fs");
	m_PrecticeShader = CompileShaders("./Shaders/Prectice.vs", "./Shaders/Prectice.fs");
	m_SmileShader = CompileShaders("./Shaders/Smile.vs", "./Shaders/Smile.fs");
	gShaderProgram = CompileShaders("./Shaders/Lecture7.vs", "./Shaders/Lecture7.fs");
	m_AnimationTextureShader = CompileShaders("./Shaders/TextureAnimation.vs", "./Shaders/TextureAnimation.fs");
	m_BMPShader = CompileShaders("./Shaders/Textures.vs", "./Shaders/Textures.fs");
	m_BrickPattonShader = CompileShaders("./Shaders/brickPatton.vs", "./Shaders/brickPatton.fs");
	//Create VBOs
	CreateVertexBufferObjects();

	if (m_SolidRectShader > 0 && m_VBOFillRect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{

	float circle[] = {
		-1.0f, -1.0f, 0.f, -1.0f, 1.0f, 0.f, 1.0f, 1.0f, 0.f, //Triangle1
		-1.0f, -1.0f, 0.f,  1.0f, 1.0f, 0.f, 1.0f, -1.0f, 0.f, //Triangle2
	};
	glGenBuffers(1, &m_VBOCircle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOCircle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

	float fillRect[] = {
		-1.0f, -1.0f, 0.f, -1.0f, 1.0f, 0.f, 1.0f, 1.0f, 0.f, //Triangle1
		-1.0f, -1.0f, 0.f,  1.0f, 1.0f, 0.f, 1.0f, -1.0f, 0.f, //Triangle2
	};
	//rect
	glGenBuffers(1, &m_VBOFillRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fillRect), fillRect, GL_STATIC_DRAW);

	float linevertex[] = {
		-0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 1.0f/3.0f,
		0.0f, -0.5f, 0.0f, 2.0f/3.0f,
		-0.5f, 0.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &m_VBOLine);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLine);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linevertex), linevertex, GL_STATIC_DRAW);

	
	float vertices[] 
		=
		{ 0.0f, 0.0f ,0.0f ,1.0f ,0.0f ,0.0f ,1.0f ,1.0f ,0.0f };

	glGenBuffers(1, &m_VBOLecture2);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	float vertices1[]
		=
		{ 0.0f, 0.0f ,0.0f, 1.0f,1.0f ,0.0f ,0.0f ,1.0f, 1.0f ,1.0f ,0.0f ,1.0f };

	glGenBuffers(1, &m_VBOLecture3);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	float verticesize[]
		=
		{ 0.5f, 0.5f, 0.5f };

	glGenBuffers(1, &m_VBOLecture3_Scale);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesize), verticesize, GL_STATIC_DRAW);

	float verticeColor[]
		=
	{ 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f};

	glGenBuffers(1, &m_VBOLecture3_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticeColor), verticeColor, GL_STATIC_DRAW);


	float PositionColor[] = {
		0.0f,0.1f,0.0f, 1.0f,1.0f,1.0f,1.0f,
		-1.0f,-1.0f,0.0f, 1.0f,0.0f,0.0f,1.0f,
		1.0f,-1.0,0.0, 0.0,0.0,1.0f,1.0f,
	};

	glGenBuffers(1, &m_VBOPositionColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositionColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(PositionColor), PositionColor, GL_STATIC_DRAW);


	float CenterPoint[] = {
		-1.0f, 0.0f, 0.0f,
	};

	glGenBuffers(1, &m_VBOCenterPoint);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOCenterPoint);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CenterPoint), CenterPoint, GL_STATIC_DRAW);

	//Lecture5
	pointCount = 200;
	float *Points = new float[(pointCount+1) * 4];
	for (int i = 0; i <= pointCount; ++i)
	{
		Points[i * 4] = ((float)i / pointCount * 2) - 1.0f;
		Points[i * 4 + 1] = 0.0f;
		Points[i * 4 + 2] = 0.0f;
		Points[i * 4 + 3] = (float)rand() / (float)RAND_MAX;
		if ((float)rand()/ (float)RAND_MAX - 0.5 > 0)
			Points[i * 4 + 3] *= -1.0f;
	}

	glGenBuffers(1, &m_VBOLecture5Points);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * pointCount, Points, GL_STATIC_DRAW);

	static const GLulong checkerboard[] =
	{
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
		0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
		0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	glGenTextures(1, &m_TexCheckerboard);
	glBindTexture(GL_TEXTURE_2D, m_TexCheckerboard);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float size = 1;
	float rectPosTex[] = {
		-size, -size, 0, 1, 0, 0,	//x, y, z, w, s, t
		size, -size, 0, 1, 1, 0,
		size, size, 0, 1, 1, 1,

		-size, -size, 0, 1, 0, 0,
		size, size, 0, 1, 1, 1,
		-size, size, 0, 1, 0, 1,
	};
	//rect
	glGenBuffers(1, &m_VBOTextureRect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureRect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectPosTex), rectPosTex, GL_STATIC_DRAW);

	GLulong textureSmile[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};

	glGenTextures(1, &m_VBOSmileTexture);
	glBindTexture(GL_TEXTURE_2D, m_VBOSmileTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	float vertPosTex[30] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &m_VBO_PosTex);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex), vertPosTex, GL_STATIC_DRAW);

	GLulong textureSmile0[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID);
	glBindTexture(GL_TEXTURE_2D, gTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile1[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID1);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile2[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID2);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile3[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID3);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	GLulong textureSmile4[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID4);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLulong textureSmile5[]
		=
	{
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureID5);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmile5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	float vertPosTex8[30] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};



	glGenBuffers(1, &VBO_PosTex);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PosTex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTex8), vertPosTex8, GL_STATIC_DRAW);

	float vertPosTexAnimation[30] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &VBO_PosTexAnimation);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PosTexAnimation);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertPosTexAnimation), vertPosTexAnimation, GL_STATIC_DRAW);

	GLulong textureSmileTotal[]
		=
	{
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,

		0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00,
		0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00,
		0xFFFFFFFF, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFF00FF00, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFF0000FF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0000,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
	};
	glGenTextures(1, &gTextureIDTotal);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 48, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureSmileTotal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned int width, height;
	unsigned char* bmp = loadBMPRaw("./Textures/boy.bmp", width, height);
	glGenTextures(1, &m_Texboy);
	glBindTexture(GL_TEXTURE_2D, m_Texboy);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned char* bmp1 = loadBMPRaw("./Textures/girl.bmp", width, height);
	glGenTextures(2, &m_Texgirl);
	glBindTexture(GL_TEXTURE_2D, m_Texgirl);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unsigned char* bmp3 = loadBMPRaw("./Textures/brick.bmp", width, height);
	glGenTextures(2, &m_Texbrick);
	glBindTexture(GL_TEXTURE_2D, m_Texbrick);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bmp3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_Texparticle = CreatePngTexture("./Textures/particle2.png");
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.\n";

	return ShaderProgram;
}

void Renderer::Test()
{
	float newX, newY;

	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLine);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(attribPosition);
}

void Renderer::Lecture2()
{
	glUseProgram(m_SolidRectShader);

	//vertex3개 인것을 확인하기
	////입력확인단계
	//glEnableVertexAttribArray(0);		//0번쨰에 입력을 받을 수 있는 무엇인가가 있었다.
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture2);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	

	GLint posLocation = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint scaleLocation = glGetAttribLocation(m_SolidRectShader, "a_Scale");
	GLint colorLocation = glGetAttribLocation(m_SolidRectShader, "a_Color");

	GLint scaleUiform = glGetUniformLocation(m_SolidRectShader, "u_Scale");

	//vertex 4개로 변환하기
	glEnableVertexAttribArray(posLocation);
	//glBindBuffer 와 glVertexAttribPointer는 세트처럼활용해야함
	//glBindBuffer 아래에 오는 glVertexAttribPointer를 받아옴
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3);
	glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//size 추가하기
	glEnableVertexAttribArray(scaleLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	//Color 추가하기
	glEnableVertexAttribArray(colorLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glUniform1f(scaleUiform, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::Lecture4()
{
	//삼각형 튕기는 것 
	//glUseProgram(m_SolidRectShader);

	//GLint posLocation = glGetAttribLocation(m_SolidRectShader, "a_Position");
	//GLint scaleLocation = glGetAttribLocation(m_SolidRectShader, "a_Scale");
	//GLint colorLocation = glGetAttribLocation(m_SolidRectShader, "a_Color");
	//GLint scaleUiform = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	//GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");

	//glEnableVertexAttribArray(posLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLine);
	//glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
	//
	////size 추가하기
	//glEnableVertexAttribArray(scaleLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	//glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	////Color 추가하기
	//glEnableVertexAttribArray(colorLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	//glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glUniform1f(scaleUiform, 1.0f);
	//glUniform1f(TimeUiform, time);
	//time += 0.01f;
	//glDrawArrays(GL_LINE_STRIP, 0, 4);
	//glDisableVertexAttribArray(posLocation);


	//원만들기
	//glUseProgram(m_SolidRectShader);

	//GLint posLocation = glGetAttribLocation(m_SolidRectShader, "a_Position");
	//GLint scaleLocation = glGetAttribLocation(m_SolidRectShader, "a_Scale");
	//GLint colorLocation = glGetAttribLocation(m_SolidRectShader, "a_Color");
	//GLint scaleUiform = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	//GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");

	//glEnableVertexAttribArray(posLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOCircle);
	//glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	////size 추가하기
	//glEnableVertexAttribArray(scaleLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	//glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	////Color 추가하기
	//glEnableVertexAttribArray(colorLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	//glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glUniform1f(scaleUiform, 1.0f);
	//glUniform1f(TimeUiform, time);
	//time += 0.01f;
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDisableVertexAttribArray(posLocation);

	//입력 한배열로 하기
	glUseProgram(m_SolidRectShader);

	int positionAttribID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	int colorAttribID = glGetAttribLocation(m_SolidRectShader, "a_Color");

	glEnableVertexAttribArray(positionAttribID);
	glEnableVertexAttribArray(colorAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositionColor);
	glVertexAttribPointer(positionAttribID, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glVertexAttribPointer(colorAttribID, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(positionAttribID);
	glDisableVertexAttribArray(colorAttribID);
}

void Renderer::Lecture5()
{
	//sin 움직이기
	/*glUseProgram(m_SolidRectShader);

	int positionAttribID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(TimeUiform, time);
	time += 0.003f;
	glEnableVertexAttribArray(positionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Points);
	glVertexAttribPointer(positionAttribID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glPointSize(4);
	
	glDrawArrays(GL_LINE_STRIP, 0, pointCount);
	glDisableVertexAttribArray(positionAttribID);*/

	/*glUseProgram(m_SolidRectShader);

	int positionAttribID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(TimeUiform, time);
	time += 0.003f;
	glEnableVertexAttribArray(positionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOCircle);
	glVertexAttribPointer(positionAttribID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(positionAttribID);*/

	glUseProgram(m_STParticleShader);

	int positionAttribID = glGetAttribLocation(m_STParticleShader, "a_Position");
	GLint TimeUniform = glGetUniformLocation(m_STParticleShader, "u_Time");
	GLint RatioUniform = glGetUniformLocation(m_STParticleShader, "u_Ratio");
	GLint WidthUniform = glGetUniformLocation(m_STParticleShader, "u_Width");
	glUniform1f(TimeUniform, time);
	glUniform1f(RatioUniform, 3.0f);
	glUniform1f(WidthUniform, 0.2f);
	/*if (time > 1)
		time = -1;*/
	time += 0.001;
	glEnableVertexAttribArray(positionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Points);
	glVertexAttribPointer(positionAttribID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, pointCount);
	glDisableVertexAttribArray(positionAttribID);
}

void Renderer::FragmentShaderAnimation()
{
	GLint shader = m_TestShader;
	glUseProgram(shader);

	

	GLint TimeUniform = glGetUniformLocation(shader, "u_Time");
	glUniform1f(TimeUniform, time);
	time += 0.001;

	float points[] = { -1, -1, 4, 1, 1, 6, -1, 1, 2, 1, -1, 4 };
	GLint uniformPoint = glGetUniformLocation(shader, "u_Points");
	//glUniform2f(uniformPoint, 0.5, 0);
	glUniform3fv(uniformPoint, 4, points);

	GLint posLocation = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);


}

void Renderer::WaveEffect(float* points, float time) 
{
	GLint shader = m_TestShader;
	glUseProgram(shader);


	GLint TimeUniform = glGetUniformLocation(shader, "u_Time");
	glUniform1f(TimeUniform, time);

	GLint uniformPoint = glGetUniformLocation(shader, "u_Points");
	glUniform3fv(uniformPoint, 4, points);

	GLint posLocation = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Rader(float * points, float time)
{
	GLint shader = m_RaderShader;
	glUseProgram(shader);


	GLint TimeUniform = glGetUniformLocation(shader, "u_Time");
	glUniform1f(TimeUniform, time);

	GLint uniformPoint = glGetUniformLocation(shader, "u_Points");
	glUniform3fv(uniformPoint, 4, points);

	GLint posLocation = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawTexture()
{
	GLuint shader = m_TextureShader;
	glUseProgram(shader);

	GLint uniformSampler = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(uniformSampler, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TexCheckerboard);

	GLint attribPosition = glGetAttribLocation(shader, "a_Position");
	GLint attribTexPos = glGetAttribLocation(shader, "a_TexPos");

	glEnableVertexAttribArray(attribPosition);
	glEnableVertexAttribArray(attribTexPos);

	//GLint uniformTexture = glGetAttribLocation(shader, "");

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureRect);
	glVertexAttribPointer(attribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(attribTexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(GL_FLOAT)*4));

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::filAll(float r, float g, float b, float a)
{
	GLint shader = m_FillAllShader;
	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint uniformColor = glGetUniformLocation(shader, "u_Color");
	glUniform4f(uniformColor, r, g, b, a);

	GLint posLocation = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_BLEND);

}

void Renderer::Prectice(float time)
{
	GLuint shader = m_PrecticeShader;

	glUseProgram(shader);

	GLuint TimeLocation = glGetUniformLocation(shader, "u_Time");
	glUniform1f(TimeLocation, time);

	GLint posLocation = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFillRect);
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawSmile()
{
	GLuint shader = m_SmileShader;
	glUseProgram(shader);

	int uniformTex = glGetUniformLocation(shader, "uTexSampler");
	glUniform1i(uniformTex, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_VBOSmileTexture);

	int attrribPosition = glGetAttribLocation(shader, "Position");
	int attrribTexPos = glGetAttribLocation(shader, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO_PosTex);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::Lecture8(float time)
{
	glUseProgram(gShaderProgram);
	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gTextureID1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gTextureID2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, gTextureID3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, gTextureID4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, gTextureID5);

	int uniformTex = glGetUniformLocation(gShaderProgram, "uTexSampler");
	glUniform1i(uniformTex, (int)time % 6);

	int attrribPosition = glGetAttribLocation(gShaderProgram, "Position");
	int attrribTexPos = glGetAttribLocation(gShaderProgram, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_PosTex);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::drawBMP()
{
	glUseProgram(m_BMPShader);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texboy);

	int uniformTex = glGetUniformLocation(m_BMPShader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_Texgirl);

	int uniformTex1 = glGetUniformLocation(m_BMPShader, "uTexSampler1");
	glUniform1i(uniformTex1, 1);

	GLuint uniformTime = glGetUniformLocation(m_BMPShader, "u_Time");
	glUniform1f(uniformTime, time);
	time += 0.05;
	int attrribPosition = glGetAttribLocation(m_BMPShader, "Position");
	int attrribTexPos = glGetAttribLocation(m_BMPShader, "TexPos");


	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureRect);
	glVertexAttribPointer(attrribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(GL_FLOAT) * 4));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);
}

void Renderer::textureAnimation()
{
	glUseProgram(m_AnimationTextureShader);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTextureIDTotal);

	int uniformTex = glGetUniformLocation(m_AnimationTextureShader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	int uniformTime = glGetUniformLocation(m_AnimationTextureShader, "uTime");
	glUniform1f(uniformTime, gTimeStamp);

	gTimeStamp += 1.f;
	if (gTimeStamp > 5.f)
		gTimeStamp = 0.f;


	int attrribPosition = glGetAttribLocation(m_AnimationTextureShader, "Position");
	int attrribTexPos = glGetAttribLocation(m_AnimationTextureShader, "TexPos");

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_PosTex);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

GLuint Renderer::CreatePngTexture(char * filePath)
{
	GLuint temp;
	glGenTextures(1, &temp);

	//Load Pngs
	// Load file and decode image.
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);

	glBindTexture(GL_TEXTURE_2D, temp);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	return temp;
}


void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::drawParticleTrail(float start_x, float start_y, float end_x, float end_y, float time)
{
	glUseProgram(m_STParticleShader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int positionAttribID = glGetAttribLocation(m_STParticleShader, "a_Position");
	GLint TimeUniform = glGetUniformLocation(m_STParticleShader, "u_Time");
	GLint RatioUniform = glGetUniformLocation(m_STParticleShader, "u_Ratio");
	GLint WidthUniform = glGetUniformLocation(m_STParticleShader, "u_Width");
	GLint StartPointUniform = glGetUniformLocation(m_STParticleShader, "u_startPoint");
	GLint EndPointUniform = glGetUniformLocation(m_STParticleShader, "u_endPoint");
	glUniform1f(TimeUniform, time);
	glUniform1f(RatioUniform, 4.0f);
	glUniform1f(WidthUniform, 0.2f);
	glUniform2f(StartPointUniform, start_x, start_y);
	glUniform2f(EndPointUniform, end_x, end_y);

	GLuint textureUniform = glGetUniformLocation(m_STParticleShader, "u_Texture");
	glUniform1i(textureUniform, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texparticle);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	glEnableVertexAttribArray(positionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Points);
	glVertexAttribPointer(positionAttribID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, pointCount);
	glDisableVertexAttribArray(positionAttribID);
}

void Renderer::drawBrick()
{
	glUseProgram(m_BrickPattonShader);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texbrick);

	int uniformTex = glGetUniformLocation(m_BrickPattonShader, "uTexSampler");
	glUniform1i(uniformTex, 0);

	int attrribPosition = glGetAttribLocation(m_BrickPattonShader, "Position");
	int attrribTexPos = glGetAttribLocation(m_BrickPattonShader, "TexPos");

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTextureRect);
	glVertexAttribPointer(attrribPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(attrribTexPos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid*)(sizeof(GL_FLOAT) * 4));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glEnableVertexAttribArray(attrribPosition);
	glEnableVertexAttribArray(attrribTexPos);
	//glDisable(GL_BLEND);
}
