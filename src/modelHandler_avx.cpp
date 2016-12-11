#include <thread>
#include <immintrin.h>
#include <atomic>
#include "filters.hpp"
#include "sec.hpp"

#define HAVE_AVX

typedef __m256 v256_t;
static inline __m256
madd256(__m256 v0, __m256 v1, __m256 v2)
{
	return _mm256_add_ps(_mm256_mul_ps(v0, v1), v2);
}

#define load_broadcast _mm256_broadcast_ss
#define load256 _mm256_load_ps
#define store256 _mm256_store_ps
#define add256 _mm256_add_ps
#define max256 _mm256_max_ps
#define min256 _mm256_min_ps
#define zero _mm256_setzero_ps
#define set1 _mm256_set1_ps
#define mul256 _mm256_mul_ps

static inline float
hadd8(__m256 v)
{
	v = _mm256_hadd_ps(v, v);
	v = _mm256_hadd_ps(v, v);

	float v0 = _mm_cvtss_f32(_mm256_extractf128_ps(v,0));
	float v1 = _mm_cvtss_f32(_mm256_extractf128_ps(v,1));

	return v0 + v1;
}

#include "modelHandler_avx_func.hpp"


#undef UNROLL
typedef __m256 vreg_t;
#define VEC_NELEM 8
#ifdef __x86_64
#define UNROLL 5
#else
#define UNROLL 2
#endif
#define store_vreg(ptr,val) _mm256_store_ps((float*)(ptr), val)
#define load_vreg(ptr) _mm256_load_ps((float*)(ptr))
#define load_vreg_broadcast(ptr) _mm256_broadcast_ss((float*)(ptr))
static inline __m256
madd_vreg(__m256 a, __m256 b, __m256 c)
{
    return _mm256_add_ps(_mm256_mul_ps(a,b), c);
}
#define add_vreg _mm256_add_ps
#define zero_vreg _mm256_setzero_ps
#define min_vreg _mm256_min_ps
#define max_vreg _mm256_max_ps
#define set1_vreg _mm256_set1_ps

#define SIMD_OPLANE

#include "modelHandler_simd.hpp"

namespace w2xc {
void
filter_AVX_impl(ComputeEnv *env,
		const float *packed_input,
		float *packed_output,
		int nInputPlanes,
		int nOutputPlanes,
		const float *fbiases,
		const float *weight,
		int ip_width,
		int ip_height,
		int nJob)
{
	if (simd_available(nInputPlanes, nOutputPlanes)) {
		filter_simd_impl0(env,
				  packed_input,
				  packed_output,
				  nInputPlanes,
				  nOutputPlanes,
				  fbiases,
				  weight,
				  ip_width,
				  ip_height,
				  nJob);
	} else {
		filter_AVX_impl0(env,
				 packed_input,
				 packed_output,
				 nInputPlanes,
				 nOutputPlanes,
				 fbiases,
				 weight,
				 ip_width,
				 ip_height,
				 nJob);
	}
}


}
