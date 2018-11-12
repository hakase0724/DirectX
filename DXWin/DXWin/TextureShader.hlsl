// �萔�o�b�t�@(CPU������̒l�󂯎���)
cbuffer global
{
    matrix gWVP;
    float4 gColor;
};
 
Texture2D mTexture : register(t0); //�e�N�X�`���[
SamplerState mSampler : register(s0); //�T���v���[

// ���_�V�F�[�_����o�͂����\����
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 TextureUV : TEXCOORD;
};
 
// ���_�V�F�[�_
VS_OUTPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD)
{
    VS_OUTPUT output;
    output.Pos = mul(Pos, gWVP);
    output.TextureUV = Tex;
    return output;
}
 
// �s�N�Z���V�F�[�_
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