#version 330

in vec3 vVertex;
in vec3 vNormal;
in vec2 vTextCoords;

out vec2 fTextCoords;
out vec3 fModelPos;
out vec3 fNormal;
out vec3 fCameraPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normalMatrix;

void main() {
	vec4 modelPos = model * vec4(vVertex, 1.0);
	vec4 cameraPos = view * modelPos;

	gl_Position = projection * cameraPos;
	
	fTextCoords = vTextCoords;
	fModelPos = modelPos.xyz;
	fNormal = normalMatrix * vNormal;
	fCameraPos = (inverse(view) * vec4(0, 0 , 0, 1)).xyz - modelPos.xyz;
}