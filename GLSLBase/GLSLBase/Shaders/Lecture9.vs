#version 330

in vec3 a_Position;
uniform float u_Time;
const float pi = 3.141592;
const vec2 target = vec2(-1, -1);
out float v_Color;

void main()
{
	//인터폴레이션 식
	//x = (1 - time) * A + time *B;
	float newX = a_Position.x;
	float newY = (a_Position.y + sin((newX + 0.5) * 2 * pi - u_Time) * 0.5);
	
	float newTime = fract(1-u_Time/10);
	float newnewX = (1-newTime) * newX + newTime * target.x;
	float newnewY = (1-newTime) * newY + newTime * target.y;
    gl_Position = vec4(newnewX, newnewY, 0, 1.0);
	v_Color = (sin((newX + 0.5) * 2 * pi - u_Time) + 1) / 2;
}
