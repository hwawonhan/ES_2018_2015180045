#version 330

uniform float u_Time;

in vec4 a_Position;

out vec2 v_Color;
out float f_Time;

void main()
{
	gl_Position = vec4(a_Position.xyz, 1);
	v_Color = a_Position.xy;
	f_Time = u_Time;
}
