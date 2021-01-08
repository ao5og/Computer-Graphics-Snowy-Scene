#version 130

// vertex attribute inputs
in vec3 vs_in_pos;
in vec3 vs_in_normal;
in vec2 vs_in_tex0;

// vertex attribute outputs
out vec3 vs_out_pos;
out vec3 vs_out_normal;
out vec2 vs_out_tex0;


// shader parameters
uniform mat4 world;
uniform mat4 worldIT;
uniform mat4 MVP;


// for elevation 
float v_loc = pow(vs_in_pos.x, 2) + pow(vs_in_pos.z,2);
float radius_a = 3.2;
float radius_b = 3.6;
float rail_width = 0.08;
float yElevation = 0.075;

void main()
{
	

	if ((v_loc < pow(radius_a + rail_width,2) && v_loc > pow(radius_a - rail_width,2)) || 
		(v_loc < pow(radius_b + rail_width,2) && v_loc > pow(radius_b - rail_width,2))) 
		{
		vs_out_pos = (world * vec4( vs_in_pos.x, vs_in_pos.y + yElevation, vs_in_pos.z, 1 )).xyz;
		gl_Position = MVP * vec4( vs_in_pos.x, vs_in_pos.y + yElevation, vs_in_pos.z, 1 );
		} else { 
		vs_out_pos = (world * vec4(vs_in_pos.x, vs_in_pos.y + yElevation, vs_in_pos.z, 1)).xyz; //everything ok
		gl_Position = MVP * vec4( vs_in_pos, 1 );
		}


	
	vs_out_normal  = (worldIT * vec4(vs_in_normal, 0)).xyz;
	vs_out_tex0 = vs_in_tex0;
}