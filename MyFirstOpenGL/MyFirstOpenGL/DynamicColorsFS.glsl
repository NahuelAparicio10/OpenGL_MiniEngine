#version 440 core

out vec4 fragColor;

uniform float elapsedTime;
float time = 0;

void main() {

    //Time increment with elapsedTime
    time = time + elapsedTime;

    //Restart the time
    float t = mod(time, 6.0);

   //Find out the time to change the color
    if (t < 2.0) {
        fragColor = vec4(1.0, 0.0, 0.0, 1.0); 
    } else if (t < 4.0) {
        fragColor = vec4(0.0, 0.0, 1.0, 1.0); // Azul
    } else {
        fragColor = vec4(0.0, 1.0, 0.0, 1.0); // Verde
    }

}