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

out vec3 ourColor;
void main()
{
    //vec3 dir=vec3(light_dir.x, light_dir.y, light_dir.z);
    vec3 dir=normalize(vec3(1.0f, 1.0f, 1.0f));
    vec3 n=vec3( (M*vec4(normal,1.0f) ).xyz);
    n=normalize(n);
    float cos = max(dot(dir, n), 0.0f);
    vec3 diffuse = vec3(ligth_color.x, ligth_color.y, ligth_color.z)*cos;
    ourColor = diffuse;
    //ourColor=color;
    gl_Position = PV*M*vec4(position, 1.0f);
}


#frag
#version 310 es
precision highp float;
in vec3 ourColor;
out vec4 color;
layout (location = 1) uniform vec4 c;
void main()
{
    color = vec4(ourColor,1.0f);
    //color = c;
}