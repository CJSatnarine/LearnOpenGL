#version 330 core 

out vec4 fragColour;

uniform vec4 uniformColour;

void main() {
    // fragColour = vec4(1.0f, 0.0f, 1.0f, 1.0f);
    fragColour = uniformColour;
}
