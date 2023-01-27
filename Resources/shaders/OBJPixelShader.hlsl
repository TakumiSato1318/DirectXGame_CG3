#include "OBJShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{ 	//テクスチャマッピング
	float4 texcolor = tex.Sample(smp,input.uv);

	float4 shadercolor;
	const float shininess=4.0f;
	float3 eyedir=normalize(cameraPos-input.worldpos.xyz);
	float3 dotlightnormal=dot(lightv,input.normal);
	float3 reflect=normalize(-lightv+2*dotlightnormal*input.normal);
	float3 ambient=m_ambient;
	float3 diffuse=dotlightnormal*m_diffuse;
	float3 specular=pow(saturate(dot(reflect,eyedir)),shininess)*m_specular;
	shadercolor.rgb=(ambient+diffuse+specular)*lightcolor;
	shadercolor.a=m_alpha;	

	return shadercolor*texcolor;
}