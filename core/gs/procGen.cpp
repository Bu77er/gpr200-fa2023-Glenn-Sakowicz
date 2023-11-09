#include "procGen.h"

namespace gs
{
	ew::MeshData createsphere(float radius, int numSegments)
	{
		ew::MeshData mesh;
		int numVertices = (numSegments + 1) * (numSegments + 1);
		int numIndices = numSegments * numSegments * 6;

		mesh.vertices.resize(numVertices);
		mesh.indices.resize(numIndices);

		int vertexIndex = 0;
		int indexIndex = 0;

		for (int i = 0; i <= numSegments; i++) {
			float phi = static_cast<float>(i) / numSegments * ew::PI;
			for (int j = 0; j <= numSegments; j++) {
				float theta = static_cast<float>(j) / numSegments * 2.0f * ew::PI;

				float x = radius * sin(phi) * cos(theta);
				float y = radius * cos(phi);
				float z = radius * sin(phi) * sin(theta);

				mesh.vertices[vertexIndex].pos = ew::Vec3(x, y, z);
				mesh.vertices[vertexIndex].normal = ew::Normalize(ew::Vec3(x, y, z));
				mesh.vertices[vertexIndex].uv = ew::Vec2(static_cast<float>(j) / numSegments, 1.0f - static_cast<float>(i) / numSegments);

				if (i < numSegments && j < numSegments) {
					int topLeft = i * (numSegments + 1) + j;
					int topRight = topLeft + 1;
					int bottomLeft = (i + 1) * (numSegments + 1) + j;
					int bottomRight = bottomLeft + 1;

					mesh.indices[indexIndex++] = topLeft;
					mesh.indices[indexIndex++] = bottomLeft;
					mesh.indices[indexIndex++] = topRight;

					mesh.indices[indexIndex++] = topRight;
					mesh.indices[indexIndex++] = bottomLeft;
					mesh.indices[indexIndex++] = bottomRight;
				}

				vertexIndex++;
			}
		}

		return mesh;
	}
	ew::MeshData createCylinder(float height, float radius, int numSegments)
	{
		ew::MeshData mesh;
		int vertices = (numSegments + 1) * 2;
		int indices = numSegments * 6;

		mesh.vertices.resize(vertices);
		mesh.indices.resize(indices);

		float topY = height / 2;
		float bottomY = -topY;
		float thetaStep = 2.0f * ew::PI / numSegments;
		int bottomCenter = mesh.vertices.size() / 2;
		int topCenter = bottomCenter + numSegments + 1;


		for (int i(0); i <= numSegments; i++)
		{
			ew::Vertex top;
			float theta = i * thetaStep;
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			top.pos = { 0,topY,0 };
			top.normal = { 0.0f,1.0f,0.0f };
			top.uv = { static_cast<float>(i) / numSegments, 0.0f };
			mesh.vertices.push_back(top);

			top.pos = { x,topY,z };
			top.normal = { 0.0f,1.0f,0.0f };
			top.uv = { static_cast<float>(i) / numSegments, 0.0f };
			mesh.vertices.push_back(top);
		}
		for (int i(0); i <= numSegments; i++)
		{
			ew::Vertex bottom;
			float theta = i * thetaStep;
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			bottom.pos = { 0, bottomY, 0 };
			bottom.normal = { 0.0f,-1.0f,0.0f };
			bottom.uv = { static_cast<float>(i) / numSegments, 1.0f };
			mesh.vertices.push_back(bottom);

			bottom.pos = { x, bottomY, z };
			bottom.normal = { 0.0f,-1.0f,0.0f };
			bottom.uv = { static_cast<float>(i) / numSegments, 1.0f };
			mesh.vertices.push_back(bottom);
		}
		int start(0);
		for (int i = 0; i < numSegments; i++) 
		{
			mesh.indices.push_back(start + i);
			mesh.indices.push_back(topCenter);
			mesh.indices.push_back(start + i + 1);

		}
			
		return mesh;
	}
	ew::MeshData createPlane(float width, float height, int subdivisions)
	{
		ew::MeshData mesh;
		float stepX = width / subdivisions;
		float stepY = height / subdivisions;
		int numVertices = (subdivisions + 1) * (subdivisions + 1);
		int numIndices = subdivisions * subdivisions * 6;

		mesh.vertices.resize(numVertices);
		mesh.indices.resize(numIndices);

		int vertex = 0;
		int index = 0;

		for (int row = 0; row <= subdivisions; row++) {
			for (int col = 0; col <= subdivisions; col++) {
				float x = col * stepX - width / 2.0f;
				float z = row * stepY - height / 2.0f;

				mesh.vertices[vertex].pos = ew::Vec3(x, 0.0f, z);
				mesh.vertices[vertex].normal = ew::Vec3(0.0f, 1.0f, 0.0f);
				mesh.vertices[vertex].uv = ew::Vec2(static_cast<float>(col) / subdivisions, static_cast<float>(row) / subdivisions);

				if (row < subdivisions && col < subdivisions) {
					int topLeft = row * (subdivisions + 1) + col;
					int topRight = topLeft + 1;
					int bottomLeft = (row + 1) * (subdivisions + 1) + col;
					int bottomRight = bottomLeft + 1;

					mesh.indices[index++] = topLeft;
					mesh.indices[index++] = bottomLeft;
					mesh.indices[index++] = topRight;

					mesh.indices[index++] = topRight;
					mesh.indices[index++] = bottomLeft;
					mesh.indices[index++] = bottomRight;
				}

				vertex++;
			}
		}
		return mesh;
	}
}