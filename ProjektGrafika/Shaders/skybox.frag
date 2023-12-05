#version 450


in vec3 worldPosition;


uniform samplerCube UISky;


out vec4 frag_colour;



void main () {
	 
    frag_colour = texture(UISky, worldPosition) * 0.2;
}

