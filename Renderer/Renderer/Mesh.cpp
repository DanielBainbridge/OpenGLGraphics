#include "Mesh.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ShaderProgram.h"
#include "assimp_glm_helpers.h"






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

	//vertex texture coordinates
	vertices[0].texCoord = { 0.0f, 1.0f };
	vertices[1].texCoord = { 1.0f, 1.0f };
	vertices[2].texCoord = { 0.0f, 0.0f };
	vertices[3].texCoord = { 0.0f, 0.0f };
	vertices[4].texCoord = { 1.0f, 1.0f };
	vertices[5].texCoord = { 1.0f, 0.0f };

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	//enable third element as texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

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

	//enable third element as texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//enable fourth element as tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40);

	//enable fifth element as bone ID
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));

	//enable sixth element as weights
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));

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

Mesh* Mesh::InitialiseFromAiMesh(aiMesh* meshToLoad, Model* model)
{
	Mesh* newMesh = new Mesh();
	std::vector<Mesh::Vertex> vertices;
	std::vector<unsigned int> indices;

	newMesh->modelOwner = model;

	int numV = 0;
	int numF = 0;
	int totalVert = 0;

	//check if the mesh type is and skip it if it is a line
	if (meshToLoad->mPrimitiveTypes & aiPrimitiveType_LINE) return nullptr;

	//get faces and vertices of the current mesh
	numF = meshToLoad->mNumFaces;
	numV = meshToLoad->mNumVertices;


	for (int i = 0; i < numF; i++)
	{
		//generate triangle
		indices.push_back(meshToLoad->mFaces[i].mIndices[0] + totalVert);
		indices.push_back(meshToLoad->mFaces[i].mIndices[2] + totalVert);
		indices.push_back(meshToLoad->mFaces[i].mIndices[1] + totalVert);

		//generate second triangle for quads
		if (meshToLoad->mFaces[i].mNumIndices == 4) {
			indices.push_back(meshToLoad->mFaces[i].mIndices[0] + totalVert);
			indices.push_back(meshToLoad->mFaces[i].mIndices[3] + totalVert);
			indices.push_back(meshToLoad->mFaces[i].mIndices[2] + totalVert);
		}
	}

	//add to total vert count for initialising size
	totalVert += numV;

	//extract vertex data
	for (int i = 0; i < numV; i++)
	{
		//position
		Vertex vert = Vertex{ glm::vec4(meshToLoad->mVertices[i].x, meshToLoad->mVertices[i].y, meshToLoad->mVertices[i].z, 1), glm::vec4(0,0,0,0), glm::vec2(0,0) };
		//normals
		vert.normal = glm::vec4(meshToLoad->mNormals[i].x, meshToLoad->mNormals[i].y, meshToLoad->mNormals[i].z, 0);
		//UV's
		if (meshToLoad->mTextureCoords[0]) {
			vert.texCoord = glm::vec2(meshToLoad->mTextureCoords[0][i].x, meshToLoad->mTextureCoords[0][i].y);
		}
		else
			vert.texCoord = glm::vec2(0);
		//add vertex
		//tangents
		if (meshToLoad->HasTangentsAndBitangents()) {
			vert.tangent = glm::vec4(meshToLoad->mTangents[i].x, meshToLoad->mTangents[i].y, meshToLoad->mTangents[i].z, 1);
		}
		if (!meshToLoad->HasTangentsAndBitangents()) {
			newMesh->CalculateTangents(vertices, numV, indices);
		}


		newMesh->SetVertexBoneDataToDefault(vert);

		vert.position = glm::vec4(AssimpGLMHelpers::GetGLMVec(meshToLoad->mVertices[i]), 1);
		vert.normal = glm::vec4(AssimpGLMHelpers::GetGLMVec(meshToLoad->mVertices[i]), 0);

		vertices.push_back(vert);

	}

	newMesh->Initialise(totalVert, vertices.data(), indices.size(), indices.data());
	return newMesh;
}

void Mesh::SetVertexBoneData(Mesh::Vertex& vertex, int boneID, float weight) {
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
	{
		if (vertex.boneIDs[i] < 0) {
			vertex.weights[i] = weight;
			vertex.boneIDs[i] = boneID;
		}
	}
}
void Mesh::SetVertexBoneDataToDefault(Mesh::Vertex& vertex)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
		vertex.boneIDs[i] = -1;
		vertex.weights[i] = 0.0f;
	}
}

void Mesh::SetTransform(glm::vec3 position, glm::vec3 eulerAngles, glm::vec3 scale)
{
	this->position = position;
	this->rotation = eulerAngles;
	this->scale = scale;

	quadTransform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void Mesh::SetPosition(glm::vec3 position)
{
	this->position = position;
	quadTransform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void Mesh::SetRotationEuler(glm::vec3 eulerAngles)
{
	rotation = eulerAngles;
	quadTransform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}

void Mesh::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	quadTransform = glm::translate(glm::mat4(1), position)
		* glm::rotate(glm::mat4(1), glm::radians(rotation.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), scale);
}


void Mesh::ApplyMaterial(ShaderProgram* shader)
{
	if (isPBR) {
		ApplyPBRMaskMaterial(shader);
		return;
	}
	ApplySpecularMaterial(shader);
}

void Mesh::ApplySpecularMaterial(ShaderProgram* shader)
{
	shader->bindUniform("Ka", Ka);
	shader->bindUniform("Kd", Kd);
	shader->bindUniform("Ks", Ks);
	shader->bindUniform("SpecularPower", specularPower);

	mapKd.Bind(0);
	shader->bindUniform("diffuseTex", 0);
	mapKs.Bind(1);
	shader->bindUniform("specularTex", 1);
	mapNormal.Bind(2);
	shader->bindUniform("normalTex", 2);
}

void Mesh::ApplyPBRMaterial(ShaderProgram* shader)
{
	albedoMap.Bind(0);
	shader->bindUniform("albedoMap", 0);
	normalMap.Bind(1);
	shader->bindUniform("normalMap", 1);
	metallicMap.Bind(2);
	shader->bindUniform("metallicMap", 2);
	roughnessMap.Bind(3);
	shader->bindUniform("roughnessMap", 3);
	aoMap.Bind(4);
	shader->bindUniform("aoMap", 4);
	emissiveMap.Bind(5);
	shader->bindUniform("emissiveMap", 5);

	shader->bindUniform("Tiling", UVTiling);
	shader->bindUniform("UVOffset", UVOffset);
	shader->bindUniform("NormalTiling", normalUVTiling);
	shader->bindUniform("NormalUVOffset", normalUVOffset);
	shader->bindUniform("MetallicTiling", metallicUVTiling);
	shader->bindUniform("MetallicUVOffset", metallicUVOffset);
	shader->bindUniform("RoughnessTiling", roughnessUVTiling);
	shader->bindUniform("RoughnessUVOffset", roughnessUVOffset);
	shader->bindUniform("AOTiling", AOUVTiling);
	shader->bindUniform("AOUVOffset", AOUVOffset);
	shader->bindUniform("EmissiveTiling", emissiveUVTiling);
	shader->bindUniform("EmissiveUVOffset", emissiveUVOffset);
	shader->bindUniform("EmissiveIntensity", emissiveIntensity);
}

void Mesh::ApplyPBRMaskMaterial(ShaderProgram* shader)
{
	albedoMap.Bind(0);
	shader->bindUniform("albedoMap", 0);
	normalMap.Bind(1);
	shader->bindUniform("normalMap", 1);
	maskMap.Bind(2);
	shader->bindUniform("maskMap", 2);
	emissiveMap.Bind(3);
	shader->bindUniform("emissiveMap", 3);


	shader->bindUniform("Tiling", UVTiling);
	shader->bindUniform("UVOffset", UVOffset);
	shader->bindUniform("NormalTiling", normalUVTiling);
	shader->bindUniform("NormalUVOffset", normalUVOffset);
	shader->bindUniform("MaskTiling", maskUVTiling);
	shader->bindUniform("MaskUVOffset", maskUVOffset);
	shader->bindUniform("EmissiveTiling", emissiveUVTiling);
	shader->bindUniform("EmissiveUVOffset", emissiveUVOffset);
	shader->bindUniform("EmissiveIntensity", emissiveIntensity);
}


void Mesh::LoadSpecularMaterial(std::string filename)
{
	std::fstream file(filename.c_str(), std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];

	std::string directory(filename);
	int index = directory.rfind('\\');
	if (index != -1) {
		directory = directory.substr(0, index + 1);
	}
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
		else if (line.find("map_Kd") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapKd.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("map_Ks") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapKs.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("bump") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			mapNormal.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("emissiveMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			emissiveMap.LoadFromFile((directory + mapFileName).c_str());
		}
	}
}

void Mesh::LoadPBRMaterial(std::string filename)
{
	std::fstream file(filename.c_str(), std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];

	std::string directory(filename);
	int index = directory.rfind('\\');
	if (index != -1) {
		directory = directory.substr(0, index + 1);
	}
	while (!file.eof()) {
		file.getline(buffer, 256);
		line = buffer;
		std::stringstream ss(line, std::stringstream::in | std::stringstream::out);
		if (line.find("albedo") == 0)
			ss >> header >> albedo.x >> albedo.y >> albedo.z;
		else if (line.find("metallic") == 0)
			ss >> header >> metallic;
		else if (line.find("roughness") == 0)
			ss >> header >> roughness;
		else if (line.find("ao") == 0)
			ss >> header >> ao;
		else if (line.find("albedoMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			albedoMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("normalMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			normalMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("metallicMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			metallicMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("roughnessMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			roughnessMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("aoMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			aoMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("emissiveMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			emissiveMap.LoadFromFile((directory + mapFileName).c_str());
		}
	}
}
void Mesh::LoadPBRMaskMaterial(std::string filename)
{
	std::fstream file(filename.c_str(), std::ios::in);
	std::string line;
	std::string header;
	char buffer[256];

	std::string directory(filename);
	int index = directory.rfind('\\');
	if (index != -1) {
		directory = directory.substr(0, index + 1);
	}
	while (!file.eof()) {
		file.getline(buffer, 256);
		line = buffer;
		std::stringstream ss(line, std::stringstream::in | std::stringstream::out);
		if (line.find("albedo ") == 0)
			ss >> header >> albedo.x >> albedo.y >> albedo.z;
		else if (line.find("metallic") == 0)
			ss >> header >> metallic;
		else if (line.find("roughness") == 0)
			ss >> header >> roughness;
		else if (line.find("ao") == 0)
			ss >> header >> ao;
		else if (line.find("albedoMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			albedoMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("normalMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			normalMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("maskMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			maskMap.LoadFromFile((directory + mapFileName).c_str());
		}
		else if (line.find("emissiveMap") == 0) {
			std::string mapFileName;
			ss >> header >> mapFileName;
			emissiveMap.LoadFromFile((directory + mapFileName).c_str());
		}
	}
}

void Mesh::CalculateTangents(std::vector<Vertex> vertices, unsigned int vertexCount, const std::vector<unsigned int>& indices)
{
	glm::vec4* tan1 = new glm::vec4[vertexCount * 2];
	glm::vec4* tan2 = tan1 + vertexCount;
	memset(tan1, 0, vertexCount * sizeof(glm::vec4) * 2);

	unsigned int indexCount = (unsigned int)indices.size();
	for (unsigned int a = 0; a < indexCount; a += 3) {
		long i1 = indices[a];
		long i2 = indices[a + 1];
		long i3 = indices[a + 2];

		const glm::vec4& v1 = vertices[i1].position;
		const glm::vec4& v2 = vertices[i2].position;
		const glm::vec4& v3 = vertices[i3].position;

		const glm::vec2& w1 = vertices[i1].texCoord;
		const glm::vec2& w2 = vertices[i2].texCoord;
		const glm::vec2& w3 = vertices[i3].texCoord;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0f / (s1 * t2 - s2 * t1);
		glm::vec4 sDir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2), (t2 * z1 - t1 * z2), 0);
		glm::vec4 tDir((s2 * x1 - s1 * x2) * r, (s2 * y1 - s1 * y2), (s2 * z1 - s1 * z2), 0);

		tan1[i1] += sDir;
		tan1[i2] += sDir;
		tan1[i3] += sDir;

		tan2[i1] += tDir;
		tan2[i2] += tDir;
		tan2[i3] += tDir;
	}
	for (unsigned int a = 0; a < vertexCount; a++) {
		const glm::vec3& n = glm::vec3(vertices[a].normal);
		const glm::vec3& t = glm::vec3(tan1[a]);

		vertices[a].tangent = glm::vec4(glm::normalize(t - n * glm::dot(n, t)), 0);
		vertices[a].tangent.w = (glm::dot(glm::cross(glm::vec3(n), glm::vec3(t)), glm::vec3(tan2[a])) < 0.0f) ? 1.0f : -1.0f;
	}
	delete[] tan1;
}



