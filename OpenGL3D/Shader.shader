#shader vertex
#version 330

in vec4 vertex;
in vec4 vColor;
in vec2 vTextCoords;

out vec4 fColor;
out vec2 fTextCoords;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vertex;
	fColor = vColor;
	fTextCoords = vTextCoords;
}

#shader fragment
#version 330

in vec4 fColor;
in vec2 fTextCoords;

uniform sampler2D texture_1;

out vec4 fragColor;

void main() {
	fragColor = texture(texture_1, fTextCoords);
}