#version 330

#define MAX_DIRECTIONAL_LIGHT 2
#define MAX_POINT_LIGHT 20
#define MAX_SPOT_LIGHT 20

#define D_LIGHTS 1
#define P_LIGHTS 1
#define S_LIGHTS 0

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

vec4 getAmbient(vec4 lAmbient, sampler2D mAmbient, vec2 coord);
vec4 getDiff(vec4 lDiff, sampler2D mDiff, vec2 coord,  vec4 lDir, vec4 mNormal);
vec4 getSpec(vec4 lSpec, sampler2D mSpec, vec2 coord,  vec4 lDir, vec4 mNormal, vec4 viewDir, float mShine);

vec4 computeDirLights(Light light, vec4 viewDir);
vec4 computePointLights(Light light, vec4 viewDir);
vec4 computeSpotLights(Light light, vec4 viewDir);

//int dirLightsNum = 1;
//int pointLightsNum = 0;
//int spotLightsNum = 0;

uniform Light dLights[MAX_DIRECTIONAL_LIGHT];
uniform Light pLights[MAX_POINT_LIGHT];
uniform Light sLights[MAX_SPOT_LIGHT];

void main() {
	vec4 viewDir = normalize(fCameraPos - fModelPos);
	//if (light.position.w == 0) {
		//lightDir = normalize(-light.position);
	//} else {
		//lightDir = normalize(light.position - fModelPos);
		//lightDistance = length(light.position - fModelPos);
		//attenuation = 1 / (light.constant + (light.linear * lightDistance) + (light.quadratic * (lightDistance * lightDistance)));
	//}

	// spotLight
	//float spotCircle = dot(lightDir, normalize(-light.direction));
	//float epsilon = light.innerRadius - light.outterRadius;
	//float lit = clamp((spotCircle - light.outterRadius) / epsilon, 0.0, 1.0);

	//ambient light
	//vec4 ambient = light.ambient * texture(material.diffuse, fTextCoords);

	// diffuse light
	//float diffFactor = max(dot(fSurfaceNormal, lightDir), 0.0);
	//vec4 diffuse = light.diffuse * diffFactor * texture(material.diffuse, fTextCoords);

	// specular light
	//vec4 viewDir = normalize(fCameraPos - fModelPos);
	//vec4 reflectDir = reflect(-lightDir, fSurfaceNormal);
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineness);
	vec4 specularMap = texture(material.specular, fTextCoords);
	specularMap.w = 0;
	//vec4 specular = light.specular * spec * specularMap;

	
	// emissive light (self-glown)
	vec4 emissive = vec4(0);
	if (specularMap == vec4(0))
		emissive = texture(material.emissive, fTextCoords);

	//vec4 result = (((ambient + diffuse + specular) * attenuation) + emissive) * lit;
	vec4 result = vec4(0);

	//for (int i = 0; i < D_LIGHTS; i++)
	//	result += computeDirLights(dLights[i], viewDir);
	
	for (int j = 0; j < P_LIGHTS; j++)
		result += computePointLights(pLights[j], viewDir);

	fragColor = result + emissive;
}

vec4 getAmbient(vec4 lAmbient, sampler2D mAmbient, vec2 coord) {
	return (lAmbient * texture(mAmbient, coord));
}

vec4 getDiff(vec4 lDiff, sampler2D mDiff, vec2 coord,  vec4 lDir, vec4 mNormal) {
	float diffFactor = max(dot(mNormal, lDir), 0.0);

	return (lDiff * diffFactor * texture(mDiff, coord));
}

vec4 getSpec(vec4 lSpec, sampler2D mSpec, vec2 coord,  vec4 lDir, vec4 mNormal, vec4 viewDir, float mShine) {
	vec4 reflectDir = reflect(-lDir, mNormal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mShine);

	vec4 specularMap = texture(mSpec, coord);
	
	return (lSpec * spec * specularMap);
}

vec4 computeDirLights(Light light, vec4 viewDir) {
	vec4 ambient = getAmbient(light.ambient, material.diffuse, fTextCoords);
	vec4 diffuse = getDiff(light.diffuse, material.diffuse, fTextCoords, light.direction, fNormal);
	vec4 specular = getSpec(light.specular, material.specular, fTextCoords, light.direction, fNormal, fCameraPos, material.shineness);

	return (ambient + diffuse + specular);
}

vec4 computePointLights(Light light, vec4 viewDir) {
	float lightDistance = length(light.position - fModelPos);
	float attenuation = 1 / (light.constant + (light.linear * lightDistance) + (light.quadratic * (lightDistance * lightDistance)));

	vec4 lightDir = normalize(light.position - fModelPos);

	vec4 ambient = getAmbient(light.ambient, material.diffuse, fTextCoords);
	vec4 diffuse = getDiff(light.diffuse, material.diffuse, fTextCoords, lightDir, fNormal);
	vec4 specular = getSpec(light.specular, material.specular, fTextCoords, lightDir, fNormal, viewDir, material.shineness);
	
	return (ambient + diffuse + specular) * attenuation;
}

vec4 computeSpotLights(Light light, vec4 viewDir) {
	return vec4(0);
}