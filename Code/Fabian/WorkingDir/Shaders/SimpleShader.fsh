#version 330 core
out vec4 color;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in vec3 EyeDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform sampler2D TextureSampler;

uniform vec4 LightColor;
uniform float LightPower;

void main()
{
	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	
	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n, l), 0, 1 );
	
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );


	vec4 MaterialDiffuseColor = texture( TextureSampler, UV ).rgba; //vec4(0.8, 0.1, 0.1, 1);
	MaterialDiffuseColor.a = 1;
	vec4 MaterialSpecularColor = vec4(0.9, 0.9, 0.9, 1);
	vec4 MaterialAmbientColor = vec4(0.1, 0.1, 0.1, 1) * MaterialDiffuseColor;
	
	color =  
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta + // / (distance*distance)
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,25);	

	// Output color = color of the texture at the specified UV
    //color = texture( TextureSampler, UV ).rgba;
}
