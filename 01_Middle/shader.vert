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
uniform int train_id = -1;
uniform int ground_id = -1;

// for elevation 
float v_loc = pow(vs_in_pos.x, 2) + pow(vs_in_pos.z,2);
float radius_big = 3.6;  //18 units 
float radius_small = 3.2;  //16 units
float rail_width = 0.04;
float bigRingInner = pow(radius_big - rail_width, 2);
float bigRingOuter = pow(radius_big + rail_width, 2);
float smallRingInner = pow(radius_small - rail_width, 2);
float smallRingOuter = pow(radius_small + rail_width, 2);

float yElevation = 0.1; 


void main()
{
	vs_out_pos = (world * vec4(vs_in_pos.x, vs_in_pos.y, vs_in_pos.z, 1)).xyz; 
				gl_Position = MVP * vec4( vs_in_pos, 1 );

	if (ground_id != -1)
	{
		if (( v_loc < smallRingOuter && v_loc > smallRingInner ) || 
			    ( v_loc < bigRingOuter && v_loc > bigRingInner))
				{ // elevate
					vs_out_pos = (world * vec4( vs_in_pos.x, vs_in_pos.y + yElevation, vs_in_pos.z, 1 )).xyz;
					gl_Position = MVP * vec4( vs_in_pos.x, vs_in_pos.y + yElevation, vs_in_pos.z, 1 );
				} else 
				{ // no elevation needed
					vs_out_pos = (world * vec4(vs_in_pos.x, vs_in_pos.y, vs_in_pos.z, 1)).xyz; 
					gl_Position = MVP * vec4( vs_in_pos, 1 );
				}
	}

	if (train_id != -1){
				vs_out_pos = (world * vec4(vs_in_pos.x, vs_in_pos.y, vs_in_pos.z, 1)).xyz; 
				gl_Position = MVP * vec4( vs_in_pos, 1 );
	}

	
	
	vs_out_normal  = (worldIT * vec4(vs_in_normal, 0)).xyz;
	vs_out_tex0 = vs_in_tex0;
}