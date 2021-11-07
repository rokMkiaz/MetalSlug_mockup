#include"IL.hlsli"

cbuffer Transform: register(b0){ matrix World      ;} // romajor �� �켱 ��� ����
cbuffer Transform: register(b1){ matrix View       ;}
cbuffer Transform: register(b2){ matrix Projection ;}




Pixel VS(
const Vertex Input)
{
	Pixel Output =
	{
		Input.Position,
		Input.TexCoord
	};

	Output.Position = mul(Output.Position, World);
	Output.Position = mul(Output.Position, View);
	Output.Position = mul(Output.Position, Projection);
	return	Output;
	
}