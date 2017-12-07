#include "cubemap.h"
#include "framebuffer.h"
#include "ppc.h"
#include "tm.h"
#include "scene.h"
Cubemap *cubemap;

using namespace std;

Cubemap::Cubemap(int flag)
{
	int u0 = 20;
	int v0 = 20;
	int w = 512;
	int h = 512;

	cube = new FrameBuffer(u0, v0, 1536, 2048, 0);
	/*if (flag) {
		cube = new FrameBuffer(u0, v0, 3232, 808, 0);
	}*/
	//leftFB->SetBGR(0xffffff);

	int pixelNumber = 0;
	int pixelNumberFace = 0;
	int factor = 0;
	cube->LoadTiff("uffizi_cross.tif");
	//if (flag)
		//cube->LoadTiff("PANO_Mine.tif");
	//cube->show();
}

void Cubemap::BackSide(FrameBuffer *backFB)
{
	factor = 785919 - 512;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			backFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor - 1536;
	}
	//backFB->show();
	backFB->label("Back");
}

void Cubemap::DownSide(FrameBuffer *downFB)
{
	factor = 785919 - 512;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			downFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor + 1536;
	}
	//downFB->show();
	downFB->label("Down");
}

void Cubemap::FrontSide(FrameBuffer *frontFB)
{
	factor = pixelNumber - 512;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			frontFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor + 1536;
	}
	frontFB->label("Front"); 
	//frontFB->show();
}

void Cubemap::UpSide(FrameBuffer *upFB)
{
	factor = 1536 * 1536 + 512;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			upFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor + 1536;
	}
	//upFB->show();
	upFB->label("Up");
}

void Cubemap::LeftSide(FrameBuffer *leftFB)
{
	factor = 1536 * 1024;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			leftFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor + 1536;
	}
	//leftFB->show();
	leftFB->label("Left");
}

void Cubemap::RightSide(FrameBuffer *rightFB)
{
	factor = 1536 * 1024 + 1024;
	pixelNumberFace = 0;

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++)
		{
			pixelNumber = j + factor;
			rightFB->pix[pixelNumberFace] = cube->pix[pixelNumber];
			pixelNumberFace++;
		}
		factor = factor + 1536;
	}
	//rightFB->show();
	rightFB->label("Right");
}
	//scene->Render(scene->fb, scene->ppc);
	//Render(fb3, ppc3);

void Cubemap::CreateCubeMap(FrameBuffer *currfb, PPC *currppc){
	for (int i = 0; i < currfb->w; i++) {
		for (int j = 0; j < currfb->h; j++)
		{

			V3 currPix(.5f + (float)i, .5f + (float)j, 1.0f);
			V3 threeDPoint = currppc->Unproject(currPix);

			V3 projectedPoint;
			
			if (scene->front->Project(threeDPoint, projectedPoint))
			{

				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->frontFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->frontFB->h)
				{
					currfb->SetGuarded(i, j, scene->frontFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (scene->left->Project(threeDPoint, projectedPoint))
			{

				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->leftFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->leftFB->h)
				{
					currfb->SetGuarded(i, j, scene->leftFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (scene->back->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->backFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->backFB->h)
				{
					currfb->SetGuarded(i, j, scene->backFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (scene->right->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->rightFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->rightFB->h)
				{
					currfb->SetGuarded(i, j, scene->rightFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (scene->down->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->downFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->downFB->h)
				{
					currfb->SetGuarded(i, j, scene->downFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (scene->up->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= scene->upFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= scene->upFB->h)
				{
					currfb->SetGuarded(i, j, scene->upFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}
		}
	}
	currfb->redraw();
}
