#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
	vec3 WorldPosition;
	vec3 WorldNormal;
}fs_in;

struct Light
{
	vec3 position;
	vec3 color;
};

#define MAX_LIGHTS 4
uniform Light _Lights[MAX_LIGHTS];
uniform sampler2D _Texture;
uniform vec3 cam;

void main(){

	vec3 final;
	vec3 ambient = vec3(1,1,1);

	for(int i =0; i < MAX_LIGHTS; i++)
	{
		vec3 lightVec = _Lights[i].position - fs_in.WorldPosition;
		float distances = length(lightVec);
		float a= 3.0f, b = 0.7f;
		float intensity = 15.0f / (a * distances * distances + b + 1.0f);

		float specular = 0.0f;

		vec3 normal = normalize(fs_in.WorldNormal);
		vec3 lightDirection = normalize(lightVec + .5);
		float diffuse = max(dot(normal, lightDirection), 0.0f);
		
		if(diffuse != 0.0f)
		{
			float specularLight = 0.5f;
			vec3 view = normalize(cam - fs_in.WorldPosition);
			vec3 halfVec = normalize(view +lightDirection);
			vec3 reflection = reflect(-lightDirection, normal);
			float specularAmount = pow(max(dot(normal, halfVec), 0.0f), 16);
			specular = specularAmount * specularLight;
		}
		vec3 textureColor = texture(_Texture, fs_in.UV).rgb;
		final += (textureColor * (diffuse * intensity + (ambient * .1)) + specular * intensity) * _Lights[i].color;
	}
		FragColor = vec4(final, .5f);
   

}