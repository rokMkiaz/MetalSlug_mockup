

struct Vertex
{
	float4 Position : POSITION; 
	float2 TexCoord : TEXCOORD; 
};


struct Pixel
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};
