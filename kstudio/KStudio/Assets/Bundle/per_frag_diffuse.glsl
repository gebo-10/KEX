#decl


#vert
#version 310 es
precision highp float;

struct TheStruct
{
  vec3 first;
  vec4 second;
  mat4 third;
};
layout(location = 20)uniform TheStruct uniformArrayOfStructs[10];


layout(std140, binding = 0) uniform Common
{
    vec4 time;
    vec4 light_dir;
    vec4 ligth_color;
    mat4 V;
    mat4 P;
    mat4 PV;
};
layout (location = 0) uniform mat4 M;


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 4) in vec2 uv;


layout(std430, binding = 10) buffer destBuffer
{
    vec4 data[];
} outBuffer;

out vec3 frag_position;
out vec3 normal_lerped;
out vec2 texture_coord;
void main()
{
    vec4 a=uniformArrayOfStructs[0].second;
    vec4 word_pos=M*vec4(position,1.0);
    //word_pos.x=word_pos.x+float(gl_InstanceID-3)*3.0;
    gl_Position = PV*word_pos;
    frag_position=word_pos.xyz;

    vec4 world_normal=M*vec4(normal,1.0);
    normal_lerped = world_normal.xyz;
    texture_coord = uv;
    //outBuffer.data[gl_VertexID]=vec4(position,0.0);
}

//////////////////////////////////////////////////////////////////////////////
#frag
#version 310 es
precision highp float;
layout(std140, binding = 0) uniform Common
{
    vec4 time;
    vec4 light_dir;
    vec4 ligth_color;
    mat4 V;
    mat4 P;
    mat4 PV;
};
layout (location = 1) uniform vec4 c;
layout (binding = 0)  uniform sampler2D texture0;
in vec3 normal_lerped;
in vec3 frag_position;
in vec2 texture_coord;
out vec4 color;

void main()
{
    //vec3 lightPos=vec3(10.0,10.0,10.0);
    //vec3 lightColor=vec3(1.0,1.0,0.0)*1.0;

    vec3 norm = normalize(normal_lerped);
    //vec3 lightDir = normalize(lightPos - frag_position);
    vec3 lightDir = normalize(light_dir.xyz);
    float diff = max(dot(norm, -lightDir), 0.0);
    vec3 diffuse = diff * c.xyz;

    
    //color = vec4(diffuse,1.0f)*0.7+c*0.3;
    color =texture(texture0,texture_coord)*0.5+ vec4(diffuse*sin(time.x*5.0),1.0f);
    //color = c;
   
}