#version 330 core

out vec4 color;

//in vec4 vertexColor;
uniform vec4 ourColor;

void main()
{
    color = ourColor;
    //color = vertexColor;
}