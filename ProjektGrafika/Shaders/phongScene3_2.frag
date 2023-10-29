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
		void main()
		{
			//Ambient part
			vec3 ambient = material.ambient * vec3(0.1, 0.1, 0.1);

			vec3 norm = normalize(normalVector);
			vec3 lightDir = normalize(lightPosition - worldPosition.xyz/worldPosition.w);
			float diff = max(dot(lightDir, norm), 0.0);
			vec3 diffuse =  lightColor * material.diffuse * diff;

			vec3 viewDir = normalize(cameraPosition - worldPosition.xyz/worldPosition.w);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
			float specularStrength = 0.5;
			vec3 specular = lightColor * material.specular * specularStrength * spec;
			/*if (diff <= 0.0)
			{
				specular = vec3(0.0);
			}*/

			float distance = length(lightPosition - worldPosition.xyz/worldPosition.w);
			float attenuation = 1.0 / (1.0 + 0.045 * distance + 0.0075 * (distance * distance));//constant, linear, quadratic costants in this order, for now for 100 distance

			vec3 result = (ambient + diffuse + specular) * objectColor * attenuation;
			fragColor = vec4(result,1.0);
		}