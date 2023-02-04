#version 330 core

out vec4 FragColor;

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_POINT_LIGHTS 16
#define MAX_SPOT_LIGHTS 16

struct Material {
  sampler2D diffuse;
  vec3 diffuse3;
  sampler2D specular;
  sampler2D height;
  sampler2D normal;
};

struct DirectionalLight {
  vec3 orientation;
	
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;
    
  vec3 attenuationCoeff;
	
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight {
  vec3 position;
  vec3 orientation;
  float innerCutOff;
  float outerCutOff;
  
  vec3 attenuationCoeff;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;       
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// camera
uniform vec3 viewPos;

// lights
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int directionalLightsCount;
uniform int pointLightsCount;
uniform int spotLightsCount;

// model
uniform Material material;
vec3 diffuse3;

vec3 GetDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 GetPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
  vec3 result = vec3(0.0, 0.0, 0.0);
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  diffuse3 = vec3(texture(material.diffuse, TexCoord));

  for (int i = 0; i < directionalLightsCount; ++i) {
	result += GetDirectionalLight(directionalLights[i], norm, viewDir);
  }

  for (int i = 0; i < pointLightsCount; ++i) {
	result += GetPointLight(pointLights[i], norm, FragPos, viewDir);
  }

  for (int i = 0; i < spotLightsCount; ++i) {
	result += GetSpotLight(spotLights[i], norm, FragPos, viewDir);
  }

  FragColor = vec4(result, vec4(texture(material.diffuse, TexCoord)).w);
}

vec3 GetDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
  vec3 lightDir = normalize(-light.orientation);

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), /*material.shininess*/32.0f);

  vec3 ambient = light.ambient * diffuse3;
  vec3 diffuse = light.diffuse * diff * diffuse3;
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

  return (ambient + diffuse + specular);
}

vec3 GetPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), /*material.shininess*/32.0f);

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.attenuationCoeff.x + light.attenuationCoeff.y * distance + light.attenuationCoeff.z * (distance * distance));    

  vec3 ambient = light.ambient * diffuse3;
  vec3 diffuse = light.diffuse * diff * diffuse3;
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

  return (ambient + diffuse + specular) * attenuation;
}

vec3 GetSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), /*material.shininess*/32.0f);

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.attenuationCoeff.z + light.attenuationCoeff.y * distance + light.attenuationCoeff.z * (distance * distance));    

  float theta = dot(lightDir, normalize(-light.orientation)); 
  float epsilon = light.innerCutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

  vec3 ambient = light.ambient * diffuse3;
  vec3 diffuse = light.diffuse * diff * diffuse3;
  vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

  return (ambient + diffuse + specular) * attenuation * intensity;
}
