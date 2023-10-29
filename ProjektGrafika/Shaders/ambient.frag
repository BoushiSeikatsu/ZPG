#version 400
		in vec4 worldPosition;
		in vec3 normalVector;
		out vec4 fragColor;

		struct Material {
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			float shininess;
		};

		uniform Material material;

		uniform vec3 cameraPosition;
		uniform vec3 lightPosition;
		uniform vec3 lightColor;
		uniform vec3 objectColor;
		void main() {
		vec3 ambient = material.ambient * vec3(0.1, 0.1, 0.1);
		vec3 result = (ambient) * objectColor;
		fragColor = vec4(result,1.0);
		};