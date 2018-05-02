#version 330

layout(location=0) out vec4 FragColor;

uniform float u_Time;
uniform vec3 u_Points[4];

in vec2 v_Color;

void main()
{
    
    float pointColor = 0;

    for(int i = 0; i < 4; ++i)
    {
        vec2 segment = u_Points[i].xy - v_Color;
        float r = 1 - length(segment);
        if( r > 0.95 )
        {
            r = 0.8;
        }
        else
        {
            r = 0;
        }
        pointColor += r;
    }


    float finalColor = 0;
    float temp = length(v_Color);
    float newTime = fract(u_Time); //0~1
    if(newTime + 0.02 > temp && newTime - 0.02 < temp)
    {
        finalColor = 0.4 * pointColor + 0.2;
    }

    if(finalColor == 0)
        discard;
   
    FragColor = vec4(finalColor, finalColor, finalColor, 1);
}


 