#version 330

smooth in vec3 w_campos;
smooth in vec3 w_vert;
smooth in vec3 w_normal;

uniform samplerCube specular_map;
uniform samplerCube diffuse_map;
uniform sampler2D brdf_lut_map;
uniform vec3    lightDir;
uniform vec3 fresnel;
uniform float	roughness;
uniform vec3	diffuseColor;
uniform float   metallic;

out vec4 FragColor;

const float PI = 3.14159265359;

float Distribution(vec3 N, vec3 H, float roughness)
{
    float a2 = roughness*roughness;
    float NdotH = max(dot(N, H),0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

void main (void) {

    vec3 N = normalize(w_normal);
    vec3 V = normalize(w_campos-w_vert);
    vec3 R = reflect(-V, N);

    vec3 F0 = mix(fresnel, diffuseColor, metallic);

    vec3 L = normalize(w_vert-lightDir);
    vec3 H = normalize(V + L);
    vec3 radiance = vec3(1,1,1);

    float D = Distribution(N, H, roughness);
    vec3 F    = fresnelSchlick(max(dot(H, V), 0), F0);
    vec3 specular = D*F/4;

    vec3 kS = F;

    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 -metallic;

    float NdotL = max(dot(N, L), 0.0);

    vec3 Lo = (kD * diffuseColor / PI + specular) * radiance * NdotL;


    // ambient lighting (we now use IBL as the ambient term)
    vec3 akS = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0,roughness);
    vec3 akD = 1.0 - akS;
    akD *= 1.0 -metallic;

    vec3 irradiance = texture(diffuse_map, N).rgb;
    vec3 adiffuse = irradiance * diffuseColor;

    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(specular_map, R,roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdf_lut_map, vec2(max(dot(N, V), 0.0), roughness)).rg;


    vec3 aspecular = prefilteredColor* (akS* brdf.x + brdf.y);
    vec3 ambient = (akD * adiffuse+aspecular);
    //end ambient



    vec3 color = ambient + Lo;
    FragColor = vec4(color, 1.0);

}
