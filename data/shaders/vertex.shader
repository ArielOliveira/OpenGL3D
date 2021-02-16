#version 330

in vec3 vertex;
in vec3 vNormal;
in vec2 vTextCoords;

out vec4 fColor;
out vec2 fTextCoords;

uniform mat4 MVP;
uniform vec3 vColor;

void main() {
	gl_Position = MVP * vec4(vertex, 1.0);
	fTextCoords = vTextCoords;
	fColor = vec4(vColor, 1.0);
}