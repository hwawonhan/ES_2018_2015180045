#version 330

in vec2 vTexPos;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    //������
    //float tX = vTexPos.x * 0.5;
    //float tY = vTexPos.y * 0.5 + 0.5;
    //��������
    //float tX = vTexPos.x * 0.5 + 0.5;
    //float tY = vTexPos.y * 0.5 + 0.5;
    //��©���� ���
    //float tX = fract(vTexPos.x * 2);
    //float tY = (1 - floor(vTexPos.x * 2)) * 0.5 + vTexPos.y * 0.5;
    //3��� ���
    float tX = fract(vTexPos.x * 3);
    float tY = (2 - floor(vTexPos.x * 3)) / 3 + vTexPos.y / 3;
    FragColor = texture(uTexture, vec2(tX,tY));
}



 