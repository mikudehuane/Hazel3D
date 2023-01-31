#include "hzpch.h"
#include "Model.h"

#include "Hazel/Core/AssetsManager.h"

namespace Hazel {

	void Model::LoadModel(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			HZ_CORE_ERROR("ERROR::ASSIMP::{0}", importer.GetErrorString());
			return;
		}
		m_Directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (uint32_t i = 0; i < node->mNumMeshes; ++i)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));  // TODO(islander): one hard copy here
		}
		
		for (uint32_t i = 0; i < node->mNumChildren; ++i)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Ref<Material> material;

		for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			aiVector3D& aiVertex = mesh->mVertices[i];
			vertex.Position = { aiVertex.x, aiVertex.y, aiVertex.z };
			aiVector3D& aiNormal = mesh->mNormals[i];
			vertex.Normal = { aiNormal.x, aiNormal.y, aiNormal.z };
			if (mesh->mTextureCoords[0])  // has tex coord?
			{
				aiVector3D& aiTexCoord = mesh->mTextureCoords[0][i];
				vertex.TexCoord = { aiTexCoord.x, aiTexCoord.y };
			}
			else
			{
				vertex.TexCoord = { 0.0f, 0.0f };
			}
			vertices.push_back(vertex);
		}
		
		for (uint32_t i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace& face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];
			material = LoadMaterial(aiMaterial);
		}
		
		return Mesh(vertices, indices, material);
	}

	Ref<Material> Model::LoadMaterial(aiMaterial* mat)
	{
		Ref<Material> material = CreateRef<Material>();

		constexpr uint32_t numTexTypes = 2;
		std::array<aiTextureType, numTexTypes> aiTypes = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR };
		std::array<Texture::Type, numTexTypes> types = { Texture::Type::Diffuse, Texture::Type::Specular };

		for (uint32_t TexTypeIdx = 0; TexTypeIdx < numTexTypes; TexTypeIdx++)
		{
			aiTextureType aiType = aiTypes[TexTypeIdx];
			Texture::Type type = types[TexTypeIdx];

			for (uint32_t i = 0; i < mat->GetTextureCount(aiType); i++)
			{
				aiString str;
				mat->GetTexture(aiType, i, &str);
				std::string path = m_Directory + '/' + str.C_Str();
				// TODO(islander): other textures
				// TODO(islander): name as key for efficiency?
				Ref<Texture2D> texture = std::dynamic_pointer_cast<Texture2D>(AssetsManager::LoadTexture(path, str.C_Str()));
				material->SetTextureMap(texture, type);  // TODO(islander): add instead of set
			}
		}
		return material;
	}

}
