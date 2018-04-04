#version 330

uniform float u_Time;
in vec4 a_Position;

out vec2 v_FragPos;

void main()
{
	/*
	float term = (a_Position.x - 1)/2;
	float yValue = sin(u_Time + a_Position.x * (3.141592*2) / (term - 1));
	gl_Position = vec4(a_Position.x, yValue, a_Position.z, 1);
	*/
	gl_Position = vec4(a_Position.xyz, 1);
	v_FragPos = a_Position.xy;
}
