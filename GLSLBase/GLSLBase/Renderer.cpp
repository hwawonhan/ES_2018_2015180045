#include "stdafx.h"
#include "Renderer.h"

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
	
	//Create VBOs
	CreateVertexBufferObjects();

	if (m_SolidRectShader > 0 && m_VBORect > 0)
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

	//rect
	glGenBuffers(1, &m_VBOLecture5Rect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Rect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

	float linevertex[] = {
		-0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f, 1.0f/3.0f,
		0.0f, -0.5f, 0.0f, 2.0f/3.0f,
		-0.5f, 0.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &m_VBOLine);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLine);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linevertex), linevertex, GL_STATIC_DRAW);

	float rect[]
		=
	{
		-0.5, -0.5, 0.f, -0.5, 0.5, 0.f, 0.5, 0.5, 0.f, //Triangle1
		-0.5, -0.5, 0.f,  0.5, 0.5, 0.f, 0.5, -0.5, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

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


	//Lecture5
	pointCount = 100;
	float *Points = new float[(pointCount+1) * 3];
	for (int i = 0; i <= pointCount; ++i)
	{
		Points[i * 3] = -1.0f + (i*0.02);
		Points[i * 3 + 1] = 0.0f;
		Points[i * 3 + 2] = 0.0f;
	}

	glGenBuffers(1, &m_VBOLecture5Points);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture5Points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * pointCount, Points, GL_STATIC_DRAW);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
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
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

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

	//vertex3�� �ΰ��� Ȯ���ϱ�
	////�Է�Ȯ�δܰ�
	//glEnableVertexAttribArray(0);		//0������ �Է��� ���� �� �ִ� �����ΰ��� �־���.
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture2);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	

	GLint posLocation = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint scaleLocation = glGetAttribLocation(m_SolidRectShader, "a_Scale");
	GLint colorLocation = glGetAttribLocation(m_SolidRectShader, "a_Color");

	GLint scaleUiform = glGetUniformLocation(m_SolidRectShader, "u_Scale");

	//vertex 4���� ��ȯ�ϱ�
	glEnableVertexAttribArray(posLocation);
	//glBindBuffer �� glVertexAttribPointer�� ��Ʈó��Ȱ���ؾ���
	//glBindBuffer �Ʒ��� ���� glVertexAttribPointer�� �޾ƿ�
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3);
	glVertexAttribPointer(posLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//size �߰��ϱ�
	glEnableVertexAttribArray(scaleLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	//Color �߰��ϱ�
	glEnableVertexAttribArray(colorLocation);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
	glUniform1f(scaleUiform, 1.0f);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::Lecture4()
{
	//�ﰢ�� ƨ��� �� 
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
	////size �߰��ϱ�
	//glEnableVertexAttribArray(scaleLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	//glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	////Color �߰��ϱ�
	//glEnableVertexAttribArray(colorLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	//glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glUniform1f(scaleUiform, 1.0f);
	//glUniform1f(TimeUiform, time);
	//time += 0.01f;
	//glDrawArrays(GL_LINE_STRIP, 0, 4);
	//glDisableVertexAttribArray(posLocation);


	//�������
	//glUseProgram(m_SolidRectShader);

	//GLint posLocation = glGetAttribLocation(m_SolidRectShader, "a_Position");
	//GLint scaleLocation = glGetAttribLocation(m_SolidRectShader, "a_Scale");
	//GLint colorLocation = glGetAttribLocation(m_SolidRectShader, "a_Color");
	//GLint scaleUiform = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	//GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");

	//glEnableVertexAttribArray(posLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOCircle);
	//glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	////size �߰��ϱ�
	//glEnableVertexAttribArray(scaleLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Scale);
	//glVertexAttribPointer(scaleLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);

	////Color �߰��ϱ�
	//glEnableVertexAttribArray(colorLocation);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOLecture3_Color);
	//glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glUniform1f(scaleUiform, 1.0f);
	//glUniform1f(TimeUiform, time);
	//time += 0.01f;
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDisableVertexAttribArray(posLocation);

	//�Է� �ѹ迭�� �ϱ�
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
	//sin �����̱�
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

	glUseProgram(m_SolidRectShader);

	int positionAttribID = glGetAttribLocation(m_SolidRectShader, "a_Position");
	GLint TimeUiform = glGetUniformLocation(m_SolidRectShader, "u_Time");
	glUniform1f(TimeUiform, time);
	time += 0.003f;
	glEnableVertexAttribArray(positionAttribID);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOCircle);
	glVertexAttribPointer(positionAttribID, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(positionAttribID);
}



void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}