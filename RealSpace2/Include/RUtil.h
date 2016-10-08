#pragma once

#include "RealSpace2.h"
#include "MUtil.h"
#include <type_traits>

using ShaderPair = std::pair<D3DPtr<IDirect3DVertexShader9>, D3DPtr<IDirect3DPixelShader9>>;
using ShaderRefPair = std::pair<const D3DPtr<IDirect3DVertexShader9>&, const D3DPtr<IDirect3DPixelShader9>&>;

inline void DisableShaders()
{
	RGetDevice()->SetVertexShader(nullptr);
	RGetDevice()->SetPixelShader(nullptr);
}

inline ShaderPair SaveAndDisableShaders()
{
	D3DPtr<IDirect3DVertexShader9> PrevVS;
	RGetDevice()->GetVertexShader(MakeWriteProxy(PrevVS));
	D3DPtr<IDirect3DPixelShader9> PrevPS;
	RGetDevice()->GetPixelShader(MakeWriteProxy(PrevPS));

	DisableShaders();

	return{ std::move(PrevVS), std::move(PrevPS) };
}

inline void SetShaders(const ShaderPair& Shaders)
{
	RGetDevice()->SetVertexShader(Shaders.first.get());
	RGetDevice()->SetPixelShader(Shaders.second.get());
}

inline void SetShaders(const ShaderRefPair& Shaders)
{
	RGetDevice()->SetVertexShader(Shaders.first.get());
	RGetDevice()->SetPixelShader(Shaders.second.get());
}