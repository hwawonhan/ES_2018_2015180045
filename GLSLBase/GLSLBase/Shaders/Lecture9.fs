#version 330

out vec4 FragColor;
in float v_Color;


void main()
{
    FragColor = vec4(v_Color);
}
