#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    vec2 texPos = gl_PointCoord;

    FragColor = texture(u_Texture, texPos);
    //FragColor = vec4(gl_PointCoord, 0, 1);

}


 