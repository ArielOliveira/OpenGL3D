#version 330

in vec4 vVertex;
in vec4 vNormal;
in vec2 vTextCoords;

out vec2 fTextCoords;
out vec4 fModelPos;
out vec4 fNormal;
out vec4 fCameraPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalMatrix;

void main() {
	vec4 modelPos = model * vVertex;
	vec4 cameraPos = view * modelPos;

	gl_Position = projection * cameraPos;
	
	fTextCoords = vTextCoords;
	fModelPos = modelPos;
	fNormal = normalize(vec4(normalMatrix * vNormal.xyz, 0));
	fCameraPos = (inverse(view) * vec4(0, 0 , 0, 1)) - modelPos;
}