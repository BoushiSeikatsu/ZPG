#version 400
		in vec4 worldPosition;
		in vec3 normalVector;
		out vec4 fragColor;
		uniform vec3 cameraPosition;
		uniform vec3 lightPosition;
		uniform vec3 lightColor;
		void main()
        {
            vec3 ambient = vec3(0.1, 0.1, 0.1);
            vec3 norm = normalize(normalVector);
            vec3 lightDir = normalize(lightPosition - worldPosition.xyz/worldPosition.w);
            float diff = max(dot(lightDir, norm), 0.0);
            vec3 diffuse = diff * lightColor;
            vec3 objectColor = vec3 (0.385 ,0.647 ,0.812);
            vec3 result = (ambient + diffuse) * objectColor;
            fragColor = vec4(result,1.0);
		}