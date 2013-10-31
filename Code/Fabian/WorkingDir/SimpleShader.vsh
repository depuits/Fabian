#version 330 core

in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
//out vec3 fragmentColor;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
    // Output position of the vertex, in clip space : MVP * position
    vec4 v = vec4(vertexPosition_modelspace,1); // Transform an homogeneous 4D vector, remember ?
    gl_Position = (Projection * View * Model) * v;
	
	// The color of each vertex will be interpolated
    // to produce the color of each fragment
    //fragmentColor = vertexColor;
}