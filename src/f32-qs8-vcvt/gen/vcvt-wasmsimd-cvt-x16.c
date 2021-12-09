// Auto-generated file. Do not edit!
//   Template: src/f32-qs8-vcvt/wasmsimd-cvt.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vcvt.h>


void xnn_f32_qs8_vcvt_ukernel__wasmsimd_cvt_x16(
    size_t n,
    const float* x,
    int8_t* y,
    const union xnn_f32_qs8_cvt_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN XNN_DISABLE_MSAN
{
  assert(n != 0);
  assert(x != NULL);
  assert(y != NULL);

  const v128_t vscale = wasm_v128_load64_splat(params->wasmsimd_cvt.scale);
  const v128_t voutput_zero_point = wasm_v128_load64_splat(params->wasmsimd_cvt.output_zero_point);
  const v128_t voutput_min = wasm_v128_load64_splat(params->wasmsimd_cvt.output_min);
  const v128_t voutput_max = wasm_v128_load64_splat(params->wasmsimd_cvt.output_max);
  for (; n >= 16 * sizeof(int8_t); n -= 16 * sizeof(int8_t)) {
    v128_t vx0123 = wasm_v128_load(x);
    v128_t vx4567 = wasm_v128_load(x + 4);
    v128_t vx89AB = wasm_v128_load(x + 8);
    v128_t vxCDEF = wasm_v128_load(x + 12);
    x += 16;

    vx0123 = wasm_f32x4_mul(vx0123, vscale);
    vx4567 = wasm_f32x4_mul(vx4567, vscale);
    vx89AB = wasm_f32x4_mul(vx89AB, vscale);
    vxCDEF = wasm_f32x4_mul(vxCDEF, vscale);

    vx0123 = wasm_f32x4_nearest(vx0123);
    vx4567 = wasm_f32x4_nearest(vx4567);
    vx89AB = wasm_f32x4_nearest(vx89AB);
    vxCDEF = wasm_f32x4_nearest(vxCDEF);

    v128_t vacc0123 = wasm_i32x4_trunc_sat_f32x4(vx0123);
    v128_t vacc4567 = wasm_i32x4_trunc_sat_f32x4(vx4567);
    v128_t vacc89AB = wasm_i32x4_trunc_sat_f32x4(vx89AB);
    v128_t vaccCDEF = wasm_i32x4_trunc_sat_f32x4(vxCDEF);

    v128_t vacc01234567 = wasm_i16x8_narrow_i32x4(vacc0123, vacc4567);
    v128_t vacc89ABCDEF = wasm_i16x8_narrow_i32x4(vacc89AB, vaccCDEF);

    vacc01234567 = wasm_i16x8_add_sat(vacc01234567, voutput_zero_point);
    vacc89ABCDEF = wasm_i16x8_add_sat(vacc89ABCDEF, voutput_zero_point);

    v128_t vy0123456789ABCDEF = wasm_i8x16_narrow_i16x8(vacc01234567, vacc89ABCDEF);

    vy0123456789ABCDEF = wasm_i8x16_max(vy0123456789ABCDEF, voutput_min);

    vy0123456789ABCDEF = wasm_i8x16_min(vy0123456789ABCDEF, voutput_max);

    wasm_v128_store(y, vy0123456789ABCDEF);
    y += 16;
  }
  for (; n >= 8 * sizeof(int8_t); n -= 8 * sizeof(int8_t)) {
    v128_t vx_lo = wasm_v128_load(x);
    v128_t vx_hi = wasm_v128_load(x + 4);
    x += 8;

    vx_lo = wasm_f32x4_mul(vx_lo, vscale);
    vx_hi = wasm_f32x4_mul(vx_hi, vscale);

    vx_lo = wasm_f32x4_nearest(vx_lo);
    vx_hi = wasm_f32x4_nearest(vx_hi);

    v128_t vacc_lo = wasm_i32x4_trunc_sat_f32x4(vx_lo);
    v128_t vacc_hi = wasm_i32x4_trunc_sat_f32x4(vx_hi);

    v128_t vacc = wasm_i16x8_narrow_i32x4(vacc_lo, vacc_hi);
    vacc = wasm_i16x8_add_sat(vacc, voutput_zero_point);

    v128_t vy = wasm_i8x16_narrow_i16x8(vacc, vacc);
    vy = wasm_i8x16_max(vy, voutput_min);
    vy = wasm_i8x16_min(vy, voutput_max);

    *((double*) y) = wasm_f64x2_extract_lane(vy, 0);
    y += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(int8_t));
    assert(n <= 7 * sizeof(int8_t));
    v128_t vx_lo = wasm_v128_load(x);
    const float* x_hi = x + 4;
    if XNN_UNPREDICTABLE((n & (4 * sizeof(int8_t))) == 0) {
      x_hi = x;
    }
    v128_t vx_hi = wasm_v128_load(x_hi);

    vx_lo = wasm_f32x4_mul(vx_lo, vscale);
    vx_hi = wasm_f32x4_mul(vx_hi, vscale);

    vx_lo = wasm_f32x4_nearest(vx_lo);
    vx_hi = wasm_f32x4_nearest(vx_hi);

    v128_t vacc_lo = wasm_i32x4_trunc_sat_f32x4(vx_lo);
    v128_t vacc_hi = wasm_i32x4_trunc_sat_f32x4(vx_hi);

    v128_t vacc = wasm_i16x8_narrow_i32x4(vacc_lo, vacc_hi);
    vacc = wasm_i16x8_add_sat(vacc, voutput_zero_point);

    v128_t vy = wasm_i8x16_narrow_i16x8(vacc, vacc);
    vy = wasm_i8x16_max(vy, voutput_min);
    vy = wasm_i8x16_min(vy, voutput_max);

    if (n & (4 * sizeof(int8_t))) {
      *((float*) y) = wasm_f32x4_extract_lane(vy, 0);
      y += 4;
      vy = wasm_u64x2_shr(vy, 32);
    }
    uint32_t vy_lo = (uint32_t) wasm_i32x4_extract_lane(vy, 0);
    if (n & (2 * sizeof(int8_t))) {
      *((uint16_t*) y) = (uint16_t) vy_lo;
      y += 2;
      vy_lo >>= 16;
    }
    if (n & (1 * sizeof(int8_t))) {
      *y = (int8_t) vy_lo;
    }
  }
}