cbuffer global
{
    matrix gW;
    matrix gWVP;
    float4 gLightPos;
    float4 gEyePos;
    float4 gColor;
};
 
struct VS_OUTPUT
{
    float4 VerPos : SV_POSITION;
    float4 LightPos : TEXCOORD0;
    float4 Normal : TEXCOORD1;
    float4 EyePos : TEXCOORD2;
};
 
struct VS_INPUT
{
    float4 pos : POSITION;
    float4 Normal : NORMAL;
};


VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.VerPos = mul(input.pos, gWVP);
    output.Normal = mul(input.Normal, gW);
    output.LightPos = gLightPos;
    output.EyePos = gEyePos;
     
    return output;
}

// ピクセルシェーダ
float4 PS(VS_OUTPUT input) : SV_Target
{
    return gColor;
}