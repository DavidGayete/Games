
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec3 u_camera_pos;
uniform vec4 u_color;
uniform sampler2D u_texture;
uniform sampler2D u_noise_texture;
uniform float u_time;

void main()
{
	vec2 uv = v_uv;
	vec4 color=u_color * texture2D( u_texture, uv );
	
	color=color*texture2D(u_noise_texture, uv*500);
	
	float dist = length(v_world_position - u_camera_pos );
	dist = clamp(dist / 200.0,0.0,1.0);
	dist=pow(dist,0.5);
	
	vec3 fog_color = vec3(0.9,0.95,1.0);
	color.xyz= mix(color.xyz,fog_color,dist);
	if(color.a <=0.0)
		discard;
	
	
	gl_FragColor = color;
}
