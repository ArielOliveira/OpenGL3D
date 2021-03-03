#version 330

#define MAX_DIRECTIONAL_LIGHT 2
#define MAX_POINT_LIGHT 20
#define MAX_SPOT_LIGHT 20

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;

	int diffuseQuotient;
	int specularQuotient;
	int emissiveQuotient;

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

vec4 getAmbient(vec4 lAmbient, vec4 mAmbient);
vec4 getDiff(vec4 lDiff, vec4 mDiff,  vec4 lDir, vec4 mNormal);
vec4 getSpec(vec4 lSpec, vec4 mSpec,  vec4 lDir, vec4 mNormal, vec4 viewDir, float mShine);

vec4 computeDirLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap);
vec4 computePointLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap);
vec4 computeSpotLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap);

uniform int D_LIGHTS;
uniform int P_LIGHTS;
uniform int S_LIGHTS;

uniform Light dLights[MAX_DIRECTIONAL_LIGHT];
uniform Light pLights[MAX_POINT_LIGHT];
uniform Light sLights[MAX_SPOT_LIGHT];

void main() {
	vec4 viewDir = normalize(fCameraPos - fModelPos);
	
	vec4 diffuseMap = texture(material.diffuse, fTextCoords) / material.diffuseQuotient;
	vec4 specularMap = texture(material.specular, fTextCoords) / material.specularQuotient;
	
	specularMap.w = 0;
	
	// emissive light (self-glown)
	vec4 emissive = vec4(0);
	if (specularMap == vec4(0))
		emissive = texture(material.emissive, fTextCoords);

	vec4 result = vec4(0);

	for (int i = 0; i < D_LIGHTS; i++)
		result += computeDirLights(dLights[i], viewDir, diffuseMap, diffuseMap, specularMap);
	
	for (int j = 0; j < P_LIGHTS; j++)
		result += computePointLights(pLights[j], viewDir, diffuseMap, diffuseMap, specularMap);

	for (int k = 0; k < S_LIGHTS; k++)
		result += computeSpotLights(sLights[k], viewDir, diffuseMap, diffuseMap, specularMap);


	fragColor = result;
}

vec4 getAmbient(vec4 lAmbient, vec4 mAmbient) {
	return (lAmbient * mAmbient);
}

vec4 getDiff(vec4 lDiff, vec4 mDiff, vec4 lDir, vec4 mNormal) {
	float diffFactor = max(dot(mNormal, lDir), 0.0);

	return (lDiff * diffFactor * mDiff);
}

vec4 getSpec(vec4 lSpec, vec4 mSpec, vec4 lDir, vec4 mNormal, vec4 viewDir, float mShine) {
	vec4 reflectDir = reflect(-lDir, mNormal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mShine);
	
	return (lSpec * spec * mSpec);
}

vec4 computeDirLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap) {
	vec4 ambient = getAmbient(light.ambient, ambientMap);
	vec4 diffuse = getDiff(light.diffuse, diffuseMap, light.direction, fNormal);
	vec4 specular = getSpec(light.specular, specularMap, light.direction, fNormal, viewDir, material.shineness);

	return (ambient + diffuse + specular);
}

vec4 computePointLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap) {
	vec4 objectToLight = normalize(light.position - fModelPos); 

	float lightDistance = length(light.position - fModelPos);
	float attenuation = 1 / (light.constant + (light.linear * lightDistance) + (light.quadratic * (lightDistance * lightDistance)));

	vec4 ambient = getAmbient(light.ambient, ambientMap);
	vec4 diffuse = getDiff(light.diffuse, diffuseMap, objectToLight, fNormal);
	vec4 specular = getSpec(light.specular, specularMap, objectToLight, fNormal, viewDir, material.shineness);
	
	return (ambient + diffuse + specular) * attenuation;
}

vec4 computeSpotLights(Light light, vec4 viewDir, vec4 ambientMap, vec4 diffuseMap, vec4 specularMap) {	
	vec4 objectToLight = normalize(light.position - fModelPos); 

	float lightDistance = length(light.position - fModelPos);
	float attenuation = 1 / (light.constant + (light.linear * lightDistance) + (light.quadratic * (lightDistance * lightDistance)));

	float spotCircle = dot(objectToLight, normalize(-light.direction));
	float epsilon = light.innerRadius - light.outterRadius;
	float lit = clamp((spotCircle - light.outterRadius) / epsilon, 0.0, 1.0);

	vec4 ambient = getAmbient(light.ambient, ambientMap);
	vec4 diffuse = getDiff(light.diffuse, diffuseMap, objectToLight, fNormal);
	vec4 specular = getSpec(light.specular, specularMap, objectToLight, fNormal, viewDir, material.shineness);

	return ((ambient + diffuse + specular) * attenuation) * lit;
}