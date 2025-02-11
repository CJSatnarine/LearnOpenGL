#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColour;
layout(location = 2) in vec2 aTextureCoordinate;

out vec3 ourColour;
out vec2 textureCoordinate;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColour = aColour;
    textureCoordinate = aTextureCoordinate;
}
