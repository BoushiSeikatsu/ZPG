#version 400

		layout(location=0) in vec3 vp;
		layout(location=1) in vec3 vn;

		out vec4 worldPosition;
		out vec3 normalVector;

		uniform mat4 modelMatrix;
		uniform mat4 viewMatrix;
		uniform mat4 projectionMatrix;

		void main() {
		worldPosition = modelMatrix * vec4(vp, 1.0);
		mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
		normalVector = normalMatrix * vn;
		gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
		}