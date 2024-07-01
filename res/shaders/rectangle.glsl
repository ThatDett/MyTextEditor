//#shader vertex
#version 400 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_projection;
uniform mat4 u_model;

void main()
{
    gl_Position = u_projection * u_model * vec4(aPos, 1.0);
}

//-----------------------------FRAGMENT-----------------------------//
//#shader fragment
out vec4 color;

uniform vec4 u_color;

void main()
{    
    color = u_color;
    // color = vec4(1.0f);
} 