#version 330

uniform float u_Time;
uniform float u_Ratio;
uniform float u_Width;

in vec4 a_Position;

out vec2 v_FragPos;

void main()
{
	/*
	float term = (a_Position.x - 1)/2;
	float yValue = sin(u_Time + a_Position.x * (3.141592*2) / (term - 1));
	gl_Position = vec4(a_Position.x, yValue, a_Position.z, 1);
	*/
	//gl_Position = vec4(a_Position.xyz, 1);
	//v_FragPos = a_Position.xy;

	float PosX = -10;
	float PosY = -10;


	float temp = u_Time + 1;

	if (temp > a_Position.x)
	{
		float newTime = temp - a_Position.x;
		newTime = fract(newTime / 2) * 2;
		PosX = newTime - 1;
		PosY = sin((newTime + a_Position.w) * 3.141592 * u_Ratio)
		* (u_Width * a_Position.w * ((newTime)/2));
	}
	else {

	}
	gl_Position = vec4(PosX, PosY, a_Position.z, 1);
	v_FragPos = a_Position.xy;
}
