#include"IL.hlsli"

Texture2D Texture : register(T0); //레지스터는 순서를 뜻함

float4 PS(const Pixel Input) : SV_TARGET
{
	const float4 Output =
	{
		Texture.Load(int3(Input.TexCoord, 0)) //몇번 min맵에서 가져올지
	};
	
	if (Output.a!=1)
		discard;
	
	return Output;
}
