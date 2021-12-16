#vert
#version 310 es
precision highp float;

layout(std140, binding = 0) uniform Common
{
	vec4 time;
	vec4 light_dir;
	vec4 light_color;
	mat4 V;
	mat4 P;
	mat4 PV;
};
layout (location = 0) uniform mat4 M;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 4) in vec2 uv;


out vec3 frag_position;
out vec3 normal_lerped;
out vec2 texture_coord;

void main()
{
	gl_Position = vec4(position,1.0);
	texture_coord = uv;
}

//////////////////////////////////////////////////////////////////////////////
#frag
#version 310 es
precision highp float;
layout(std140, binding = 0) uniform Common
{
	vec4 time;
	vec4 light_dir;
	vec4 light_color;
	mat4 V;
	mat4 P;
	mat4 PV;
};


layout (location = 1)	uniform float 		texture_width;
layout (location = 2)	uniform float 		texture_height;

layout (location = 3)	uniform vec2 		blur_dir;
layout (location = 4)	uniform float 		blur_radius;

layout (binding = 0)	uniform sampler2D 	texture0;

layout (location = 0) 	out 	vec4 		color;

in vec2 texture_coord;

vec4 gaussianBlur( vec2 coord,  vec2 dir)
{

    // Defines the one-dimensional Gaussian Kernel with 9 samples.
    float GAUSSIAN_KERNEL[9];
    GAUSSIAN_KERNEL[0] = 0.028532;
    GAUSSIAN_KERNEL[1] = 0.067234;
    GAUSSIAN_KERNEL[2] = 0.124009;
    GAUSSIAN_KERNEL[3] = 0.179044;
    GAUSSIAN_KERNEL[4] = 0.20236;
    GAUSSIAN_KERNEL[5] = 0.179044;
    GAUSSIAN_KERNEL[6] = 0.124009;
    GAUSSIAN_KERNEL[7] = 0.067234;
    GAUSSIAN_KERNEL[8] = 0.028532;

    vec2 texel = vec2(1.0/texture_width, 1.0/texture_height);
    vec4 sum = vec4(0.0);
    // Get the original texture coordinate for this fragment.
    vec2 tc = coord;
    // Get the amount to blur.
    float blur = blur_radius;
    // Set the amount of blur in the horizontal direction.
    float hstep = dir.x*texel.x;
    // Set the amount of blur in the vertical direction.
    float vstep = dir.y*texel.y;
    
    // Sample the texture 9 times for every fragment.
    for(int i = 0; i < 9; i++)
    {
        float pixelOffset = (float(i) - floor(9.0 * 0.5));
         vec2 coord = vec2(tc.x + pixelOffset * blur * hstep, tc.y + pixelOffset * blur * vstep);
        sum += texture(texture0, coord) * GAUSSIAN_KERNEL[i];
    }

    return sum;
}

void main()
{
    color = gaussianBlur(texture_coord, blur_dir) ;
    //gl_FragColor =texture(texture0, texture_coord);
    color.a=1.0;
}

//////////////////////////////////////////////////////////////////////////////
#decl
return{
	{
		name="M",
		location = 0,
		type=ShaderDataType.MAT4,
		value={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	},
	{
		name="texture_width",
		location = 1,
		type=ShaderDataType.FLOAT,
		value={1024}
	},
	{
		name="texture_height",
		location = 2,
		type=ShaderDataType.FLOAT,
		value={1024}
	},
	{
		name="blur_dir",
		location = 3,
		type=ShaderDataType.VEC2,
		value={0,0}
	},
	{
		name="blur_radius",
		location = 4,
		type=ShaderDataType.FLOAT,
		value={2}
	}
}
