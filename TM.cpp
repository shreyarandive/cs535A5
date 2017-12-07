#include "tm.h"
#include "aabb.h"
#include "m33.h"
#include "scene.h"
#include <fstream>

void TM::Allocate(int vsN, int tsN) {

	vertsN = vsN;
	verts = new V3[vertsN];
	cols = new V3[vertsN];
	trisN = tsN;
	tris = new unsigned[3*trisN];
	V3 rv;

}

void TM::SetToBox(V3 O, V3 dims, V3 color) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < vertsN/2; vi++) {
		cols[vi] = color;
		cols[vi + vertsN / 2] = color*0.5f;
	}

	int vi = 0;
	verts[vi++] = O + V3(-dims[0] / 2.0f, +dims[1] / 2.0f, +dims[2] / 2.0f);
	verts[vi++] = O + V3(-dims[0] / 2.0f, -dims[1] / 2.0f, +dims[2] / 2.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, -dims[1] / 2.0f, +dims[2] / 2.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, +dims[1] / 2.0f, +dims[2] / 2.0f);

	verts[vi++] = O + V3(-dims[0] / 2.0f, +dims[1] / 2.0f, -dims[2] / 2.0f);
	verts[vi++] = O + V3(-dims[0] / 2.0f, -dims[1] / 2.0f, -dims[2] / 2.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, -dims[1] / 2.0f, -dims[2] / 2.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, +dims[1] / 2.0f, -dims[2] / 2.0f);

	trisN = 0;
	int tri = 0;

	tris[tri * 3 + 0] = 0;
	tris[tri * 3 + 1] = 1;
	tris[tri * 3 + 2] = 2;
	tri++;
	tris[tri * 3 + 0] = 2;
	tris[tri * 3 + 1] = 3;
	tris[tri * 3 + 2] = 0;
	tri++;
	trisN += 2;

	tris[tri * 3 + 0] = 3;
	tris[tri * 3 + 1] = 2;
	tris[tri * 3 + 2] = 6;
	tri++;
	tris[tri * 3 + 0] = 6;
	tris[tri * 3 + 1] = 7;
	tris[tri * 3 + 2] = 3;
	tri++;
	trisN += 2;

	tris[tri * 3 + 0] = 7;
	tris[tri * 3 + 1] = 6;
	tris[tri * 3 + 2] = 5;
	tri++;
	tris[tri * 3 + 0] = 5;
	tris[tri * 3 + 1] = 4;
	tris[tri * 3 + 2] = 7;
	tri++;
	trisN += 2;

	tris[tri * 3 + 0] = 4;
	tris[tri * 3 + 1] = 5;
	tris[tri * 3 + 2] = 1;
	tri++;
	tris[tri * 3 + 0] = 1;
	tris[tri * 3 + 1] = 0;
	tris[tri * 3 + 2] = 4;
	tri++;
	trisN += 2;


	tris[tri * 3 + 0] = 5;
	tris[tri * 3 + 1] = 6;
	tris[tri * 3 + 2] = 2;
	tri++;
	tris[tri * 3 + 0] = 2;
	tris[tri * 3 + 1] = 1;
	tris[tri * 3 + 2] = 5;
	tri++;
	trisN += 2;

	tris[tri * 3 + 0] = 0;
	tris[tri * 3 + 1] = 3;
	tris[tri * 3 + 2] = 7;
	tri++;
	tris[tri * 3 + 0] = 7;
	tris[tri * 3 + 1] = 4;
	tris[tri * 3 + 2] = 0;
	tri++;
	trisN += 2;





}

void TM::SetToMyRectangle(V3 a, V3 b, V3 c, V3 d)
{
	vertsN = 4;
	trisN = 3;
	Allocate(vertsN, trisN);

	verts[0] = a;
	verts[1] = b;
	verts[2] = c;
	verts[3] = d;

	trisN = 0;
	int tri = 0;

	tris[tri * 3 + 0] = 0;
	tris[tri * 3 + 1] = 1;
	tris[tri * 3 + 2] = 3;
	tri++;
	tris[tri * 3 + 0] = 1;
	tris[tri * 3 + 1] = 2;
	tris[tri * 3 + 2] = 3;
	tri++;
	trisN += 2;

	tcs = new V3[4];
	tcs[1] = V3(0.0f, 0.0f, 0.0f);
	tcs[2] = V3(0.0f, 1.0f, 0.0f);
	tcs[3] = V3(1.0f, 1.0f, 0.0f);
	tcs[0] = V3(1.0f, 0.0f, 0.0f);
}

void TM::SetToRectangle(V3 O, V3 dims, V3 color) {

	vertsN = 4;
	trisN = 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < vertsN; vi++) {
		cols[vi] = color;
	}

	int vi = 0;
	verts[vi++] = O + V3(-dims[0] / 2.0f, +dims[1] / 2.0f, 0.0f);
	verts[vi++] = O + V3(-dims[0] / 2.0f, -dims[1] / 2.0f, 0.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, -dims[1] / 2.0f, 0.0f);
	verts[vi++] = O + V3(+dims[0] / 2.0f, +dims[1] / 2.0f, 0.0f);

	trisN = 0;
	int tri = 0;

	tris[tri * 3 + 0] = 0;
	tris[tri * 3 + 1] = 1;
	tris[tri * 3 + 2] = 2;
	tri++;
	tris[tri * 3 + 0] = 2;
	tris[tri * 3 + 1] = 3;
	tris[tri * 3 + 2] = 0;
	tri++;
	trisN += 2;

	tcs = new V3[4];
	tcs[0] = V3(0.0f, 0.0f, 0.0f);
	tcs[1] = V3(0.0f, 1.0f, 0.0f);
	tcs[2] = V3(1.0f, 1.0f, 0.0f);
	tcs[3] = V3(1.0f, 0.0f, 0.0f);

}



void TM::RenderPoints(PPC *ppc, FrameBuffer *fb) {

	for (int vi = 0; vi < vertsN; vi++) {
		V3 projV;
		if (!ppc->Project(verts[vi], projV))
			continue;
		unsigned int vcolor = cols[vi].GetColor();
		fb->DrawCircle((int) projV[0], (int) projV[1], 5, vcolor);
	}

}

void TM::VisualizeNormals(PPC *ppc, FrameBuffer *fb, float len) {

	for (int vi = 0; vi < vertsN; vi++) {
		fb->Draw3DSegment(verts[vi], verts[vi] + normals[vi].UnitVector()*len,
			V3(0.0f, 0.0f, 0.0f), V3(0.0f, 1.0f, 0.0f), ppc);
	}

}

void TM::RenderWireframe(PPC *ppc, FrameBuffer *fb) {

	for (int tri = 0; tri < trisN; tri++) {
		for (int ei = 0; ei < 3; ei++) {
			int ei1 = (ei + 1) % 3;
			V3 V0 = verts[tris[3 * tri + ei]];
			V3 V1 = verts[tris[3 * tri + ei1]];
			V3 c0 = cols[tris[3 * tri + ei]];
			V3 c1 = cols[tris[3 * tri + ei1]];
			fb->Draw3DSegment(V0, V1, c0, c1, ppc);
		}
	}

}

V3 SetEEQs(V3 v0, V3 v1, V3 v2) {

	V3 ret;
	ret[0] = v1[1] - v0[1];
	ret[1] = v0[0] - v1[0];
	ret[2] = -v0[0] * ret[0] + v0[1] * -ret[1];

	V3 v2p(v2[0], v2[1], 1.0f);
	if (v2p*ret < 0.0f)
		ret = ret * -1.0f;
 
	return ret;
}

M33 TM::ComputeSSIM(V3* pvs) {

	M33 ssim;
	ssim.SetColumn(0, V3(pvs[0][0], pvs[1][0], pvs[2][0]));
	ssim.SetColumn(1, V3(pvs[0][1], pvs[1][1], pvs[2][1]));
	ssim.SetColumn(2, V3(1.0f, 1.0f, 1.0f));
	ssim = ssim.Inverted();
	return ssim;

}

void TM::RenderProjector(PPC *ppc, FrameBuffer *fb, FrameBuffer *cubefb, V3 lightSource, M33 lightSourceMatrix) {
	V3 *projV = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], projV[vi]))
			projV[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	for (int tri = 0; tri < trisN; tri++) {
		V3 pvs[3];
		M33 vs;
		M33 cs;
		M33 ttcs;
		M33 nms;
		pvs[0] = projV[tris[3 * tri + 0]];
		pvs[1] = projV[tris[3 * tri + 1]];
		pvs[2] = projV[tris[3 * tri + 2]];
		cs[0] = cols[tris[3 * tri + 0]];
		cs[1] = cols[tris[3 * tri + 1]];
		cs[2] = cols[tris[3 * tri + 2]];
		if (tex) {
			ttcs[0] = tcs[tris[3 * tri + 0]];
			ttcs[1] = tcs[tris[3 * tri + 1]];
			ttcs[2] = tcs[tris[3 * tri + 2]];
		}
		vs[0] = verts[tris[3 * tri + 0]];
		vs[1] = verts[tris[3 * tri + 1]];
		vs[2] = verts[tris[3 * tri + 2]];
		if (normals) {
			nms[0] = normals[tris[3 * tri + 0]];
			nms[1] = normals[tris[3 * tri + 1]];
			nms[2] = normals[tris[3 * tri + 2]];
			//			nms[0] = nms[1] = nms[2] = ((vs[1] - vs[0]) ^ (vs[2] - vs[0])).UnitVector();
		}

		if (
			pvs[0][0] == FLT_MAX ||
			pvs[1][0] == FLT_MAX ||
			pvs[2][0] == FLT_MAX
			)
			continue;
		AABB aabb(pvs[0]);
		aabb.AddPoint(pvs[1]);
		aabb.AddPoint(pvs[2]);
		V3 minc(0.0f, 0.0f, 0.0f);
		V3 maxc((float)fb->w, (float)fb->h, 0.0f);
		V3 eeqs[3];
		for (int i = 0; i < 3; i++) {
			eeqs[i] = SetEEQs(pvs[i], pvs[(i + 1) % 3], pvs[(i + 2) % 3]);
		}
		if (!aabb.Clip(minc, maxc, 2))
			continue;
		int left = (int)(aabb.corners[0][0] + 0.5f);
		int right = (int)(aabb.corners[1][0] - 0.5f);
		int top = (int)(aabb.corners[0][1] + 0.5f);
		int bottom = (int)(aabb.corners[1][1] - 0.5f);
		M33 ssim = ComputeSSIM(pvs);
		M33 msim = ComputeMSIM(vs, ppc);
		V3 denABC = msim[0] + msim[1] + msim[2];
		M33 colsNumABC = cs.Transposed()*msim;
		M33 nmsNumABC = nms.Transposed()*msim;
		M33 tcsNumABC = ttcs.Transposed()*msim;

		M33 lightSourceMatrixInverted = lightSourceMatrix.Inverted();
		V3 C1minusC2 = ppc->C - lightSource;
		M33 viewPointMatrix;
		viewPointMatrix.SetColumn(0, ppc->a);
		viewPointMatrix.SetColumn(1, ppc->b);
		viewPointMatrix.SetColumn(2, ppc->c);

		V3 w2A = lightSourceMatrixInverted * C1minusC2;
		M33 w2B = lightSourceMatrixInverted * viewPointMatrix;
		V3 w2C, w2Vector;

		float w1, w2;
		int u2, v2, pixelNumber;

		M33 colsABC = (ssim * cs).Transposed();
		V3 zABC = ssim*V3(pvs[0][2], pvs[1][2], pvs[2][2]);
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);

				if (currPix * eeqs[0] < 0.0f || currPix * eeqs[1] < 0.0f
					|| currPix*eeqs[2] < 0.0f)
					continue;
				V3 ccSSv = colsABC * currPix;
				V3 ccMSv = (colsNumABC * currPix) / (denABC * currPix);
				V3 nmsv = (nmsNumABC*currPix) / (denABC*currPix);
				w1 = 1 / (denABC*currPix);
				nmsv = nmsv.UnitVector();
				V3 ctcs = (tcsNumABC * currPix) / (denABC * currPix);

				//currPix[2] = currPix*zABC;

				w2C = V3(w1 * currPix[0], w1 * currPix[1], w1);
				w2Vector = (w2B * w2C);
				w2Vector = w2Vector + w2A;
				w2 = w2Vector[2];
				u2 = (int)(w2Vector[0] / w2);
				v2 = (int)(w2Vector[1] / w2);

				pixelNumber = ((fb->h - v2 - 1) * fb->w) + u2;

				currPix[2] = currPix*zABC;
				
				if (pixelNumber >= 0 && pixelNumber < (fb->h*fb->w)) {
					double  esp = 1e-3;

					if (cubefb->pix[pixelNumber] != 0x00000000)
						fb->SetZB(currPix, cubefb->pix[pixelNumber]);
				
					else
						fb->SetZB(currPix, ccMSv.GetColor());
				}
			}
		}
	}
	delete[] projV;

}

void TM::RenderFilled(PPC *ppc, FrameBuffer *fb, FrameBuffer *frontfb, FrameBuffer *backfb, FrameBuffer *leftfb, FrameBuffer *rightfb, FrameBuffer *upfb, FrameBuffer *downfb,
	PPC *front, PPC *back, PPC *leftppc, PPC *rightppc, PPC *up, PPC *down)
{


	V3 *projV = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], projV[vi]))
			projV[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}
	V3 pointOnPlane(-512.0f, 512.0f, -512.0f);
	V3 pointOfIntersection;
	int dScalar;

	for (int tri = 0; tri < trisN; tri++) {
		V3 pvs[3];
		M33 vs;
		M33 cs;
		M33 ttcs;
		M33 nms;
		pvs[0] = projV[tris[3 * tri + 0]];
		pvs[1] = projV[tris[3 * tri + 1]];
		pvs[2] = projV[tris[3 * tri + 2]];
		cs[0] = cols[tris[3 * tri + 0]];
		cs[1] = cols[tris[3 * tri + 1]];
		cs[2] = cols[tris[3 * tri + 2]];
		if (tex) {
			ttcs[0] = tcs[tris[3 * tri + 0]];
			ttcs[1] = tcs[tris[3 * tri + 1]];
			ttcs[2] = tcs[tris[3 * tri + 2]];
		}
		vs[0] = verts[tris[3 * tri + 0]];
		vs[1] = verts[tris[3 * tri + 1]];
		vs[2] = verts[tris[3 * tri + 2]];
		if (normals) {
			nms[0] = normals[tris[3 * tri + 0]];
			nms[1] = normals[tris[3 * tri + 1]];
			nms[2] = normals[tris[3 * tri + 2]];
		}

		if (
			pvs[0][0] == FLT_MAX ||
			pvs[1][0] == FLT_MAX ||
			pvs[2][0] == FLT_MAX
			)
			continue;
		AABB aabb(pvs[0]);
		aabb.AddPoint(pvs[1]);
		aabb.AddPoint(pvs[2]);
		V3 minc(0.0f, 0.0f, 0.0f);
		V3 maxc((float)fb->w, (float)fb->h, 0.0f);
		V3 eeqs[3];
		for (int i = 0; i < 3; i++) {
			eeqs[i] = SetEEQs(pvs[i], pvs[(i + 1) % 3], pvs[(i + 2) % 3]);
		}
		if (!aabb.Clip(minc, maxc, 2))
			continue;
		int left = (int)(aabb.corners[0][0] + 0.5f);
		int right = (int)(aabb.corners[1][0] - 0.5f);
		int top = (int)(aabb.corners[0][1] + 0.5f);
		int bottom = (int)(aabb.corners[1][1] - 0.5f);
		M33 ssim = ComputeSSIM(pvs);
		M33 msim = ComputeMSIM(vs, ppc);
		V3 denABC = msim[0] + msim[1] + msim[2];
		M33 colsNumABC = cs.Transposed()*msim;
		M33 nmsNumABC = nms.Transposed()*msim;
		M33 tcsNumABC = ttcs.Transposed()*msim;
		M33 colsABC = (ssim * cs).Transposed();
		V3 zABC = ssim*V3(pvs[0][2], pvs[1][2], pvs[2][2]);
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				if (currPix * eeqs[0] < 0.0f || currPix * eeqs[1] < 0.0f
					|| currPix*eeqs[2] < 0.0f)
					continue;
				V3 ccSSv = colsABC * currPix;
				V3 ccMSv = (colsNumABC * currPix) / (denABC * currPix);
				V3 nmsv = (nmsNumABC*currPix) / (denABC*currPix);
				nmsv = nmsv.UnitVector();
				V3 ctcs = (tcsNumABC * currPix) / (denABC * currPix);

				currPix[2] = currPix*zABC;
				if (tex) {
					fb->SetZB(currPix, tex->LookUpNN(ctcs[0], ctcs[1]));
//					fb->SetZB(currPix, tex->LookUpBilinear(ctcs[0], ctcs[1]));
					continue;
				}
				if (id == 3) {
					fb->SetZB(currPix, ccSSv.GetColor());
					continue;
				}
				if (id == 1) {
					V3 materialColor(1.0f, 0.0f, 0.0f);
					float ka = 0.3f;
					V3 L(0.0f, 0.0f, 0.0f);
					if (scene)
						L = scene->L;
					V3 P = ppc->Unproject(currPix);
					V3 lv = (L - P).UnitVector(); // light vector
					float kd = nmsv*lv; kd = (kd < 0.0f) ? 0.0f : kd;
					V3 litColor = materialColor*(ka + (1.0f - ka)*kd);
					V3 ev = ppc->C - P; // eye vector
					V3 evn = nmsv*(ev*nmsv); // normal component of eye vector
					rv = (evn*2.0f - ev).UnitVector(); // reflected vector
					float specc = 180.0f;
					if (scene)
						specc = scene->specc;
					float ks = rv*lv; 
					ks = rv*lv;
					ks = (ks < 0.0f) ? 0.0f : ks;
 					ks = powf(ks, specc);

					unsigned int cubemapColor = 0x000000;

					V3 projectedPoint;

					if (back->Project(rv, projectedPoint))
					{
						if (projectedPoint[0] >= 0 && projectedPoint[0] <= backfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= backfb->h)
						{
							cubemapColor = backfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					if (leftppc->Project(rv, projectedPoint))
					{

						if (projectedPoint[0] >= 0 && projectedPoint[0] <= leftfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= leftfb->h)
						{
							cubemapColor = leftfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					if (front->Project(rv, projectedPoint))
					{

						if (projectedPoint[0] >= 0 && projectedPoint[0] <= frontfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= frontfb->h)
						{
							cubemapColor = frontfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					if (rightppc->Project(rv, projectedPoint))
					{
						if (projectedPoint[0] >= 0 && projectedPoint[0] <= rightfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= rightfb->h)
						{
							cubemapColor = rightfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					if (down->Project(rv, projectedPoint))
					{
						if (projectedPoint[0] >= 0 && projectedPoint[0] <= downfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= downfb->h)
						{
							cubemapColor = downfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					if (up->Project(rv, projectedPoint))
					{
						if (projectedPoint[0] >= 0 && projectedPoint[0] <= upfb->w && projectedPoint[1] >= 0 && projectedPoint[1] <= upfb->h)
						{
							cubemapColor = upfb->Get(projectedPoint[0], projectedPoint[1]);
						}
					}

					fb->SetZB(currPix, cubemapColor);
					continue;
				}
				if (id == 5) {
					unsigned int currColor = 0xFFFFFFFF;
					if (scene->smfb) {
						V3 P = ppc->Unproject(currPix);
						V3 PP;
						if (scene->smppc->Project(P, PP)) {
							if (!scene->smfb->IsVisible(PP)) {
								currColor = 0xFF000000;
							}
						}
					}
					fb->SetZB(currPix, currColor);
					continue;
				}

				fb->SetZB(currPix, ccMSv.GetColor());
			}
		}
	}


	delete [] projV;

}


V3 TM::GetCenterOfMass() {

	V3 ret(0.0f, 0.0f, 0.0f);
	for (int vi = 0; vi < vertsN; vi++) {
		ret = ret + verts[vi];
	}
	ret = ret / (float)vertsN;
	return ret;

}


void TM::LoadBin(char *fname) {

	ifstream ifs(fname, ios::binary);
	if (ifs.fail()) {
		cerr << "INFO: cannot open file: " << fname << endl;
		return;
	}

	ifs.read((char*)&vertsN, sizeof(int));
	char yn;
	ifs.read(&yn, 1); // always xyz
	if (yn != 'y') {
		cerr << "INTERNAL ERROR: there should always be vertex xyz data" << endl;
		return;
	}
	if (verts)
		delete verts;
	verts = new V3[vertsN];

	ifs.read(&yn, 1); // cols 3 floats
	if (cols)
		delete cols;
	cols = 0;
	if (yn == 'y') {
		cols = new V3[vertsN];
	}

	ifs.read(&yn, 1); // normals 3 floats
	if (normals)
		delete normals;
	normals = 0;
	if (yn == 'y') {
		normals = new V3[vertsN];
	}

	ifs.read(&yn, 1); // texture coordinates 2 floats
	float *tcs = 0; // don't have texture coordinates for now
	if (tcs)
		delete tcs;
	tcs = 0;
	if (yn == 'y') {
		tcs = new float[vertsN * 2];
	}

	ifs.read((char*)verts, vertsN * 3 * sizeof(float)); // load verts

	if (cols) {
		ifs.read((char*)cols, vertsN * 3 * sizeof(float)); // load cols
	}

	if (normals)
		ifs.read((char*)normals, vertsN * 3 * sizeof(float)); // load normals

	if (tcs)
		ifs.read((char*)tcs, vertsN * 2 * sizeof(float)); // load texture coordinates

	ifs.read((char*)&trisN, sizeof(int));
	if (tris)
		delete tris;
	tris = new unsigned int[trisN * 3];
	ifs.read((char*)tris, trisN * 3 * sizeof(unsigned int)); // read tiangles

	ifs.close();

	cerr << "INFO: loaded " << vertsN << " verts, " << trisN << " tris from " << endl << "      " << fname << endl;
	cerr << "      xyz " << ((cols) ? "rgb " : "") << ((normals) ? "nxnynz " : "") << ((tcs) ? "tcstct " : "") << endl;

	delete[]tcs;

}



void TM::RotateAboutAxis(V3 O, V3 a, float theta) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi].RotatePointAboutAxis(O, a, theta);
	}

}

M33 TM::ComputeMSIM(M33 vs, PPC *ppc) {

	M33 qm = vs.Transposed();
	qm.SetColumn(0, qm.GetColumn(0) - ppc->C);
	qm.SetColumn(1, qm.GetColumn(1) - ppc->C);
	qm.SetColumn(2, qm.GetColumn(2) - ppc->C);

	M33 cam;
	cam.SetColumn(0, ppc->a);
	cam.SetColumn(1, ppc->b);
	cam.SetColumn(2, ppc->c);

	qm = qm.Inverted() * cam;

	return qm;
}


AABB TM::ComputeAABB() {

	AABB aabb(verts[0]);
	for (int vi = 1; vi < vertsN; vi++)
		aabb.AddPoint(verts[vi]);
	return aabb;

}

void TM::TranslateVertsZ(float z) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + V3(0.0f, 0.0f, z);
	}

}

void TM::TranslateVertsY(float z) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + V3(0.0f, z, 0.0f);
	}
}

void TM::TranslateVertsX(float z) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + V3(z, 0.0f, 0.0f);
	}
}