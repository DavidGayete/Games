
varying vec3 v_position;
varying vec3 v_world_position;
varying vec3 v_normal;
varying vec2 v_uv;
varying vec4 v_color;

uniform vec3 u_camera_pos;
uniform vec4 u_color;
uniform sampler2D u_texture;
uniform float u_time;

void main()
{

	vec3 u_light_direction= vec3(0.8,0.6,0.2);
	normalize(u_light_direction);
	vec2 uv = v_uv;
	vec4 color = u_color *texture2D(u_texture,uv * 1.0);
	vec3 N = normalize(v_normal);
	vec3 L = normalize(u_light_direction);
	float NdotL = clamp(dot(N,L),0.0,1.0);
	NdotL = round(NdotL *4.0)/4.0;
	vec3 light=NdotL * vec3(1.0,1.0,1.0) *0.8;
	light += vec3 (0.2,0.3,0.4);
	color.xyz *=light;
	
	float dist = length(v_world_position - u_camera_pos );
	dist = clamp(dist / 200.0,0.0,1.0);
	dist=pow(dist,0.5);
	
	vec3 fog_color = vec3(0.9,0.95,1.0);
	color.xyz= mix(color.xyz,fog_color,dist);
	
	
	gl_FragColor = color;
}
