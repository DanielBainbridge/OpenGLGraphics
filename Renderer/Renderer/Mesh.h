#pragma once
#include "Graphics.h"
class Mesh {
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex {
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void InitialiseQuad();
	virtual void Draw();
	//takes an array of vertices,a count of vertices
	void Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indicies = nullptr);
	void InitialiseFromFile(std::string filename);

protected:
	unsigned int triCount;
	//vertex array object, vertex buffer object, index buffer object
	unsigned int vao, vbo, ibo;
};