cbuffer global
{
    float4x4 gWVP;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

struct VS_INPUT
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.pos = mul(input.pos, gWVP);
    output.color = input.color;
    return output;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.color;
};