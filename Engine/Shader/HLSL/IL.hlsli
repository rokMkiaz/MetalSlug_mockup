//IL input layout �� ���� ���

struct Vertex
{
	float4 Position : POSITION; // ���ڰ� ���ڸ��Ե����� 0001�� ä������
	float2 TexCoord : TEXCOORD; //Texture Coordinates
};


struct Pixel
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};