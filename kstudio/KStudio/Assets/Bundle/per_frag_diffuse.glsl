#decl


#vert
#version 310 es
precision highp float;

layout(std140, binding = 0) uniform Common
{
    vec4 light_dir;
    vec4 ligth_color;
    mat4 V;
    mat4 P;
    mat4 PV;
    //float time; error
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

layout (location = 0) uniform mat4 M;

out vec3 frag_position;
out vec3 normal_lerped;
void main()
{
    vec4 word_pos=M*vec4(position,1.0);
    gl_Position = PV*word_pos;
    frag_position=word_pos.xyz;

    vec4 world_normal=M*vec4(normal,1.0);
    normal_lerped = world_normal.xyz;
}


#frag
#version 310 es
precision highp float;
layout(std140, binding = 0) uniform Common
{
    vec4 light_dir;
    vec4 ligth_color;
    mat4 V;
    mat4 P;
    mat4 PV;
    //float time; error
};
layout (location = 1) uniform vec4 c;
in vec3 normal_lerped;
in vec3 frag_position;
out vec4 color;

void main()
{
    //vec3 lightPos=vec3(10.0,10.0,10.0);
    //vec3 lightColor=vec3(1.0,1.0,0.0)*1.0;

    vec3 norm = normalize(normal_lerped);
    //vec3 lightDir = normalize(lightPos - frag_position);
    vec3 lightDir = normalize(light_dir.xyz);
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * ligth_color.xyz;

    
    color = vec4(diffuse,1.0f)*0.7+c*0.3;
    //color = c;
}