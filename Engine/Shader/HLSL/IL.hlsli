//IL input layout 을 위한 헤더

struct Vertex
{
	float4 Position : POSITION; // 인자가 모자르게들어오면 0001이 채워진다
	float2 TexCoord : TEXCOORD; //Texture Coordinates
};


struct Pixel
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};