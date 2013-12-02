#version 330 core
out vec3 color;

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;

// Values that stay constant for the whole mesh.
uniform sampler2D TextureSampler;

uniform vec3 LightColor;
uniform float LightPower;

void main()
{
	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	
	// Cosine of the angle between the normal and the light direction,
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n, l), 0, 1 );
	
	vec3 MaterialDiffuseColor = vec3(0.8, 0.1, 0.1);
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	
	color =  
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta;// / (distance*distance);
	
	
	
	
	
	
	// Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    //color = fragmentColor;
	
    //color = vec3(UV.x, UV.y, 0);
    //color = vec3(1, 0, 0);    
	
	// Output color = color of the texture at the specified UV
    //color = texture( myTextureSampler, UV ).rgb;
}
