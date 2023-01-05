#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform mat4 model;
uniform mat4 camMatrix;

void main() {
  gl_Position = camMatrix * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
  color = aColor;
  texCoord = aTex;
}