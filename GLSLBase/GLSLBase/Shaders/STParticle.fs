#version 330

layout(location=0) out vec4 FragColor;

in vec4 v_Color;

void main()
{
    FragColor = vec4(v_Color.xyz, 0.5);

}


 