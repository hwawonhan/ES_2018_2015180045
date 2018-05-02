#version 330


in vec4 a_Position;
out vec2 f_vec2;

void main()
{
	gl_Position = vec4(a_Position.xyz, 1);
	f_vec2 = a_Position.xy;
}
