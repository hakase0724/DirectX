cbuffer global
{
	matrix gWVP;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

VS_OUTPUT VS(float4 pos:POSITION,float4 color:COLOR)
{
    VS_OUTPUT output;
    output.pos = mul(pos, gWVP);
    output.color = color;
    return output;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
};