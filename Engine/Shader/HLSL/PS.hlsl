#include"IL.hlsli"

Texture2D Texture : register(T0); 

float4 PS(const Pixel Input) : SV_TARGET
{
	const float4 Output =
	{
		Texture.Load(int3(Input.TexCoord, 0)) 
	};
	
	if (Output.a!=1)
		discard;
	
	return Output;
}
