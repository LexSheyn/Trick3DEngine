// FRAGMENT Shader
#version 450

//
//
//
//
//

// Recieved from Vertex Shader.
layout ( location = 0 )  in vec3 FragmentColor;

// Sent to GPU.
layout ( location = 0 ) out vec4 OutColor;

// Retrieved from FMeshUniform.
layout ( set = 0, binding = 0 ) uniform UniformBuffer
{
// Camera:

	mat4 CameraProjection;
	mat4 CameraView;

// Light:

	vec3  LightDirection;
	float LightAmbient;

} MeshUniform;

// Retrieved from FMeshPushConstant.
layout ( push_constant ) uniform PushConstant
{
// Transform:

	vec3 Translation;
	vec3 Rotation;
	vec3 Scale;

} MeshConstant;

void main()
{
	OutColor = vec4( FragmentColor, 1.0 );
}