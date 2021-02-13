#version 330

in vec3 vertex;
in vec3 vNormal;
in vec2 vTextCoords;

out vec4 fColor;
out vec2 fTextCoords;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(vertex, 1.f);
	fTextCoords = vTextCoords;
}