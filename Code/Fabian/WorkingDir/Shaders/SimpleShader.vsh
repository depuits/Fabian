#version 130

//layout(location = 0) in vec3 in_vertexPosition_modelspace;
//layout(location = 1) in vec3 in_vertexNormal;
//layout(location = 2) in vec2 in_vertexUV;

in vec3 in_vertexPos;
in vec3 in_vertexNormal;
in vec2 in_vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 EyeDirection_cameraspace;

uniform vec3 LightPosition_worldspace;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    // Output position of the vertex, in clip space : MVP * position
    vec4 v = vec4(in_vertexPos, 1); // Transform an homogeneous 4D vector
    gl_Position = (Projection * View * Model) * v;
	 
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0), because we are in camera space.
	vec3 vertexPosition_cameraspace = ( View * Model * v).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
	 
	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( View * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	 
	// Normal of the the vertex, in camera space
	// Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	Normal_cameraspace = ( View * Model * vec4(in_vertexNormal,0)).xyz; 
		 
	// UV of the vertex. No special space for this one.
    UV = in_vertexUV;
}
