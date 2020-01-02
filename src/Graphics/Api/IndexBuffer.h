#pragma once

namespace Fireblast 
{
	class IndexBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Delete() = 0;
	};
}