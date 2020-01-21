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
		bool IsTriangilized;
		Vertex3D* Vertices;
		int* Indicies;
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
		FileLoader* m_FileLoader;
		MeshFileInfo* m_MeshInfo;
	public:
		BaseMeshLoader()
			: m_FileLoader(new FileLoader()), m_MeshInfo(new MeshFileInfo()) {}
		virtual ~BaseMeshLoader() { delete m_FileLoader; delete m_MeshInfo; }
	protected:
		virtual const bool IsFileCorrectFileFormat() = 0;
		virtual void FormatFileData() = 0;
		
	protected:
		const MeshFileInfo* GetMeshInfo() { return m_MeshInfo; }
		const FileLoader* GetFileLoader() { return m_FileLoader; }

	public:
		void LoadFile(const std::string& path)
		{
			m_FileLoader->LoadFile(path);
			m_FileLoader->ReadContent();
		};
	};

	class ObjMeshLoader
		: public BaseMeshLoader
	{
	private:
		const char m_Delimiter = 0x20; // space

	public:
		ObjMeshLoader() 
			: BaseMeshLoader() {}
	private:
		const bool IsLineAComment(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens[0] == "#");
		};

		const bool IsLineAVertice(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens.size() == 4 && tokens[0] == "v");
		};

		const bool IsLineAVerticeTexture(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens.size() == 4 && tokens[0] == "vt");
		};

		const bool IsLineAVerticeNormal(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens.size() == 4 && tokens[0] == "vn");
		};

		const bool IsLineAFace(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens.size() == 5 && tokens[0] == "f");
		};

		const bool IsLineAGroupName(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens[0] == "g");
		};

		const bool IsLineAMaterial(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens[0] == "usemtl");
		};

		const bool IsLineASmoothingGroup(const std::string& line) 
		{
			std::vector<std::string> tokens = FileUtils::Split(line, m_Delimiter);

			return (tokens[0] == "s");
		};

	protected:
		virtual const bool IsFileCorrectFileFormat() override 
		{
			std::vector<std::string> lines = FileUtils::Split(GetFileLoader()->GetContent(), '\n');

			for (unsigned int i = 0; i < lines.size(); i++)
			{
				std::vector<std::string> lineCommands = FileUtils::Split(lines[i], m_Delimiter);

				if (lineCommands.size() != 0)
					FB_CORE_INFO("command {0} Size {1}", lineCommands[0], lineCommands.size());
			}

			return false;
		};

		virtual void FormatFileData() override 
		{
			
		};

	public:
		bool TestMethod() { return IsFileCorrectFileFormat(); };
	};
}}