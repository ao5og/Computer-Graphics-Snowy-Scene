#version 130

in vec3 vs_out_pos;
in vec3 vs_out_normal;
in vec2 vs_out_tex0;

out vec4 fs_out_col;

//
// uniform variables
//

uniform int objId = -1; // for each object to set respective colour or texture

// scene attributes

uniform vec3 eye_pos = vec3(0, 15, 15);

uniform sampler2D texImage;

void main()
{



	fs_out_col = texture(texImage, vs_out_tex0.st);
	
}
