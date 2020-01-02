#pragma once

namespace Fireblast 
{
	enum class RenderPrimitives 
	{
		Triangles,
		Traingles_Strip,
		Quads
	};

	enum class BufferUsage
	{
		Static_Draw,
		Dynamic_Draw
	};

	enum class ShaderType 
	{
		Float,
		Int
	};
}