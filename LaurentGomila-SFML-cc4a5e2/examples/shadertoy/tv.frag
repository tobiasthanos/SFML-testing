uniform float times;
uniform vec2 resolution;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
    //screen coordinates
    vec2 p = -1.0 +2.0 * gl_FragCoord.xy / resolution.xy;

float cout;

if( modf( gl_FragCoord.y , 2)==0)
{
cout = 1.0;
}
else
{
cout = 0.0;
}

    //set the output color
    gl_FragColor = vec4(cout,cout,cout,1);
}







