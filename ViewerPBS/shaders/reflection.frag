#version 330

smooth in vec3 w_campos;
smooth in vec3 w_vert;
smooth in vec3 w_normal;

uniform samplerCube specular_map;

out vec4 frag_color;

void main (void) {

    vec3 N = normalize(w_normal);
    vec3 V = normalize(w_campos-w_vert);
    vec3 R = reflect(-V, N);

    vec3 color_specular = texture(specular_map,R).rgb;

    frag_color = vec4(color_specular,1.0);
}
