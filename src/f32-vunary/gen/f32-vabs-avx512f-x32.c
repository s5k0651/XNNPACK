// Auto-generated file. Do not edit!
//   Template: src/f32-vunary/avx512f.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vunary.h>


void xnn_f32_vabs_ukernel__avx512f_x32(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_abs_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const __m512i vnonsign_mask = _mm512_set1_epi32((int) params->avx512.nonsign_mask);
  for (; batch >= 32 * sizeof(float); batch -= 32 * sizeof(float)) {
    const __m512i vx0123456789ABCDEF = _mm512_loadu_si512(input);
    const __m512i vxGHIJKLMNOPQRSTUV = _mm512_loadu_si512(input + 16);
    input += 32;

    const __m512i vy0123456789ABCDEF = _mm512_and_epi32(vx0123456789ABCDEF, vnonsign_mask);
    const __m512i vyGHIJKLMNOPQRSTUV = _mm512_and_epi32(vxGHIJKLMNOPQRSTUV, vnonsign_mask);

    _mm512_storeu_si512(output, vy0123456789ABCDEF);
    _mm512_storeu_si512(output + 16, vyGHIJKLMNOPQRSTUV);
    output += 32;
  }
  for (; batch >= 16 * sizeof(float); batch -= 16 * sizeof(float)) {
    const __m512i vx = _mm512_loadu_si512(input);
    input += 16;

    const __m512i vy = _mm512_and_epi32(vx, vnonsign_mask);

    _mm512_storeu_si512(output, vy);
    output += 16;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 15 * sizeof(float));
    // Prepare mask for valid 32-bit elements (depends on batch).
    batch >>= XNN_LOG2_SIZEOF_FLOAT;
    const __mmask16 vmask = _cvtu32_mask16((uint16_t) ((uint32_t) (UINT32_C(1) << batch) - UINT32_C(1)));

    const __m512i vx = _mm512_maskz_loadu_epi32(vmask, input);
    const __m512i vy = _mm512_and_epi32(vx, vnonsign_mask);
    _mm512_mask_storeu_epi32(output, vmask, vy);
  }
}
