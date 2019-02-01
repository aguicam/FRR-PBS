#version 330 core
out vec4 FragColor;

in vec3 w_vert;
in vec3 w_normal;
in vec3 w_campos ;

// material parameters
uniform vec3 diffuseColor;
uniform float roughness;
uniform vec3 fresnel;
uniform mat4 view;
// IBL
uniform samplerCube diffuse_map;
uniform samplerCube specular_map;

// lights
uniform vec3 lightColor;
uniform vec3 lightDir;

const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a2 = roughness*roughness;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------

void main()
{

vec3 L=normalize(w_vert-vec3(0,-1,-0.5));


vec3 N = normalize(w_normal);
vec3 V = normalize(w_campos - w_vert);
vec3 R = reflect(-V,N);
//vec3 L = normalize(-lightDir);
vec3 H = normalize(L+V);



vec3 F = fresnelSchlick(max(dot(N,L),0.0),fresnel);
float D = DistributionGGX(N,H,roughness);
vec3 Lo = F*D/4;

F = fresnelSchlickRoughness(max(dot(H,L),0.0),fresnel,roughness);
vec3 irradiance = F*texture(diffuse_map, N).rgb;
vec3 spec = 1+(1-roughness)*texture(specular_map, R).rgb;

vec3 color = irradiance*spec+Lo;
FragColor = vec4(color,1.0);
}
