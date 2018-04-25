#version 330


in vec4 a_Position;
in vec2 a_TexPos;

out vec2 v_TexPos;

void main()
{
	gl_Position = a_Position;
	v_TexPos = a_TexPos;
}
