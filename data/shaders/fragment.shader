#version 330

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
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

void main() {
	vec3 fSurfaceNormal = normalize(fNormal);
	vec3 lightDir = normalize(light.position - fModelPos);

	//ambient light
	vec3 ambient = light.ambient * texture(material.diffuse, fTextCoords).rgb;

	// diffuse light
	float diffFactor = max(dot(fSurfaceNormal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diffFactor * texture(material.diffuse, fTextCoords).rgb;

	// specular light
	vec3 viewDir = normalize(fCameraPos - fModelPos);
	vec3 reflectDir = reflect(-lightDir, fSurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec3 specularMap = texture(material.specular, fTextCoords).rgb;
	vec3 specular = light.specular * spec * specularMap;

	// emissive light (self-glown)
	vec3 emissive = vec3(0);
	if (specularMap == vec3(0))
		emissive = texture(material.emissive, fTextCoords).rgb;

	vec3 result = ambient + diffuse + specular + emissive;
	fragColor = vec4(result, 1.0);
}