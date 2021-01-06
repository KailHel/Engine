#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

    vec3 c=vec3(0,0,0);
    float l,z=time;

    for(int i=0;i<3;i++) {

        vec2 uv,p=gl_FragCoord.xy/resolution;
        uv=p;
        p-=.5;
        p.x*=resolution.x/resolution.y;
        z+=.7;
        l=length(p*p);
        uv+=p/l*(sin(z)+.1)*abs(sin(l*58.-z*2.));
        c[i]=.01/length(abs(mod(uv,1.)-.2));
    }
    gl_FragColor=vec4(c/l,time);

}