#pragma once
#include <string>

namespace Fireblast {
	class Shader 
	{
	public:
		inline Shader(const char* vertexSource, const char* fragmentSource) {};
		inline virtual ~Shader() {};
	public:
		virtual void Bind() = 0;
		virtual void Delete() = 0;
	protected:
		virtual void GetUniformLocation(const char* name) = 0;
	};
}