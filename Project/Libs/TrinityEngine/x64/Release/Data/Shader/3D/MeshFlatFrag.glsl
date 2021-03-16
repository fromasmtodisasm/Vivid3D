#version 330 core

uniform vec3 mCol;

out vec4 color;

void main(){

    vec4 fc;

    fc.rgb = mCol;
    fc.a = 1.0;

    color = fc;

}