// VERTEX Shader
#version 450

// Retrieved from Vertex.
layout ( location = 0 ) in vec3 Position;
layout ( location = 1 ) in vec3 Color;
layout ( location = 2 ) in vec3 Normal;
layout ( location = 3 ) in vec2 TexCoord;

// Sent to Fragment Shader.
layout ( location = 0 ) out vec3 FragmentColor;

//
//

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

mat4 ToTransform       (vec3 Translation, vec3 Rotation, vec3 Scale);
mat3 ToNormalMatrix    (vec3 Rotation, vec3 Scale);

void main()
{
	mat4 MeshMatrix = ToTransform(MeshConstant.Translation, MeshConstant.Rotation, MeshConstant.Scale);

	mat4 Transform  = MeshUniform.CameraProjection * MeshUniform.CameraView * MeshMatrix; 

	gl_Position = Transform * vec4( Position, 1.0 );



	mat3 NormalMatrix     = ToNormalMatrix( MeshConstant.Rotation, MeshConstant.Scale );

	vec3 NormalWorldSpace = normalize( NormalMatrix * Normal );

	float LightIntensity  = MeshUniform.LightAmbient + max( dot(NormalWorldSpace, MeshUniform.LightDirection), 0 );

	FragmentColor = Color * LightIntensity;
}


mat4 ToTransform(vec3 Translation, vec3 Rotation, vec3 Scale)
{
// Tait–Bryan angles ZYX convention:

	float Sin1 = sin(Rotation.z);
	float Cos1 = cos(Rotation.z);

	float Sin2 = sin(Rotation.y);
	float Cos2 = cos(Rotation.y);
	
	float Sin3 = sin(Rotation.x);
	float Cos3 = cos(Rotation.x);

	mat4 Transform;

// Basis X:

	Transform[0][0] = Scale.x * (  Cos1 * Cos2 );
	Transform[0][1] = Scale.x * (  Cos2 * Sin1 );
	Transform[0][2] = Scale.x * ( -Sin2 );
	Transform[0][3] = 0.0;

// Basis Y:

	Transform[1][0] = Scale.y * ( (Cos1 * Sin2 * Sin3) - (Cos2 * Sin1) );
	Transform[1][1] = Scale.y * ( (Cos1 * Cos3) + (Sin1 * Sin2 * Sin3) );
	Transform[1][2] = Scale.y * ( Cos2 * Sin3 );
	Transform[1][3] = 0.0;

// Basis Z:

	Transform[2][0] = Scale.z * ( (Sin1 * Sin3) + (Cos1 * Cos3 * Sin2) );
	Transform[2][1] = Scale.z * ( (Cos3 * Sin1 * Sin2) - (Cos1 * Sin3) );
	Transform[2][2] = Scale.z * ( Cos2 * Cos3 );
	Transform[2][3] = 0.0;

// Basis W sneaky used for translation:

	Transform[3][0] = Translation.x;
	Transform[3][1] = Translation.y;
	Transform[3][2] = Translation.z;
	Transform[3][3] = 1.0;

	return Transform;
}

mat3 ToNormalMatrix(vec3 Rotation, vec3 Scale)
{
// Tait–Bryan angles ZYX convention:

	float Sin1 = sin(Rotation.z);
	float Cos1 = cos(Rotation.z);

	float Sin2 = sin(Rotation.y);
	float Cos2 = cos(Rotation.y);
	
	float Sin3 = sin(Rotation.x);
	float Cos3 = cos(Rotation.x);

	vec3 InverseScale = 1.0 / Scale;
	mat3 NormalMatrix;

// Basis X:

	NormalMatrix[0][0] = InverseScale.x * (  Cos1 * Cos2 );
	NormalMatrix[0][1] = InverseScale.x * (  Cos2 * Sin1 );
	NormalMatrix[0][2] = InverseScale.x * ( -Sin2 );

// Basis Y:

	NormalMatrix[1][0] = InverseScale.y * ( (Cos1 * Sin2 * Sin3) - (Cos2 * Sin1) );
	NormalMatrix[1][1] = InverseScale.y * ( (Cos1 * Cos3) + (Sin1 * Sin2 * Sin3) );
	NormalMatrix[1][2] = InverseScale.y * ( Cos2 * Sin3 );

// Basis Z:

	NormalMatrix[2][0] = InverseScale.z * ( (Sin1 * Sin3) + (Cos1 * Cos3 * Sin2) );
	NormalMatrix[2][1] = InverseScale.z * ( (Cos3 * Sin1 * Sin2) - (Cos1 * Sin3) );
	NormalMatrix[2][2] = InverseScale.z * ( Cos2 * Cos3 );

	return NormalMatrix;
}
