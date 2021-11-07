#include"IL.hlsli"

Texture2D Texture : register(T0); //�������ʹ� ������ ����

float4 PS(const Pixel Input) : SV_TARGET
{
	const float4 Output =
	{
		Texture.Load(int3(Input.TexCoord, 0)) //��� min�ʿ��� ��������
	};
	
	if (Output.a!=1)
		discard;
	
	return Output;
}
