#version 330

in vec3 vVertex;
in vec3 vNormal;
in vec2 vTextCoords;

out vec2 fTextCoords;
out vec4 fColor;
out vec4 fLightColor;
out vec3 fSurfaceNormal;
out vec3 fLightDir;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 vColor;
uniform vec3 vLightColor;
uniform vec3 vLightPosition;

uniform float vLightIntensity;

void main() {
	vec4 modelPos = model * vec4(vVertex, 1.0);
	vec4 cameraPos = view * modelPos;

	gl_Position = projection * cameraPos;
	fTextCoords = vTextCoords;
	fColor = vec4(vColor, 1.0);
	fLightColor = vec4(vLightColor, 1.0) * vLightIntensity;

	fSurfaceNormal = normalize((model * vec4(vNormal, 0.0)).xyz);
	fLightDir = normalize(vLightPosition - modelPos.xyz);
}