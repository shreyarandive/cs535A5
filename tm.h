#pragma once

#include "v3.h"
#include "aabb.h"
#include "framebuffer.h"
#include "ppc.h"
#include "m33.h"

class TM {

public:
	V3 *verts, *cols, *tcs, *normals;
	FrameBuffer *tex;
	int vertsN;
	unsigned int *tris;
	int trisN;
	int enabled;
	int id;
	V3 rv;

	TM() : normals(0), tcs(0), tex(0), id (0), verts(0), cols(0), vertsN(0), tris(0), trisN(0), enabled(1) {};
	void SetToBox(V3 O, V3 dims, V3 color);
	void SetToRectangle(V3 O, V3 dims, V3 color);
	void Allocate(int vsN, int tsN);
	void RenderPoints(PPC *ppc, FrameBuffer *fb);
	void RenderWireframe(PPC *ppc, FrameBuffer *fb);
	void RenderFilled(PPC *ppc, FrameBuffer *fb, FrameBuffer *frontfb, FrameBuffer *backfb, FrameBuffer *leftfb, FrameBuffer *rightfb, FrameBuffer *upfb, FrameBuffer *downfb,PPC *front, PPC *back, PPC *left, PPC *right, PPC *up, PPC *down);
	void SetToMyRectangle(V3 a, V3 b, V3 c, V3 d);
	V3 GetCenterOfMass();
	void LoadBin(char *fname);
	void RotateAboutAxis(V3 O, V3 a, float theta);
	M33 ComputeSSIM(V3 *pvs);
	M33 ComputeMSIM(M33 vs, PPC *ppc);
	void VisualizeNormals(PPC *ppc, FrameBuffer *fb, float len);
	AABB ComputeAABB();
	void RenderProjector(PPC *ppc, FrameBuffer *fb, FrameBuffer *cubefb, V3 lightSource, M33 lightSourceMatrix);
	void TranslateVertsZ(float z);
	void TranslateVertsY(float z);
	void TranslateVertsX(float z);
};