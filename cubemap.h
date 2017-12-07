#pragma once
#include "ppc.h"
#include "framebuffer.h"
#include "tm.h"

class Cubemap {
public:
	PPC *left, *right, *up, *down, *front, *back;
	FrameBuffer *leftFB, *rightFB, *upFB, *downFB, *frontFB, *backFB;
	FrameBuffer *cube;
	int factor, pixelNumber, pixelNumberFace;
	TM *tms;
	int tmsN;
	Cubemap(int flag);
	void LeftSide(FrameBuffer *leftFB);
	void FrontSide(FrameBuffer *frontFB);
	void BackSide(FrameBuffer *backFB);
	void DownSide(FrameBuffer *downFB);
	void UpSide(FrameBuffer *upFB);
	void RightSide(FrameBuffer *rightFB);
	
	void CreateCubeMap(FrameBuffer *fb, PPC *ppc);
};

extern Cubemap *cubemap;