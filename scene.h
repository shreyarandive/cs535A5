#pragma once

#include "gui.h"
#include "framebuffer.h"
#include "tm.h"
#include "cubemap.h"

class Scene {
public:

	GUI *gui;
	FrameBuffer *fb, *fb3, *smfb, *texts;
	V3 L;
	float specc;
	TM *tms;
	int tmsN;
	Cubemap *cubemapFB;
	string filename;
	int filenumber = 1;
	FrameBuffer *leftFB, *rightFB, *upFB, *downFB, *frontFB, *backFB;
	PPC *ppc, *ppc3, *smppc;
	PPC *front, *back, *up, *down, *left, *right, *lightSource;
	Scene();
	void DBG();
	void NewButton();
	void Render(FrameBuffer *fb, PPC *ppc);
	void Render1(FrameBuffer *fb, PPC *ppc);
	void RenderAll();
	void ShadowMapSetup();
	void Left();
	void Down();
	void Up();
	void Down1();
	void Up1();
	void Right();
};

extern Scene *scene;