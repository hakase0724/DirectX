#include "stdafx.h"
#include "SphereMesh.h"
#include <DirectXMath.h>

using namespace MyDirectX;
using namespace DirectX;

SphereMesh::SphereMesh()
{
	const int u_max = 30;
	const int v_max = 15;
	vertexNum = u_max * (v_max + 1);
	indexNum = 2 * v_max * (u_max + 1);

	vertics = new VERTEX_DATA[vertexNum];
	for (int v = 0; v <= v_max; v++) {
		for (int u = 0; u < u_max; u++) {
			double theta = XMConvertToRadians(180.0f * v / v_max);
			double phi = XMConvertToRadians(360.0f * u / u_max);
			//’¼Œa‚ª1‚É‚È‚é‚æ‚¤‚É0.5‚ð‚©‚¯‚Ä‚¢‚é(sin‚âcos‚Í1‚ªo‚Ä‚«‚Ä‚»‚¤‚·‚é‚Æ’¼Œa‚ª2‚É‚È‚Á‚Ä‚µ‚Ü‚¤‚©‚ç)
			double x = sin(theta) * cos(phi) * 0.5f;
			double y = cos(theta) * 0.5f;
			double z = sin(theta) * sin(phi) * 0.5f;
			vertics[u_max * v + u].V = { (float)x, (float)y, (float)z };
			vertics[u_max * v + u].N = { (float)x, (float)y, (float)z };
		}
	}

	int i = 0;
	indexes = new int[indexNum];
	for (int v = 0; v < v_max; v++) {
		for (int u = 0; u <= u_max; u++) {
			if (u == u_max) {
				indexes[i++] = v * u_max;
				indexes[i++] = (v + 1) * u_max;
			}
			else {
				indexes[i++] = (v * u_max) + u;
				indexes[i++] = indexes[i - 1] + u_max;
			}
		}
	}
	
}


SphereMesh::~SphereMesh()
{
	delete vertics;
	delete indexes;
}

