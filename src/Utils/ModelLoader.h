#pragma once
#include "glm/glm.hpp"
#include <string>

namespace Fireblast { namespace Mesh {
		
	struct MeshFileFormat
	{
		bool IsTriangilized;

		glm::vec3* Vertices;
		glm::vec2* TextureVertices;
		glm::vec3* VerticeNormals;
		unsigned int* Indicies;
	};

	class BaseMeshLoader
	{
	private:
		std::string m_RawFileData;
	protected:
		BaseMeshLoader() {};
		virtual ~BaseMeshLoader() {}

		void SetFileData(std::string& data) { m_RawFileData = data; }
		virtual MeshFileFormat* FormatData() = 0;
	};

	class OBJMeshLoader : public BaseMeshLoader
	{
	private:
		MeshFileFormat* m_Data;
	public:
		OBJMeshLoader() 
			: m_Data(nullptr) {};
		virtual ~OBJMeshLoader() { delete m_Data; }

	private:
		bool IsLineVertices() {};
		bool IsLineTextureVertices() {};
		bool IsLineVerticeNormals() {};
		bool IsLineIndicieLine() {};
	protected:
		virtual MeshFileFormat* FormatData() override {};
	};

	class ModelFileLoader
	{

	};
}}