#include "fbpch.h"
#include "Core/Core.h"
#include "FileUtils.h"
#include "Application/Log.h"

namespace Fireblast {
	std::string FileUtils::ReadFileContent(const std::string path) {

		std::string content;

		try {

			std::ifstream ifs(path.c_str());
			FB_ASSERT(ifs.is_open(), std::string("File could not open ") + path);

			ifs >> std::noskipws;

			std::string line;

			while (std::getline(ifs, line)) {
				content.append(line);
				content.append("\n");
			}

			ifs.close();
		}
		catch (std::exception const &e) {
			FB_CORE_ERROR("There was an error {0}", e.what());
		}

		return content;
	}

	unsigned char* FileUtils::ReadImageData(const std::string path, unsigned int* width, unsigned int* height)
	{
		int _c;

		unsigned char* _dataPtr = stbi_load(path.c_str(), (int*)width, (int*)height, &_c, 4);

		FB_ASSERT(_dataPtr, "Couldn't load image: " + path);

		return _dataPtr;
	}

	void FileUtils::FlipImages(const bool flip)
	{
		stbi_set_flip_vertically_on_load(flip);
	}

	std::vector<std::string> FileUtils::Split(const std::string& text, char delimiter)
	{
		std::vector<std::string> tokens;

		if (delimiter == ' ' || delimiter == 0x20)
		{
			std::istringstream buf(text);
			std::istream_iterator<std::string> beg(buf), end;

			tokens = std::vector<std::string>(beg, end);
		}
		else
		{
			std::string token;
			std::istringstream tokenStream(text);

			while (std::getline(tokenStream, token, delimiter))
			{
				tokens.push_back(token);
			}
		}

		return tokens;
	}
}