#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 2) in vec2 in_uv;

out vec2 our_uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform float offsetX;
<<<<<<< HEAD
uniform vec2 scaleUV;
=======
>>>>>>> 34e51efbe7a2de4def3fa3ce581d8224e196a9df

void main(){

	gl_Position = projection * view * model * vec4(in_position, 1.0);
	our_uv = in_uv;
	our_uv.x = our_uv.x + offsetX;
<<<<<<< HEAD
	if(scaleUV.x != 0 && scaleUV.y != 0)
		our_uv = our_uv * scaleUV;
=======
>>>>>>> 34e51efbe7a2de4def3fa3ce581d8224e196a9df
}

