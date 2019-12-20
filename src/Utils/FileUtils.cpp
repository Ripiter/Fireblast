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
}