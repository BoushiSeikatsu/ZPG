#version 450

layout(location=0) in vec3 vp;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPosition;

void main () {
    vec4 position = modelMatrix * vec4(vp, 1.0);
    worldPosition = position.xyz / position.w;
    gl_Position = (projectionMatrix * mat4(mat3(viewMatrix)) * modelMatrix) * vec4(vp, 1.0);
};