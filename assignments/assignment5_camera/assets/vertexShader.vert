#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNormal;

out vec3 Normal;
uniform mat4 _Model;
uniform mat4 projection;
uniform mat4 view;

void main(){
	Normal = vNormal;
	gl_Position = _Model * projection * view * vec4(vPos,1.0);
}