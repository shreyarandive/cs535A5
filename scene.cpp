#include "scene.h"
#include "v3.h"
#include "m33.h"
#include "ppc.h"
#include "cubemap.h"
#include <sstream>
#include <fstream>

Scene *scene;

using namespace std;

#include <iostream>

string FileNumberToString(int integer_number)
{
	stringstream string_number;
	string_number << integer_number;

	return string_number.str();
}

Scene::Scene() {

	string filename;
	int filenumber = 1;

	gui = new GUI();
	gui->show();

	L = V3(0.0f, 0.0f, 0.0f);
	specc = 180.0f;

	int u0 = 20;
	int v0 = 20;
	int sci = 2;
	int w = 640;
	int h = 480;

	fb = new FrameBuffer(u0, v0, w, h, 0);
	fb->label("First person");
	fb->show();
	
	fb3 = new FrameBuffer(u0, v0, w, h, 1);
	fb3->label("Third person");
	fb3->position(u0 + fb->w + 20, v0);
	//fb3->show();

	leftFB = new FrameBuffer(u0, v0, 512, 512, 1);
	rightFB = new FrameBuffer(u0, v0, 512, 512, 1);
	upFB = new FrameBuffer(u0, v0, 512, 512, 1);
	downFB = new FrameBuffer(u0, v0, 512, 512, 1);
	frontFB = new FrameBuffer(u0, v0, 512, 512, 1);
	backFB = new FrameBuffer(u0, v0, 512, 512, 1);

	cubemap = new Cubemap(0);
	
	cubemap->BackSide(backFB);
	cubemap->DownSide(downFB);
	cubemap->FrontSide(frontFB);
	cubemap->UpSide(upFB);
	cubemap->RightSide(rightFB);
	cubemap->LeftSide(leftFB);
	V3(0.0f, 0.0f, 0.0f);

	gui->uiw->position(u0, v0 + fb->h + 20);

	float hfov = 90.0f;
	ppc = new PPC(fb->w, fb->h, 90.0f);
	ppc3 = new PPC(fb3->w, fb3->h, 90.0f);

	front = new PPC(frontFB->w, frontFB->h, hfov);
	back = new PPC(backFB->w, backFB->h, hfov);
	
	up = new PPC(upFB->w, upFB->h, hfov);
	down = new PPC(downFB->w, downFB->h, hfov);
	
	left = new PPC(leftFB->w, leftFB->h, hfov);
	right = new PPC(rightFB->w, rightFB->h, hfov);
	
	tmsN = 12;
	tms = new TM[tmsN];
	tms[0].id = 0;
	tms[0].SetToBox(V3(0.0f, 0.0f, -100.0f), V3(30.0f, 30.0f, 30.0f), 
		V3(1.0f, 0.5f, 0.0f));
	tms[0].enabled = 0;

	tms[1].LoadBin("geometry/teapot1K.bin");
	tms[1].id = 1;
	tms[1].enabled = 1;
	
	ppc->C = tms[1].GetCenterOfMass() + V3(0.0f, 0.0f, 100.0f);
	L = ppc->C;
	
	ppc->PositionAndOrient(ppc->C, tms[1].GetCenterOfMass(), V3(0.0f, 1.0f, 0.0f));
	ppc3->PositionAndOrient(ppc->C + V3(50.0f, 100.0f, 50.0f), tms[1].GetCenterOfMass(), V3(0.0f, 1.0f, 0.0f));
	
	front->C = V3(0.0f,0.0f,0.0f);
	front->lookAtPoint = V3(0.0f,0.0f, -1.0f);
	front->PositionAndOrient(front->C, front->lookAtPoint, V3(0.0f, 1.0f, 0.0f));

	back->C = V3(0.0f, 0.0f, 0.0f);
	back->lookAtPoint = V3(0.0f, 0.0f, 1.0f);
	back->PositionAndOrient(back->C, back->lookAtPoint, V3(0.0f, 1.0f, 0.0f));
	
	down->C = V3(0.0f, 0.0f, 0.0f);
	down->lookAtPoint = V3(0.0f, -1.0f, 0.0f);
	down->PositionAndOrient(down->C, down->lookAtPoint, V3(0.0f, 0.0f, -1.0f));
	
	up->C = V3(0.0f, 0.0f, 0.0f);
	up->lookAtPoint = V3(0.0f, 1.0f, 0.0f);
	up->PositionAndOrient(up->C, up->lookAtPoint, V3(0.0f, 0.0f, 1.0f));

	left->C = V3(0.0f, 0.0f, 0.0f);
	left->lookAtPoint = V3(-1.0f, 0.0f, 0.0f);
	left->PositionAndOrient(left->C, left->lookAtPoint, V3(0.0f, 1.0f, 0.0f));
	
	right->C = V3(0.0f, 0.0f, 0.0f);
	right->lookAtPoint = V3(1.0f, 0.0f, 0.0f);
	right->PositionAndOrient(right->C, right->lookAtPoint, V3(0.0f, 1.0f, 0.0f));

	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

}

void Scene::Render1 (FrameBuffer *currfb, PPC *currppc) 
{
	for (int i = 0; i < currfb->w ; i++) {
		for (int j = 0; j < currfb->h; j++) 
		{
	
			V3 currPix(.5f + (float)i, .5f + (float)j, 1.0f);
			V3 threeDPoint = currppc->Unproject(currPix);

			V3 projectedPoint;

			 if (front->Project(threeDPoint, projectedPoint))
			{
					
				 if (projectedPoint[0] >= 0 && projectedPoint[0] <= frontFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				 {
					 currfb->SetGuarded(i, j, frontFB->Get(projectedPoint[0], projectedPoint[1]));
				 }
			}

			if (left->Project(threeDPoint, projectedPoint))
			{
				
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= leftFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				{
					currfb->SetGuarded(i, j, leftFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (back->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= leftFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				{
					currfb->SetGuarded(i, j, backFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (right->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= rightFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				{
					currfb->SetGuarded(i, j, rightFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (down->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= leftFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				{
					currfb->SetGuarded(i, j, downFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}

			if (up->Project(threeDPoint, projectedPoint))
			{
				if (projectedPoint[0] >= 0 && projectedPoint[0] <= leftFB->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontFB->h)
				{
					currfb->SetGuarded(i, j, upFB->Get(projectedPoint[0], projectedPoint[1]));
				}
			}
		}
	}

	currfb->redraw();
}

void Scene::ShadowMapSetup() {


	int smw = 512;
	smppc = new PPC(smw, smw, 55.0f);
	smppc->PositionAndOrient(L, tms[1].GetCenterOfMass(), V3(0.0f, 1.0f, 0.0f));
	FrameBuffer *tmpsmfb = new FrameBuffer(100, 100, smw, smw, 2);
	Render(tmpsmfb, smppc);
	tmpsmfb->label("Shadow Map");

	smfb = tmpsmfb;

}

void Scene::DBG() {
	{
		Render(fb, ppc);
		Render1(fb, ppc);
	}
	{
		V3 L0 = L;
		V3 L1 = L + V3(50.0f, -20.0f, -30.0f);

		ppc->LoadFromTextFile("view.txt");
		int fsN = 30;
		for (int fi = 0; fi < fsN; fi++) {
			L = L0 + (L1 - L0)*(float)fi / (float) fsN;
			RenderAll();
			ShadowMapSetup();
			RenderAll();
			Fl::check();
		}
		L = L0;
		return;

	}

	{
		float s0 = 10000.0f;
		float s1 = 10.0f;
		for (int fi = 0; fi < 100; fi++) {
			specc = s0 + (s1 - s0)*(float)fi / 99.0f;
			RenderAll();
			Fl::check();
		}
		return;

	}

	{
		V3 L0 = tms[1].GetCenterOfMass() + V3(0.0f, 0.0f, 100.0f);
		V3 L1 = tms[1].GetCenterOfMass() + V3(0.0f, 100.0f, 0.0f);
		for (int fi = 0; fi < 100; fi++) {
			L = L0 + (L1 - L0)*(float)fi / 99.0f;
			RenderAll();
			Fl::check();
		}
		return;

	}

	{

		float len = 10.0f;
		tms[1].VisualizeNormals(ppc, fb, len);
		fb->redraw();
		return;

	}

	{

		fb->Clear(0xFFFFFFFF, 0.0f);
		fb->Draw3DPoint(ppc->C+V3(0.0f, 0.0f, -100.0f), V3(0.0f, 0.0f, 1.0f),
			11.2f, ppc);
		fb->redraw();
		return;

	}

	{

		V3 a(1.0f, 2.0f, 0.25f);
		a = a.UnitVector();
		V3 C = tms[1].GetCenterOfMass();
		for (int i = 0; i < 360; i++) {
			tms[1].RotateAboutAxis(C, a, 1.0f);
			Render(fb, ppc);
			Fl::check();
		}
		return;

	}


	{

		PPC ppc0 = *ppc;
		V3 O = tms[0].GetCenterOfMass();
		V3 newC = ppc->C + V3(50.0f, 40.0f, 30.0f);
		ppc->PositionAndOrient(newC, O, V3(0.0f, 1.0f, 0.0f));
		PPC ppc1 = *ppc;
		int framesN = 300;
		for (int fi = 0; fi < framesN; fi++) {
			float fracf = (float)fi / (float)(framesN - 1);
			ppc->SetInterpolated(&ppc0, &ppc1, fracf);
			Render(fb, ppc);
			Fl::check();
		}
		*ppc = ppc0;
		return;

	}

	{

		float hfov = 55.0f;
		PPC ppc(fb->w, fb->h, hfov);

		V3 P(0.0f, 0.0f, -100.0f);
		V3 projP;
		if (ppc.Project(P, projP)) {
			cerr << projP << endl;
			fb->DrawCircle((int) projP[0], (int) projP[1], 5.0f, 0xFF00FF00);
			fb->redraw();
		}
		else {
			cerr << "point behind head" << endl;
		}


		return;

	}

	{

		M33 m;
		m[0] = V3(1.0f, -3.0f, 7.0f);
		m[1] = V3(2.0f, 10.0f, 4.3f);
		m[2] = V3(-8.0f, -50.0f, 1.3f);

		M33 m1 = m.Inverted();
		cerr << m1*m << endl << m*m1 << endl;
		return;


	}


	{
		V3 p0(23.5f, 100.1f, 0.0f);
		V3 p1 = p0 + V3(300.0f, 0.0f, 0.0f);
		V3 p2(23.5f, 300.1f, 0.0f);
		V3 p3 = p2 + V3(300.0f, 0.0f, 0.0f);
		int stepsN = 1000;
		for (int i = 0; i < stepsN; i++) {
			float frac = (float)i / (float)stepsN;
			V3 p01 = p0 + (p1 - p0)*frac;
			V3 p32 = p3 + (p2 - p3)*frac;
			V3 p02 = p0 + (p2 - p0)*frac;
			V3 p31 = p3 + (p1 - p3)*frac;
			fb->SetBGR(0xFFFFFFFF);
			V3 c1(0.0f, 1.0f, 0.0f);
			V3 c0(1.0f, 0.0f, 0.0f);
			fb->Draw2DSegment(p01, p32, c0, c0);
			fb->Draw2DSegment(p02, p31, c1, c1);
			fb->redraw();
			Fl::check();
		}
		return;

	}


	{

		M33 m;
		m[0] = V3(1.0f, 0.0f, 0.0f);
		m[1] = V3(0.0f, 1.0f, 0.0f);
		m[2] = V3(0.0f, 0.0f, 1.0f);
		cerr << m << endl;
		V3 v(2.0f, 10.0f, -1.0f);
		cerr << m*v << endl;
		return;

	}

	{
		int u0 = 100;
		int v0 = 200;
		int u1 = 500;
		int v1 = 400;
		float r = 34.3f;
		int stepsN = 100;
		unsigned int color = 0xFF00FFFF;
		for (int stepi = 0; stepi < stepsN; stepi++) {
			int curru = u0 + (u1 - u0)*stepi / stepsN;
			int currv = v0 + (v1 - v0)*stepi / stepsN;
			fb->SetBGR(0xFFFFFFFF);
			fb->DrawCircle(curru, currv, r, color);
			fb->redraw();
			Fl::check();
		}
		return;
	}

	{
		V3 v0(4.0f, 3.0f, 0.0f);
		V3 v1(5.0f, 2.0f, 1.0f);
		cerr << v0.Length() << endl;
		return;
		cerr << v0 << endl << v1 << endl << v0-v1 << endl;
		return;
		v0[0] = 3.0f;
		cerr << "v0[0]= " << v0[0] << endl;
		return;
	}

	{
		int u0 = 20;
		int v0 = 40;
		int u1 = 400;
		int v1 = 200;
		unsigned int color = 0xFFFF0000;
		fb->Draw2DRectangle(u0, v0, u1, v1, color);
	}

	fb->redraw();
	return;

	for (int u = 0; u < fb->w; u++) {
		fb->Set(u, fb->h / 2, 0xFF000000);
	}

	fb->redraw();

}


void Scene::NewButton() {
	cerr << "INFO: pressed New Button" << endl;
	ppc->SaveToTextFile("view.txt");

	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
}

void Scene::Up1() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[1] = 0.0f; move[0] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, 1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, 1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, 1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, 1.0f);

	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

	return; 

}
void Scene::Down1() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[1] = 0.0f; move[0] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, -1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, -1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, -1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, -1.0f);
	
	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

	return;

}


void Scene::Up() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[1] = 0.0f; move[2] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, -1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, -1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, -1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, -1.0f);
	
	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

	return;

}
void Scene::Down() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[1] = 0.0f; move[2] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, 1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, 1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, 1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, 1.0f);
	
	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

	return;

}

void Scene::Left() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[0] = 0.0f; move[2] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, 1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, 1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, 1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, 1.0f);
	
	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;

	return;
}

void Scene::Right() {

	V3 move = tms[1].GetCenterOfMass();
	move = move.UnitVector();
	move[0] = 0.0f; move[2] = 0.0f;
	ppc->C = ppc->C.RotateDirectionAboutDirection(move, -1.0f);
	ppc->a = ppc->a.RotateDirectionAboutDirection(move, -1.0f);
	ppc->b = ppc->b.RotateDirectionAboutDirection(move, -1.0f);
	ppc->c = ppc->c.RotateDirectionAboutDirection(move, -1.0f);
	
	filename = "sprite" + FileNumberToString(filenumber) + ".tif";
	unsigned int bgr = 0xff000000;
	fb->Clear(bgr, 0.0f);
	Render1(fb, ppc);
	Render(fb, ppc);
	//fb->SaveAsTiff(filename.c_str());
	filenumber++;
	return;
}

void Scene::RenderAll() {

	
	Render(fb, ppc);
	Render1(fb, ppc);

	Render(fb3, ppc3);

}

void Scene::Render(FrameBuffer *currfb, PPC *currppc) {

	//unsigned int bgr = 0x00000000;
	//currfb->Clear(bgr, 0.0f);


	for (int tmi = 0; tmi < tmsN; tmi++) {
		if (currfb->id == 1) {
			continue;
		}
		if (!tms[tmi].enabled)
			continue;
		tms[tmi].RenderFilled(currppc, currfb, frontFB, backFB, leftFB, rightFB, upFB, downFB, front, back, left, right, up, down);
	}

	if (currfb->id == 1) {
		float visz = 40.0f;
		ppc->Visualize(visz, currppc, currfb);
		fb->VisualizeImagePoints(visz, ppc, ppc3, fb3);
		fb->Visualize3DPoints(ppc, ppc3, fb3);
	}
	currfb->Draw3DSegment(L, L + V3(0.0f, 5.0f, 0.0f), V3(1.0f, 1.0f, 0.0f), V3(1.0f, 1.0f, 0.0f), currppc);
	currfb->Draw3DSegment(L, L + V3(5.0f, 0.0f, 0.0f), V3(1.0f, 1.0f, 0.0f), V3(1.0f, 1.0f, 0.0f), currppc);
	currfb->Draw3DSegment(L, L + V3(0.0f, 0.0f, 5.0f), V3(1.0f, 1.0f, 0.0f), V3(1.0f, 1.0f, 0.0f), currppc);
	currfb->redraw();
}
