#pragma once
#include "glm/glm.hpp"
#include "Graphics/Vertice.h"
#include "Core/Core.h"
#include "FileUtils.h"

#include <string>
#include <fstream>
#include <iostream>

namespace Fireblast { namespace Utils {
	
	struct MeshFileInfo
	{
		std::string Name;
		std::vector<Vertex3D> Vertices;
		std::vector<int> Indicies;
		bool IsTriangilized;

		MeshFileInfo() : IsTriangilized(false), Vertices(), Indicies() {};
		~MeshFileInfo() 
		{
		}
	};

	class FileLoader
	{
	private:
		std::string m_Path;
		std::string m_Content;
	public:
		FileLoader()
			: m_Path(),  m_Content() 
		{};

		~FileLoader() {};
	private:
		inline std::string ReadContent(const std::string& path)
		{
			std::stringstream content;

			std::ifstream fileStream(path);
			FB_ASSERT(fileStream.is_open(), "Could not open filestream to read content");
			content << fileStream.rdbuf();

			return content.str();
		}

		inline void WriteContent(const std::string& path, const std::string& content)
		{
			std::ofstream stream;
			stream.open(path);
			FB_ASSERT(stream.is_open(), "Could not open path for stream to write");

			stream << content;
			stream.flush();
			stream.close();
		}

	public:
		inline void LoadFile(const std::string& path)
		{
			m_Path = path;
		}

		inline void ReadContent()
		{
			m_Content = ReadContent(m_Path);
		}

		inline void WriteToFile(const std::string& content)
		{
			m_Content = content;
			WriteContent(m_Path, m_Content);
		}

		inline void AppendToFile(const std::string& content)
		{
			m_Content += content;
			WriteContent(m_Path, m_Content);
		}

		inline const std::string& GetContent() const { return m_Content; }
	};

	class BaseMeshLoader
	{
	private:
		std::string m_TextData;
	public:
		BaseMeshLoader() : m_TextData("") {};
		virtual ~BaseMeshLoader() {};

	protected:
		const std::string& GetTextData() const { return m_TextData; }
	public:
		virtual MeshFileInfo* ConvertToMeshFileInfo() = 0;
		void SetTextData(const std::string& data) { m_TextData = data; }
	};

	class OBJFileLoader : public BaseMeshLoader
	{
	public:
		OBJFileLoader() : BaseMeshLoader() {}
		virtual ~OBJFileLoader() override = default;

	private:
		struct OBJFormat
		{
			unsigned int IndiciesPerPrimitive;
			std::string Name;

			std::vector<float> Vertices;
			std::vector<float> VerticeNormals;
			std::vector<float> VerticeTextures;
			std::vector<int> Indicies;
		};

		OBJFormat* TextToOBJFormat(const std::vector<std::string>& lines) 
		{
			OBJFormat* data = new OBJFormat();

			for (unsigned int i = 0; i < lines.size(); i++)
			{
				std::vector<std::string>& tokens = FileUtils::Split(lines[i], ' ');

				if (IsLineNullOrWhiteSpace(tokens))
					continue;

				if (IsLineVerticeLine(tokens))
				{
					data->Vertices.push_back((float)::atof(tokens[1].c_str()));
					data->Vertices.push_back((float)::atof(tokens[2].c_str()));
					data->Vertices.push_back((float)::atof(tokens[3].c_str()));
				}

				if (IsLineVerticeNormalLine(tokens))
				{
					data->VerticeNormals.push_back((float)::atof(tokens[1].c_str()));
					data->VerticeNormals.push_back((float)::atof(tokens[2].c_str()));
					data->VerticeNormals.push_back((float)::atof(tokens[3].c_str()));
				}

				if (IsLineVerticeTextureLine(tokens))
				{
					data->VerticeTextures.push_back((float)::atof(tokens[1].c_str()));
					data->VerticeTextures.push_back((float)::atof(tokens[2].c_str()));
				}

				if (IsLineIndicieLine(tokens))
				{
					for (unsigned int i = 0; i < tokens.size()-1; i++)
					{
						data->IndiciesPerPrimitive = tokens.size() - 1;
						std::vector<std::string>& faces = FileUtils::Split(tokens[i + 1], '/');

						for (unsigned int q = 0; q < 3; q++)
						{
							data->Indicies.push_back(std::stoi(faces[q]));
						}
					}
				}

				if (IsLineNameLine(tokens))
					data->Name = tokens[1];

			}

			return data;
		}

		MeshFileInfo* OBJToMeshFormat(const OBJFormat& data) 
		{ 
			MeshFileInfo* meshData		= new MeshFileInfo();
			unsigned int _verticeSize	= data.Indicies.size() / data.IndiciesPerPrimitive;
			
			meshData->IsTriangilized	= (data.IndiciesPerPrimitive == 3) ? true : false;
			meshData->Name				= data.Name;

			for (unsigned int i = 0; i < data.Indicies.size(); i += data.IndiciesPerPrimitive)
			{
				int curVerticePosition			= (data.Indicies[i] - 1) * 3;
				int curVerticeTexturePosition	= (data.Indicies[i+1] - 1) * 2;
				int curVerticeNormalPosition	= (data.Indicies[i+2] - 1) * 3;

				glm::vec3 _curVertice(data.Vertices[curVerticePosition], data.Vertices[curVerticePosition + 1], data.Vertices[curVerticePosition + 2]);
				glm::vec2 _curTextureCoord(data.VerticeTextures[curVerticeTexturePosition], data.VerticeTextures[curVerticeTexturePosition + 1]);
				glm::vec3 _curNormal(data.VerticeNormals[curVerticeNormalPosition], data.VerticeNormals[curVerticeNormalPosition + 1], data.VerticeNormals[curVerticeNormalPosition + 2]);

				Vertex3D vertex				= Vertex3D();
				vertex.Vertice				= _curVertice;
				vertex.TextureCoordination	= _curTextureCoord;
				vertex.Normal				= _curNormal;

				meshData->Vertices.push_back(vertex);
			}

			return meshData;
		}

		const bool IsLineNullOrWhiteSpace(const std::vector<std::string>& tokens)
		{
			return (tokens.size() == 0 || tokens[0] == " ");
		}

		const bool IsLineVerticeLine(const std::vector<std::string>& tokens)
		{
			return (tokens.size() == 4 && tokens[0] == "v");
		}

		const bool IsLineVerticeNormalLine(const std::vector<std::string>& tokens)
		{
			return (tokens.size() == 4 && tokens[0] == "vn");
		}

		const bool IsLineVerticeTextureLine(const std::vector<std::string>& tokens)
		{
			return (tokens.size() == 3 && tokens[0] == "vt");
		}

		const bool IsLineIndicieLine(const std::vector<std::string>& tokens)
		{
			return (tokens.size() >= 4 && tokens[0] == "f");
		}

		const bool IsLineNameLine(const std::vector<std::string>& tokens)
		{
			return (tokens.size() == 2 && tokens[0] == "o");
		}

	public:
		virtual MeshFileInfo* ConvertToMeshFileInfo() override
		{
			const std::string& textData		= GetTextData();
			std::vector<std::string>& lines	= FileUtils::Split(textData, '\n');
			OBJFormat* formatData			= TextToOBJFormat(lines);
			MeshFileInfo* meshData			= OBJToMeshFormat(*formatData);

			delete formatData;
			return meshData;
		};
	};

	class MeshLoader
	{
	private:
		MeshFileInfo* m_MeshInfo;
		FileLoader* m_FileLoader;
		BaseMeshLoader* m_BaseMeshLoader;
	public:
		MeshLoader() : m_MeshInfo(new MeshFileInfo()), m_FileLoader(new FileLoader()), m_BaseMeshLoader(nullptr) {}
		~MeshLoader() { delete m_MeshInfo; delete m_FileLoader; delete m_BaseMeshLoader; }
	private:
		BaseMeshLoader* GetCorrectMeshLoader()
		{
			return new OBJFileLoader();
		}
	public:
		inline bool LoadFile(const std::string& path)
		{
			m_FileLoader->LoadFile(path);
			m_FileLoader->ReadContent();

			m_BaseMeshLoader = GetCorrectMeshLoader();
			m_BaseMeshLoader->SetTextData(m_FileLoader->GetContent());

			m_MeshInfo = m_BaseMeshLoader->ConvertToMeshFileInfo();

			return true;
		}
		const MeshFileInfo* GetMeshData() const { return m_MeshInfo; }
	};
}}