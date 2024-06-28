//#shader vertex
#version 400 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_projection;
uniform mat4 u_model;
uniform int u_width;
uniform int u_height;

void main()
{
    gl_Position = u_projection * u_model * vec4(aPos, 1.0);
}

//-----------------------------FRAGMENT-----------------------------//
//#shader fragment
out vec4 color;

void main()
{    
    color = vec4(1.0);
} 