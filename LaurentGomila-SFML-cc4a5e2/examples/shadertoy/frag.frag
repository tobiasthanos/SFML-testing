uniform float times;
uniform vec2 resolution;
uniform vec2 mouse;

#define num 3

vec2 points[num];
float rs[num];

float fakebeat = pow(abs(sin(times*4)),50);

//seed.x = 13*gl_fragCoord.x;
//seed.y = 4.7*gl_fragCoord.y;
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
//note to self: DO NOT CREATE INFINITE LOOPS
    //screen coordinates
    vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
   float metaball = 0;
   
   vec2 mblob;
   float mr;

   mblob.x = mouse.x/resolution.x*2-1;
   mblob.y = -mouse.y/resolution.y*2+1;
   mr = (dot(p-mblob,p-mblob))*40/fakebeat;

//   mr = smoothstep(mblob.x,mblob.y,mr);
  // metaball += mr;

 for(int i = 0; i < num; i++)
    {
        points[i].x = cos( .5 *times * i+1+ 2*i   + fakebeat/2-1)  ;
        points[i].y = sin( .5 * times * i +1/ 3   + fakebeat/2-1)  ;
        rs[i] = (dot(p-points[i],p-points[i]))*40.0;
        metaball += (1.0 / rs[i]);        
    }
	metaball += (1.0/mr);
	
    //sum the meatballs
   //float metaball =(1.0/r1+1.0/r2);
    //alter the cut-off power
    //float col = pow(metaball,-1);
    float col = (rand(p*times)*.2)+smoothstep(-metaball*10,80,5) ;

    //set the output color
    gl_FragColor = vec4(2*col,0.0*col,col,1);
}





















