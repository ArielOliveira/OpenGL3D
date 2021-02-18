#version 330

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shineness;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 fTextCoords;
in vec3 fModelPos;
in vec3 fNormal;
in vec3 fCameraPos;

out vec4 fragColor;

uniform Material material;
uniform Light light;
uniform sampler2D texture_1;

void main() {
	vec3 fSurfaceNormal = normalize(fNormal);
	vec3 lightDir = normalize(light.position - fModelPos);

	//ambient light
	vec3 ambient = light.ambient * material.ambient;

	// diffuse light
	float diffFactor = max(dot(fSurfaceNormal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diffFactor * material.diffuse);

	// specular light
	vec3 viewDir = normalize(fCameraPos - fModelPos);
	vec3 reflectDir = reflect(-lightDir, fSurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0);
}