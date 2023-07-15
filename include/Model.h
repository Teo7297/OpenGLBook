#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <Mesh.h>

using namespace std;


class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);

private:
	// model data
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int TextureFromFile(const char* path, const string& directory);
};