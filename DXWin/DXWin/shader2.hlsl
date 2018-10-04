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
 
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
     
    VS_OUTPUT output;
    output.VerPos = mul(Pos, gWVP);
    output.Normal = mul(Normal, gW);
    output.LightPos = gLightPos;
    output.EyePos = gEyePos;
     
    return output;
}

// �s�N�Z���V�F�[�_
float4 PS(VS_OUTPUT input) : SV_Target
{
 
    float4 L = normalize(input.LightPos - input.Normal); // ���̕\�ʏ�̓_��������ւ̕����x�N�g��
    float4 N = normalize(input.Normal); // �\�ʏ�̓_�ɂ�����@��
    float LN = dot(L, N);
    float4 R = normalize(2 * LN * N - normalize(input.LightPos)); // ���������˂�������
    float4 V = normalize(input.EyePos); // ���_�Ɍ���������
    float RV = saturate(dot(R, V));
 
    // �����ˌ�
    float4 ambient = gColor * 0.3;
    // �g�U���ˌ�
    float4 diffuse = saturate(LN * gColor);
    // ���ʔ��ˌ�
    float4 specular = saturate(60.0 * pow(RV, 5.0) * float4(1.0, 1.0, 1.0, 1.0));
 
    return ambient + diffuse + specular;
}