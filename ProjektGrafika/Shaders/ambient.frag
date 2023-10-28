#version 400
		in vec4 worldPosition;
		in vec3 normalVector;
		out vec4 fragColor;
		uniform vec3 cameraPosition;
		uniform vec3 lightPosition;
		uniform vec3 lightColor;
		void main() {
		vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
		vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);
		fragColor = (ambient) * objectColor;
		};