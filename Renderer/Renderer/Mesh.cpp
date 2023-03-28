#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);

}

void Mesh::InitialiseQuad()
{
	//chcek mesh doesn't exist
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	//unit quad
	Vertex vertices[6];
	//tri 1
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	//tri 2
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	//vertex normals
	vertices[0].normal = { 0,1,0,0 };
	vertices[1].normal = { 0,1,0,0 };
	vertices[2].normal = { 0,1,0,0 };
	vertices[3].normal = { 0,1,0,0 };
	vertices[4].normal = { 0,1,0,0 };
	vertices[5].normal = { 0,1,0,0 };

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//quad has 2 tris

	triCount = 2;
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}

void Mesh::Initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned int* indicies)
{
	//chcek mesh doesn't exist
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);


	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//bind indicies
	if (indexCount != 0) {
		glGenBuffers(1, &ibo);
		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else {
		triCount = vertexCount / 3;
	}

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::InitialiseFromFile(std::string filename)
{
	//read vertices from model
	//aiPostProcessSteps steps = aiPro
	const aiScene* scene = aiImportFile(filename.c_str(),
		aiProcess_Triangulate &
		aiProcess_CalcTangentSpace &
		aiProcess_JoinIdenticalVertices);
	//load meshes we find
	std::vector<aiMesh*> meshes;
	for (int i = 0; i < scene->mNumMeshes; i++) {
		meshes.push_back(scene->mMeshes[i]);
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int numV = 0;
	int numF = 0;
	int totalVert = 0;

	for (aiMesh* m : meshes) {

		//check if the mesh type is and skip it if it is a line
		if (m->mPrimitiveTypes & aiPrimitiveType_LINE) continue;

		//get faces and vertices of the current mesh
		numF = m->mNumFaces;
		numV = m->mNumVertices;


		for (int i = 0; i < numF; i++)
		{
			//generate triangle
			indices.push_back(m->mFaces[i].mIndices[0] + totalVert);
			indices.push_back(m->mFaces[i].mIndices[2] + totalVert);
			indices.push_back(m->mFaces[i].mIndices[1] + totalVert);

			//generate second triangle for quads
			if (m->mFaces[i].mNumIndices == 4) {
				indices.push_back(m->mFaces[i].mIndices[0] + totalVert);
				indices.push_back(m->mFaces[i].mIndices[3] + totalVert);
				indices.push_back(m->mFaces[i].mIndices[2] + totalVert);
			}
		}

		//add to total vert count for initialising size
		totalVert += numV;

		//extract vertex data
		for (int i = 0; i < numV; i++)
		{
			//position
			Vertex vert = Vertex{ glm::vec4(m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z, 1), glm::vec4(0,0,0,0), glm::vec2(0,0) };
			//normals
			vert.normal = glm::vec4(m->mNormals[i].x, m->mNormals[i].y, m->mNormals[i].z, 0);
			//UV's

			//add vertex
			vertices.push_back(vert);
		}
	}

	Initialise(totalVert, vertices.data(), indices.size(), indices.data());

}

void Mesh::SetPosition(glm::vec3 position)
{
	glm::translate(quadTransform, position);
	quadTransform = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		position.x, position.y, position.z, 1
	};
}

void Mesh::ApplyMaterial(ShaderProgram* shader)
{
	shader->SetVectorUniform("Ka", Ka);
	shader->SetVectorUniform("Kd", Kd);
	shader->SetVectorUniform("Ks", Ks);
	shader->SetFloatUniform("SpecularPower", specularPower);
}

void Mesh::LoadMaterial(std::string filename)
{
	std::fstream file(filename.c_str(), std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];
	while (!file.eof()) {
		file.getline(buffer, 256);
		line = buffer;
		std::stringstream ss(line, std::stringstream::in | std::stringstream::out);
		if (line.find("Ka") == 0)
			ss >> header >> Ka.x >> Ka.y >> Ka.z;
		else if (line.find("Ks") == 0)
			ss >> header >> Ks.x >> Ks.y >> Ks.z;
		else if (line.find("Kd") == 0)
			ss >> header >> Kd.x >> Kd.y >> Kd.z;
		else if (line.find("Ns") == 0)
			ss >> header >> specularPower;
	}
}
