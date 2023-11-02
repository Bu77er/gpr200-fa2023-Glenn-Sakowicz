#pragma once

#include "../ew/mesh.h"

namespace gs
{
	ew::MeshData createsphere(float radius, int numSegments);
	ew::MeshData createCylinder(float height, float radius, int numSegments);
	ew::MeshData createPlane(float width, float heigth, int subdivisions);
}