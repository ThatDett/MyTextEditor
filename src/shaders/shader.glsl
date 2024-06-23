#shader vertex
#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 v_color;

//uniform float u_offset;

void main()
{
    gl_Position = vec4(aPos.xyz, 1.0);
    v_color = aColor;
}

//-----------------------------FRAGMENT-----------------------------//
#shader fragment
#version 400 core

out vec4 FragColor;
in vec3 v_color;

void main()
{
    FragColor = vec4(v_color, 1.0f);
}