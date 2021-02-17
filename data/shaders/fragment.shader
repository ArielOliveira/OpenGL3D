#version 330

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shineness;
};

in vec4 fColor;
in vec4 fLightColor;
in vec3 fSurfaceNormal;
in vec2 fTextCoords;
in vec3 fLightDir;


out vec4 fragColor;

uniform Material material;
uniform sampler2D texture_1;

void main() {
	float diffFactor = max(dot(fSurfaceNormal, fLightDir), 0.0);
	vec3 diffuse = diffFactor * fLightColor.xyz;
	vec4 result = vec4(material.ambient, 1.0) * vec4(diffuse, 1.0);
	fragColor = result;
}