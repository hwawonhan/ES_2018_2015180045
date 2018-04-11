#version 330

uniform float u_Time;
uniform float u_Ratio;
uniform float u_Width;
uniform vec2 u_startPoint;
uniform vec2 u_endPoint;

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
	float pi = 3.141592;

	float temp = u_Time + 1;

	vec2 dir = u_endPoint - u_startPoint;

	mat2 rot = mat2(cos(pi/2), -sin(pi/2), sin(pi/2), cos(pi/2));
	
	vec2 tempVec = normalize(rot * dir);

	if (temp > a_Position.x)
	{
		float newTime = temp - a_Position.x;
		newTime = fract(newTime / 2) * 2;
		float temp2 = sin((newTime + a_Position.w) * 3.141592 * u_Ratio) * (u_Width * a_Position.w * ((newTime)/2));
		tempVec = tempVec * temp2;

		PosX = u_startPoint.x + dir.x  * newTime / 2 + tempVec.x;
		PosY = u_startPoint.y + dir.y  * newTime / 2 + tempVec.y;
	}
	else {

	}
	
	gl_Position = vec4(PosX, PosY, a_Position.z, 1);
	v_FragPos = a_Position.xy;
}
