//	#version 450
//	out vec4 FragColor;
//	in vec2 UV;
//	void main()
//	{
//		FragColor = vec4(UV, 0.0,1.0);
//	}
	#version 450
	out vec4 FragColor;
	uniform vec3 _Color;
	uniform float _Brightness;
	in vec2 UV;
	void main(){
		FragColor = vec4(_Color * _Brightness,1.0);
	}
