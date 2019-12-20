#pragma once
#include <string>

namespace Fireblast {
	class FileUtils {
	public:
		static std::string ReadFileContent(const std::string path);
	};
}