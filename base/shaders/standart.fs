#version 330 core

in vec3 ourColor;
out vec4 color;
//in vec4 vertexColor;
uniform float timer;

void main()
{
    color = vec4(ourColor*timer, 1.0f);
    //color = vertexColor;
}