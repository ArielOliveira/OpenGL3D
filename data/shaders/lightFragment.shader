#version 330

uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 fragColor;

void main() {
	fragColor = vec4(objectColor * lightColor, 1.f);
}