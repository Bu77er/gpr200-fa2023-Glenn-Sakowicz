#version 450
out vec4 FragColor;

in vec3 Normal;
in vec2 UV;
uniform sampler2D _Texture;

//0 for uniform color 
//1 for normals
//2 for UVs
//3 for texture
//4 for shaded
uniform int _Mode;
uniform vec3 _Color;
uniform vec3 _LightDir;
uniform float _AmbientK = 0.3;
uniform float _DiffuseK = 0.7;

float calcLight(vec3 normal){
	return _AmbientK + _DiffuseK * max(dot(-_LightDir,normal),0.0);
}

void main(){
	if (_Mode == 0){
		FragColor = vec4(_Color,1.0);
	}
	else if (_Mode == 1){
		vec3 normal = normalize(Normal);
		FragColor = vec4(abs(normal),1.0);
	}
	else if (_Mode == 2){
		FragColor = vec4(UV,0.0,1.0);
	}
	else if (_Mode == 3){
		FragColor = texture(_Texture,UV);
	}else if (_Mode == 4){
		vec3 normal = normalize(Normal);
		vec3 col = _Color * calcLight(normal);
		FragColor = vec4(col,1.0);
	}else if (_Mode == 5){
		vec3 normal = normalize(Normal);
		vec3 col = texture(_Texture,UV).rgb * calcLight(normal);
		FragColor = vec4(col,1.0);
	}
}