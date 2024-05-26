#version 440 core

out vec4 fragColor;

uniform vec2 windowSize;

void main(){
	
	if(gl_FragCoord.y > windowSize.y * 0.5){
		fragColor = vec4(0.0, 0.0, 0.7, 1.0);
	}
	else{
		fragColor = vec4(1.0, 0.5, 1.0, 1.0);
	}
}