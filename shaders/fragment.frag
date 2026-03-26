#version 330 core
in vec3 x;
out vec4 fragcolor;

void main(){
    fragcolor = vec4(x, 1.0f);
}

