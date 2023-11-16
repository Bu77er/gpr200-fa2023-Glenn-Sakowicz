#version 450
out vec4 FragColor;

in Surface{
	vec2 UV;
}fs_in;

uniform sampler2D _Texture;

void main(){
	FragColor = texture(_Texture,fs_in.UV);
}