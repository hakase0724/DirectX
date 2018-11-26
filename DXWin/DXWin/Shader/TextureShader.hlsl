// 定数バッファ(CPU側からの値受け取り場)
cbuffer global
{
    matrix gWVP;
    float4 gColor;
};
 
Texture2D mTexture : register(t0); //テクスチャー
SamplerState mSampler : register(s0); //サンプラー

// 頂点シェーダから出力される構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TextureUV : TEXCOORD;
};
 
// 頂点シェーダ
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output;
    output.Pos = mul(Pos, gWVP);
    output.TextureUV = Tex;
    return output;
}
 
// ピクセルシェーダ
float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 tex = mTexture.Sample(mSampler, input.TextureUV);
    if (tex.a <= 0)
    {
        discard;
    }
    tex.r *= gColor.r;
    tex.g *= gColor.g;
    tex.b *= gColor.b;
    tex.a *= gColor.a;
    return tex;
}