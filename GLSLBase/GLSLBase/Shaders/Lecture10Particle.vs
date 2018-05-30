#version 330

in vec3 Position;
in vec2 TexPos;
in vec4 Velocity;

const vec3 c_Gravity = vec3(-1, -2, 0);

uniform float uTime;

out vec2 vTexPos;
out float vAlpa;

void main()
{
	vec3 newPosition = vec3(-1000,-1000,-10000);
	float newTime = uTime - Velocity.w;
	vAlpa = 1;
	if(newTime > 0)
	{
		newTime = fract(newTime/1) * 1;
		vAlpa = fract(newTime/1);

		newPosition = Position + newTime * Velocity.xyz + 0.5 * c_Gravity * newTime * newTime;
	}
    gl_Position = vec4(newPosition, 1.0);
	vTexPos = TexPos;
}
