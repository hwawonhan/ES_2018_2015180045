#version 330

in vec4 a_Position;
in float a_Scale;
in vec4 a_Color;

out vec4 v_Color;

uniform float u_Scale;

void main()
{
	gl_Position = vec4(a_Position.xyz,1);
	v_Color = vec4(a_Position.w, 0, 0, 1);
}
