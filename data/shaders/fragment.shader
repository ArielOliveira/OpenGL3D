#version 330

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shineness;
};

struct Light {
	vec4 position;
	vec4 direction;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float constant;
	float linear;
	float quadratic;

	float innerRadius;
	float outterRadius;
};

in vec2 fTextCoords;
in vec4 fModelPos;
in vec4 fNormal;
in vec4 fCameraPos;

out vec4 fragColor;

uniform Material material;
uniform Light light;

void main() {
	vec4 fSurfaceNormal = normalize(fNormal);
	vec4 lightDir;
	float attenuation = 1;
	float lightDistance = 1;
	//if (light.position.w == 0) {
		//lightDir = normalize(-light.position);
	//} else {
		lightDir = normalize(light.position - fModelPos);
		lightDistance = length(light.position - fModelPos);
		attenuation = 1 / (light.constant + (light.linear * lightDistance) + (light.quadratic * (lightDistance * lightDistance)));
	//}

	// spotLight
	float spotCircle = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerRadius - light.outterRadius;
	float lit = clamp((spotCircle - light.outterRadius) / epsilon, 0.0, 1.0);

	//ambient light
	vec4 ambient = light.ambient * texture(material.diffuse, fTextCoords);

	// diffuse light
	float diffFactor = max(dot(fSurfaceNormal, lightDir), 0.0);
	vec4 diffuse = light.diffuse * diffFactor * texture(material.diffuse, fTextCoords);

	// specular light
	vec4 viewDir = normalize(fCameraPos - fModelPos);
	vec4 reflectDir = reflect(-lightDir, fSurfaceNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec4 specularMap = texture(material.specular, fTextCoords);
	vec4 specular = light.specular * spec * specularMap;

	// emissive light (self-glown)
	vec4 emissive = vec4(0);
	if (specularMap == vec4(0))
		emissive = texture(material.emissive, fTextCoords);

	vec4 result = (((ambient + diffuse + specular) * attenuation) + emissive) * lit;
	fragColor = result;
}