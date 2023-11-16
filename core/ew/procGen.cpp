/*
	Author: Eric Winebrenner
*/


#include "procGen.h"
#include <stdlib.h>

namespace ew {
	/// <summary>
	/// Helper function for createCube. Note that this is not meant to be used standalone
	/// </summary>
	/// <param name="normal">Normal direction of the face</param>
	/// <param name="size">Width/height of the face</param>
	/// <param name="mesh">MeshData struct to fill</param>
	static void createCubeFace(ew::Vec3 normal, float size, MeshData* mesh) {
		unsigned int startVertex = mesh->vertices.size();
		ew::Vec3 a = ew::Vec3(normal.z, normal.x, normal.y); //U axis
		ew::Vec3 b = ew::Cross(normal, a); //V axis
		for (int i = 0; i < 4; i++)
		{
			int col = i % 2;
			int row = i / 2;

			ew::Vec3 pos = normal * size * 0.5f;
			pos -= (a + b) * size * 0.5f;
			pos += (a * col + b * row) * size;
			Vertex vertex;// = &mesh->vertices[mesh->vertices.size()];
			vertex.pos = pos;
			vertex.normal = normal;
			vertex.uv = ew::Vec2(col, row);
			mesh->vertices.push_back(vertex);
		}

		//Indices
		mesh->indices.push_back(startVertex);
		mesh->indices.push_back(startVertex + 1);
		mesh->indices.push_back(startVertex + 3);
		mesh->indices.push_back(startVertex + 3);
		mesh->indices.push_back(startVertex + 2);
		mesh->indices.push_back(startVertex);
	}
	/// <summary>
	/// Creates a cube of uniform size
	/// </summary>
	/// <param name="size">Total width, height, depth</param>
	/// <param name="mesh">MeshData struct to fill. Will be cleared.</param>
	MeshData createCube(float size) {
		MeshData mesh;
		mesh.vertices.reserve(24); //6 x 4 vertices
		mesh.indices.reserve(36); //6 x 6 indices
		createCubeFace(ew::Vec3{ +0.0f,+0.0f,+1.0f }, size, &mesh); //Front
		createCubeFace(ew::Vec3{ +1.0f,+0.0f,+0.0f }, size, &mesh); //Right
		createCubeFace(ew::Vec3{ +0.0f,+1.0f,+0.0f }, size, &mesh); //Top
		createCubeFace(ew::Vec3{ -1.0f,+0.0f,+0.0f }, size, &mesh); //Left
		createCubeFace(ew::Vec3{ +0.0f,-1.0f,+0.0f }, size, &mesh); //Bottom
		createCubeFace(ew::Vec3{ +0.0f,+0.0f,-1.0f }, size, &mesh); //Back
		return mesh;
	}
	MeshData createPlane(float width, float height, int subdivisions)
	{
		//VERTICES
		MeshData mesh;
		int columns = subdivisions + 1;
		for (size_t row = 0; row <= subdivisions; row++)
		{
			for (size_t col = 0; col <= subdivisions; col++)
			{
				Vertex v;
				v.uv.x = ((float)col / subdivisions);
				v.uv.y = ((float)row / subdivisions);
				v.pos.x = -width/2 + width * v.uv.x;
				v.pos.y = 0;
				v.pos.z = height/2 -height * v.uv.y;
				v.normal = ew::Vec3(0, 1, 0);
				mesh.vertices.push_back(v);
			}
		}
		//INDICES
		for (size_t row = 0; row < subdivisions; row++)
		{
			for (size_t col = 0; col < subdivisions; col++)
			{
				int start = row * columns + col;
				mesh.indices.push_back(start);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns + 1);
				mesh.indices.push_back(start + columns + 1);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start);
			}
		}
		return mesh;
	}
	MeshData createSphere(float radius, int subdivisions)
	{
		MeshData mesh;
		//VERTICES
		float thetaStep = ew::TAU / subdivisions;
		float phiStep = ew::PI / subdivisions;
		for (size_t row = 0; row <= subdivisions; row++)
		{
			float phi = row * phiStep;
			for (size_t col = 0; col <= subdivisions; col++)
			{
				float theta = thetaStep * col;
				Vertex v;
				v.normal.x = cosf(theta) * sinf(phi);
				v.normal.y = cosf(phi);
				v.normal.z = sinf(theta) * sinf(phi);
				v.pos = v.normal * radius;
				v.uv.x = (float)col / subdivisions;
				v.uv.y = 1.0 - ((float)row / subdivisions);
				mesh.vertices.push_back(v);
			}
		}
		
		//INDICES
		unsigned int columns = subdivisions + 1;
		unsigned int sideStart = columns;
		unsigned int poleStart = 0;
		//Top cap
		for (size_t i = 0; i < subdivisions; i++)
		{
			mesh.indices.push_back(sideStart + i);
			mesh.indices.push_back(poleStart + i);
			mesh.indices.push_back(sideStart +i+1);
		}
		//Rows of quads for sides
		for (size_t row = 1; row < subdivisions - 1; row++)
		{
			for (size_t col = 0; col < subdivisions; col++)
			{
				int start = row * columns + col;
				mesh.indices.push_back(start);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns + 1);
			}
		}
		//Bottom cap
		poleStart = (columns * columns) - columns;
		sideStart = poleStart - columns;
		for (size_t i = 0; i < subdivisions; i++)
		{
			mesh.indices.push_back(sideStart + i);
			mesh.indices.push_back(sideStart + i + 1);
			mesh.indices.push_back(poleStart + i);
		}
		return mesh;
	}
	void createCylinderRing(MeshData* meshData, float radius, int subdivisions, float y, bool sideFacing) {
		float thetaStep = ew::TAU / subdivisions;
		for (size_t i = 0; i <= subdivisions; i++)
		{
			float theta = i * thetaStep;
			float cosA = cosf(theta);
			float sinA = sinf(theta);
			ew::Vertex v;
			v.pos = ew::Vec3(cosA * radius, y, sinA * radius);
			if (sideFacing) {
				v.normal = ew::Vec3(cosA, 0, sinA);
				v.uv = ew::Vec2((float)i / subdivisions, y > 0 ? 1 : 0);
			}
			else {
				v.normal = ew::Vec3(0, ew::Sign(y), 0);
				v.uv = ew::Vec2(cosA * 0.5 + 0.5, sinA * 0.5 + 0.5);
			}

			meshData->vertices.push_back(v);
		}
	}
	MeshData createCylinder(float radius, float height, int subdivisions)
	{
		MeshData mesh;

		//VERTICES
		{
			const float topY = height * 0.5;
			const float bottomY = -topY;

			ew::Vertex topVertex;
			topVertex.pos = ew::Vec3(0, topY, 0);
			topVertex.normal = ew::Vec3(0, 1, 0);
			topVertex.uv = ew::Vec2(0.5);
			mesh.vertices.push_back(topVertex);

			createCylinderRing(&mesh, radius, subdivisions, topY, false);
			createCylinderRing(&mesh, radius, subdivisions, topY, true);
			createCylinderRing(&mesh, radius, subdivisions, bottomY, true);
			createCylinderRing(&mesh, radius, subdivisions, bottomY, false);

			ew::Vertex bottomVertex;
			bottomVertex.pos = ew::Vec3(0, bottomY, 0);
			bottomVertex.normal = ew::Vec3(0, -1, 0);
			bottomVertex.uv = ew::Vec2(0.5);
			mesh.vertices.push_back(bottomVertex);
		}
		

		//INDICES
		{
			int columns = subdivisions + 1;
			//Top cap
			for (size_t i = 0; i < columns; i++)
			{
				mesh.indices.push_back(0);
				mesh.indices.push_back(i + 1);
				mesh.indices.push_back(i);
			}
			int sideStart = columns;
			//Sides
			for (size_t i = 0; i < columns; i++)
			{
				int start = sideStart + i;
				mesh.indices.push_back(start);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start + columns);
				mesh.indices.push_back(start + 1);
				mesh.indices.push_back(start + columns + 1);
			}
			//Bottom cap
			int bottomIndex = mesh.vertices.size() - 1;
			sideStart = bottomIndex - columns;
			for (size_t i = 0; i < columns; i++)
			{
				mesh.indices.push_back(bottomIndex);
				mesh.indices.push_back(sideStart + i);
				mesh.indices.push_back(sideStart + i + 1);
			}
		}
		return mesh;
	}
}