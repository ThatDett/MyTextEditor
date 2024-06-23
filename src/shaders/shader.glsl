#shader vertex
#version 400 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.xyz, 1.0);
}

//-----------------------------FRAGMENT-----------------------------//
#shader fragment
#version 400 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}