#version 330

in vec4 fColor;
in vec2 fTextCoords;

uniform sampler2D texture_1;

out vec4 fragColor;

void main() {
	fragColor = texture(texture_1, fTextCoords);
}