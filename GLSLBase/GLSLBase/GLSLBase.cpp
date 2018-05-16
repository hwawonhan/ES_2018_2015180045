/*
Copyright 2018 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer *g_Renderer = NULL;
float ex, ey;
float gTime = 0.0f;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//g_Renderer->filAll(1, 1, 1, 0.01);

	float points[] = { 0.5, 0.5, 6, -0.5, 0.5, 8, 0.5, -0.5, 5, -0.5, -0.5, 7 };
	//g_Renderer->WaveEffect(points, gTime);
	//g_Renderer->drawParticleTrail(0, 0, 0, 1, gTime);
	//g_Renderer->Rader(points, gTime);
	//g_Renderer->drawSmile();
	//g_Renderer->Lecture8(gTime);
	//g_Renderer->textureAnimation();
	//g_Renderer->Prectice(gTime);
	//g_Renderer->drawBMP();
	g_Renderer->drawBrick();
	gTime += 0.0005f;
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	
	ex = -(y / 500.0f - 0.5f) * 2.0f;
	ey = -(-x + 250) / 250.0f;
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("GLSL KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

