#include <syslog.h>
#include <stdarg.h>

/*
 * libSystem's simd matrix identity constants.
 *
 * Xcode binaries bind these eagerly (they are data, not stub calls), so if the
 * symbol is missing dyld refuses to load the client image:
 *
 *     dyld: Symbol not found: _matrix_identity_double4x4
 *       Referenced from: .../SharedFrameworks/ModelIO.framework/Versions/A/ModelIO
 *       Expected in: /usr/lib/libSystem.B.dylib
 *
 * These live in libsystem_c on Darwin, which libSystem re-exports.
 *
 * Note the values: an identity matrix has 1 on the diagonal and 0 elsewhere.
 * The previous float4x4 definition was zero-initialised, which is not an
 * identity, so any client composing a transform with it silently produced a
 * zero matrix.
 */

typedef float __attribute__((ext_vector_type(2))) simd_float2;
typedef float __attribute__((ext_vector_type(3))) simd_float3;
typedef float __attribute__((ext_vector_type(4))) simd_float4;
typedef double __attribute__((ext_vector_type(4))) simd_double4;

typedef struct { simd_float2 columns[2]; } simd_float2x2;
typedef struct { simd_float3 columns[3]; } simd_float3x3;
typedef struct { simd_float4 columns[4]; } simd_float4x4;
typedef struct { simd_double4 columns[4]; } simd_double4x4;

simd_float2x2 matrix_identity_float2x2 = {
	.columns[0] = { 1.0f, 0.0f },
	.columns[1] = { 0.0f, 1.0f },
};

simd_float3x3 matrix_identity_float3x3 = {
	.columns[0] = { 1.0f, 0.0f, 0.0f },
	.columns[1] = { 0.0f, 1.0f, 0.0f },
	.columns[2] = { 0.0f, 0.0f, 1.0f },
};

simd_float4x4 matrix_identity_float4x4 = {
	.columns[0] = { 1.0f, 0.0f, 0.0f, 0.0f },
	.columns[1] = { 0.0f, 1.0f, 0.0f, 0.0f },
	.columns[2] = { 0.0f, 0.0f, 1.0f, 0.0f },
	.columns[3] = { 0.0f, 0.0f, 0.0f, 1.0f },
};

simd_double4x4 matrix_identity_double4x4 = {
	.columns[0] = { 1.0, 0.0, 0.0, 0.0 },
	.columns[1] = { 0.0, 1.0, 0.0, 0.0 },
	.columns[2] = { 0.0, 0.0, 1.0, 0.0 },
	.columns[3] = { 0.0, 0.0, 0.0, 1.0 },
};