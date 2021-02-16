#version 330

in vec4 fColor;
in vec2 fTextCoords;

out vec4 fragColor;

uniform sampler2D texture_1;

void main() {
	fragColor = texture(texture_1, fTextCoords) + fColor;
}