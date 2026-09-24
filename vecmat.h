/* Copyright 2024 Rikard Olajos
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <float.h>
#include <math.h>
#include <stdbool.h>

/* GCC and CLANG */
#if defined(__GNUC__) || defined(__clang__)

#if !defined(__SSE__)
#error "VECMAT: SSE is required"
#endif

#include <immintrin.h>
#define ALIGN(x) __attribute__((aligned(x)))

/* MSVC */
#elif defined(_MSC_VER)

#if !defined(_M_X64) && !(defined(_M_IX86_FP) && _M_IX86_FP >= 1)
#error "VECMAT: SSE is required"
#endif

#include <intrin.h>
#define ALIGN(x) __declspec(align(x))

#else
#error "VECMAT: Unknown compiler"
#endif


typedef ALIGN(16) union {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float array[4];
    __m128 sse;
} vec2;

typedef ALIGN(16) union {
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
    float array[4];
    __m128 sse;
} vec3;

typedef ALIGN(16) union {
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
    float array[4];
    __m128 sse;
} vec4;

typedef ALIGN(16) union {
    vec4 cols[4];
    float cr[4][4];
    float array[16];
} mat4;

/* Rotation quaternion, stored as (x, y, z, w) with w as the scalar part. The
 * layout matches vec4, glTF and GLSL. See the quaternion section below for the
 * conventions. */
typedef ALIGN(16) union {
    struct {
        float x, y, z, w;
    };
    float array[4];
    __m128 sse;
} quat;

/* Tightly packed storage types (8 and 12 bytes). Arrays of these match the GPU
 * vertex formats R32G32_SFLOAT and R32G32B32_SFLOAT. Convert to vec2/vec3 with
 * vec2_unpack()/vec3_unpack() to do math, and back with vec2_pack()/vec3_pack()
 */
typedef union {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float array[2];
} vec2_packed;

typedef union {
    struct {
        float x, y, z;
    };
    struct {
        float r, g, b;
    };
    float array[3];
} vec3_packed;

_Static_assert(sizeof(vec2_packed) == 8, "VECMAT: vec2_packed must be 8 bytes");
_Static_assert(sizeof(vec3_packed) == 12, "VECMAT: vec3_packed must be 12 bytes");


#ifdef VECMAT_USE_GENERICS

/* Add two generic types together */
#define vm_add(a, b)                                                           \
    _Generic((a),                                                              \
        vec2: _Generic((b), vec2: vec2_add, default: vec2_add),                \
        vec3: _Generic((b), vec3: vec3_add, default: vec3_add),                \
        vec4: _Generic((b), vec4: vec4_add, default: vec4_add),                \
        mat4: _Generic((b), mat4: mat4_add, default: mat4_add))(a, b)

/* Subtract two generic types from each other */
#define vm_sub(a, b)                                                           \
    _Generic((a),                                                              \
        vec2: _Generic((b), vec2: vec2_sub, default: vec2_sub),                \
        vec3: _Generic((b), vec3: vec3_sub, default: vec3_sub),                \
        vec4: _Generic((b), vec4: vec4_sub, default: vec4_sub),                \
        mat4: _Generic((b), mat4: mat4_sub, default: mat4_sub))(a, b)

/* Scalar multiplication of a generic type */
#define vm_scale(f, a)                                                         \
    _Generic((a),                                                              \
        vec2: vec2_scale,                                                      \
        vec3: vec3_scale,                                                      \
        vec4: vec4_scale,                                                      \
        mat4: mat4_scale)(f, a)

/* Dot multiplication of two vectors */
#define vm_dot(a, b)                                                           \
    _Generic((a),                                                              \
        vec2: _Generic((b), vec2: vec2_dot, default: vec2_dot),                \
        vec3: _Generic((b), vec3: vec3_dot, default: vec3_dot),                \
        vec4: _Generic((b), vec4: vec4_dot, default: vec4_dot),                \
        quat: _Generic((b), quat: quat_dot, default: quat_dot))(a, b)

/* Cross multiplication of two vec3 */
#define vm_cross(a, b)                                                         \
    _Generic((a), vec3: _Generic((b), vec3: vec3_cross))(a, b)

/* Calculate norm of a generic type */
#define vm_norm(a)                                                             \
    _Generic((a),                                                              \
        vec2: vec2_norm,                                                       \
        vec3: vec3_norm,                                                       \
        vec4: vec4_norm,                                                       \
        quat: quat_norm)(a)

/* Calculate normalized vector with same direction */
#define vm_normalize(a)                                                        \
    _Generic((a),                                                              \
        vec2: vec2_normalize,                                                  \
        vec3: vec3_normalize,                                                  \
        vec4: vec4_normalize,                                                  \
        quat: quat_normalize)(a)

#endif /* VECMAT_USE_GENERICS */


#define MAT4_IDENTITY                                                          \
    (mat4)                                                                     \
    {                                                                          \
        {                                                                      \
            {1.0f, 0.0f, 0.0f, 0.0f},                                          \
            {0.0f, 1.0f, 0.0f, 0.0f},                                          \
            {0.0f, 0.0f, 1.0f, 0.0f},                                          \
            {0.0f, 0.0f, 0.0f, 1.0f},                                          \
        },                                                                     \
    }

#define QUAT_IDENTITY                                                          \
    (quat)                                                                     \
    {                                                                          \
        {0.0f, 0.0f, 0.0f, 1.0f}                                               \
    }


/* Create a vec2, with the unused lanes set to zero */
static inline vec2 vec2_make(float x, float y)
{
    return (vec2){.sse = _mm_set_ps(0.0f, 0.0f, y, x)};
}

/* Create a vec3, with the unused lane set to zero */
static inline vec3 vec3_make(float x, float y, float z)
{
    return (vec3){.sse = _mm_set_ps(0.0f, z, y, x)};
}

/* Create a vec4 */
static inline vec4 vec4_make(float x, float y, float z, float w)
{
    return (vec4){.sse = _mm_set_ps(w, z, y, x)};
}


/* Convert a vec2 to its packed storage type */
static inline vec2_packed vec2_pack(vec2 v)
{
    return (vec2_packed){{v.x, v.y}};
}

/* Convert a vec3 to its packed storage type */
static inline vec3_packed vec3_pack(vec3 v)
{
    return (vec3_packed){{v.x, v.y, v.z}};
}

/* Convert a packed vec2 to a vec2, with the unused lanes set to zero */
static inline vec2 vec2_unpack(vec2_packed p)
{
    return vec2_make(p.x, p.y);
}

/* Convert a packed vec3 to a vec3, with the unused lane set to zero */
static inline vec3 vec3_unpack(vec3_packed p)
{
    return vec3_make(p.x, p.y, p.z);
}


/* Extend a vec3 to a vec4 with the given w */
static inline vec4 vec4_from_vec3(vec3 v, float w)
{
    return (vec4){.sse = _mm_set_ps(w, v.z, v.y, v.x)};
}

/* Drop the w component of a vec4 */
static inline vec3 vec3_from_vec4(vec4 v)
{
    return vec3_make(v.x, v.y, v.z);
}


/* Addition for vec2 */
static inline vec2 vec2_add(vec2 u, vec2 v)
{
    return (vec2){.sse = _mm_add_ps(u.sse, v.sse)};
}

/* Addition for vec3 */
static inline vec3 vec3_add(vec3 u, vec3 v)
{
    return (vec3){.sse = _mm_add_ps(u.sse, v.sse)};
}

/* Addition for vec4 */
static inline vec4 vec4_add(vec4 u, vec4 v)
{
    return (vec4){.sse = _mm_add_ps(u.sse, v.sse)};
}


/* Subtraction for vec2 */
static inline vec2 vec2_sub(vec2 u, vec2 v)
{
    return (vec2){.sse = _mm_sub_ps(u.sse, v.sse)};
}

/* Subtraction for vec3 */
static inline vec3 vec3_sub(vec3 u, vec3 v)
{
    return (vec3){.sse = _mm_sub_ps(u.sse, v.sse)};
}

/* Subtraction for vec4 */
static inline vec4 vec4_sub(vec4 u, vec4 v)
{
    return (vec4){.sse = _mm_sub_ps(u.sse, v.sse)};
}


/* Scalar multiplication for vec2 */
static inline vec2 vec2_scale(float f, vec2 u)
{
    return (vec2){.sse = _mm_mul_ps(_mm_set_ps1(f), u.sse)};
}

/* Scalar multiplication for vec3 */
static inline vec3 vec3_scale(float f, vec3 u)
{
    return (vec3){.sse = _mm_mul_ps(_mm_set_ps1(f), u.sse)};
}

/* Scalar multiplication for vec4 */
static inline vec4 vec4_scale(float f, vec4 u)
{
    return (vec4){.sse = _mm_mul_ps(_mm_set_ps1(f), u.sse)};
}


/* Dot multiplication for vec2 */
static inline float vec2_dot(vec2 u, vec2 v)
{
    __m128 p = _mm_mul_ps(u.sse, v.sse);
    __m128 y = _mm_shuffle_ps(p, p, _MM_SHUFFLE(1, 1, 1, 1));
    return _mm_cvtss_f32(_mm_add_ss(p, y));
}

/* Dot multiplication for vec3 */
static inline float vec3_dot(vec3 u, vec3 v)
{
    __m128 p = _mm_mul_ps(u.sse, v.sse);
    __m128 y = _mm_shuffle_ps(p, p, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 z = _mm_movehl_ps(p, p);
    return _mm_cvtss_f32(_mm_add_ss(_mm_add_ss(p, y), z));
}

/* Dot multiplication for vec4 */
static inline float vec4_dot(vec4 u, vec4 v)
{
    __m128 p = _mm_mul_ps(u.sse, v.sse);
    __m128 s = _mm_add_ps(p, _mm_movehl_ps(p, p));
    __m128 t = _mm_shuffle_ps(s, s, _MM_SHUFFLE(1, 1, 1, 1));
    return _mm_cvtss_f32(_mm_add_ss(s, t));
}


/* Cross multiplication for vec3 */
static inline vec3 vec3_cross(vec3 u, vec3 v)
{
    __m128 tmp0 = _mm_shuffle_ps(u.sse, u.sse, _MM_SHUFFLE(3, 0, 2, 1));
    __m128 tmp1 = _mm_shuffle_ps(v.sse, v.sse, _MM_SHUFFLE(3, 1, 0, 2));
    __m128 tmp2 = _mm_mul_ps(tmp0, v.sse);
    __m128 tmp3 = _mm_mul_ps(tmp0, tmp1);
    __m128 tmp4 = _mm_shuffle_ps(tmp2, tmp2, _MM_SHUFFLE(3, 0, 2, 1));
    return (vec3){.sse = _mm_sub_ps(tmp3, tmp4)};
}


/* Calculate the norm of a vec2 */
static inline float vec2_norm(vec2 u)
{
    return sqrtf(vec2_dot(u, u));
}

/* Calculate the norm of a vec3 */
static inline float vec3_norm(vec3 u)
{
    return sqrtf(vec3_dot(u, u));
}

/* Calculate the norm of a vec4 */
static inline float vec4_norm(vec4 u)
{
    return sqrtf(vec4_dot(u, u));
}


/* Normalization of vec2 */
static inline vec2 vec2_normalize(vec2 u)
{
    float n = vec2_norm(u);
    return n > 0.0f ? vec2_scale(1 / n, u) : u;
}

/* Normalization of vec3 */
static inline vec3 vec3_normalize(vec3 u)
{
    float n = vec3_norm(u);
    return n > 0.0f ? vec3_scale(1 / n, u) : u;
}

/* Normalization of vec4 */
static inline vec4 vec4_normalize(vec4 u)
{
    float n = vec4_norm(u);
    return n > 0.0f ? vec4_scale(1 / n, u) : u;
}


/* Transpose matrix */
static inline mat4 mat4_transpose(mat4 m)
{
    _MM_TRANSPOSE4_PS(m.cols[0].sse, m.cols[1].sse, m.cols[2].sse,
                      m.cols[3].sse);
    return m;
}


/* Add two matrices together */
static inline mat4 mat4_add(mat4 m, mat4 n)
{
    mat4 res;
    for (int i = 0; i < 4; i++) {
        res.cols[i] = vec4_add(m.cols[i], n.cols[i]);
    }
    return res;
}


/* Subtract two matrices */
static inline mat4 mat4_sub(mat4 m, mat4 n)
{
    mat4 res;
    for (int i = 0; i < 4; i++) {
        res.cols[i] = vec4_sub(m.cols[i], n.cols[i]);
    }
    return res;
}


/* Scalar multiplication of matrix */
static inline mat4 mat4_scale(float f, mat4 m)
{
    mat4 res;
    for (int i = 0; i < 4; i++) {
        res.cols[i] = vec4_scale(f, m.cols[i]);
    }
    return res;
}


/* Matrix-vector multiplication */
static inline vec4 mat4_mul_vec4(mat4 m, vec4 v)
{
    __m128 x = _mm_shuffle_ps(v.sse, v.sse, _MM_SHUFFLE(0, 0, 0, 0));
    __m128 y = _mm_shuffle_ps(v.sse, v.sse, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 z = _mm_shuffle_ps(v.sse, v.sse, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 w = _mm_shuffle_ps(v.sse, v.sse, _MM_SHUFFLE(3, 3, 3, 3));
    __m128 xy =
        _mm_add_ps(_mm_mul_ps(m.cols[0].sse, x), _mm_mul_ps(m.cols[1].sse, y));
    __m128 zw =
        _mm_add_ps(_mm_mul_ps(m.cols[2].sse, z), _mm_mul_ps(m.cols[3].sse, w));
    return (vec4){.sse = _mm_add_ps(xy, zw)};
}


/* Matrix multiplication */
static inline mat4 mat4_mul(mat4 m, mat4 n)
{
    mat4 res;
    res.cols[0] = mat4_mul_vec4(m, n.cols[0]);
    res.cols[1] = mat4_mul_vec4(m, n.cols[1]);
    res.cols[2] = mat4_mul_vec4(m, n.cols[2]);
    res.cols[3] = mat4_mul_vec4(m, n.cols[3]);
    return res;
}


/* Adjugate matrix, with the determinant of m written to det */
static inline mat4 mat4_adjugate(mat4 m, float* det)
{
    mat4 a;

    a.array[0] = m.array[5] * m.array[10] * m.array[15] -
                 m.array[5] * m.array[11] * m.array[14] -
                 m.array[9] * m.array[6] * m.array[15] +
                 m.array[9] * m.array[7] * m.array[14] +
                 m.array[13] * m.array[6] * m.array[11] -
                 m.array[13] * m.array[7] * m.array[10];

    a.array[4] = -m.array[4] * m.array[10] * m.array[15] +
                 m.array[4] * m.array[11] * m.array[14] +
                 m.array[8] * m.array[6] * m.array[15] -
                 m.array[8] * m.array[7] * m.array[14] -
                 m.array[12] * m.array[6] * m.array[11] +
                 m.array[12] * m.array[7] * m.array[10];

    a.array[8] = m.array[4] * m.array[9] * m.array[15] -
                 m.array[4] * m.array[11] * m.array[13] -
                 m.array[8] * m.array[5] * m.array[15] +
                 m.array[8] * m.array[7] * m.array[13] +
                 m.array[12] * m.array[5] * m.array[11] -
                 m.array[12] * m.array[7] * m.array[9];

    a.array[12] = -m.array[4] * m.array[9] * m.array[14] +
                  m.array[4] * m.array[10] * m.array[13] +
                  m.array[8] * m.array[5] * m.array[14] -
                  m.array[8] * m.array[6] * m.array[13] -
                  m.array[12] * m.array[5] * m.array[10] +
                  m.array[12] * m.array[6] * m.array[9];

    a.array[1] = -m.array[1] * m.array[10] * m.array[15] +
                 m.array[1] * m.array[11] * m.array[14] +
                 m.array[9] * m.array[2] * m.array[15] -
                 m.array[9] * m.array[3] * m.array[14] -
                 m.array[13] * m.array[2] * m.array[11] +
                 m.array[13] * m.array[3] * m.array[10];

    a.array[5] = m.array[0] * m.array[10] * m.array[15] -
                 m.array[0] * m.array[11] * m.array[14] -
                 m.array[8] * m.array[2] * m.array[15] +
                 m.array[8] * m.array[3] * m.array[14] +
                 m.array[12] * m.array[2] * m.array[11] -
                 m.array[12] * m.array[3] * m.array[10];

    a.array[9] = -m.array[0] * m.array[9] * m.array[15] +
                 m.array[0] * m.array[11] * m.array[13] +
                 m.array[8] * m.array[1] * m.array[15] -
                 m.array[8] * m.array[3] * m.array[13] -
                 m.array[12] * m.array[1] * m.array[11] +
                 m.array[12] * m.array[3] * m.array[9];

    a.array[13] = m.array[0] * m.array[9] * m.array[14] -
                  m.array[0] * m.array[10] * m.array[13] -
                  m.array[8] * m.array[1] * m.array[14] +
                  m.array[8] * m.array[2] * m.array[13] +
                  m.array[12] * m.array[1] * m.array[10] -
                  m.array[12] * m.array[2] * m.array[9];

    a.array[2] = m.array[1] * m.array[6] * m.array[15] -
                 m.array[1] * m.array[7] * m.array[14] -
                 m.array[5] * m.array[2] * m.array[15] +
                 m.array[5] * m.array[3] * m.array[14] +
                 m.array[13] * m.array[2] * m.array[7] -
                 m.array[13] * m.array[3] * m.array[6];

    a.array[6] = -m.array[0] * m.array[6] * m.array[15] +
                 m.array[0] * m.array[7] * m.array[14] +
                 m.array[4] * m.array[2] * m.array[15] -
                 m.array[4] * m.array[3] * m.array[14] -
                 m.array[12] * m.array[2] * m.array[7] +
                 m.array[12] * m.array[3] * m.array[6];

    a.array[10] = m.array[0] * m.array[5] * m.array[15] -
                  m.array[0] * m.array[7] * m.array[13] -
                  m.array[4] * m.array[1] * m.array[15] +
                  m.array[4] * m.array[3] * m.array[13] +
                  m.array[12] * m.array[1] * m.array[7] -
                  m.array[12] * m.array[3] * m.array[5];

    a.array[14] = -m.array[0] * m.array[5] * m.array[14] +
                  m.array[0] * m.array[6] * m.array[13] +
                  m.array[4] * m.array[1] * m.array[14] -
                  m.array[4] * m.array[2] * m.array[13] -
                  m.array[12] * m.array[1] * m.array[6] +
                  m.array[12] * m.array[2] * m.array[5];

    a.array[3] = -m.array[1] * m.array[6] * m.array[11] +
                 m.array[1] * m.array[7] * m.array[10] +
                 m.array[5] * m.array[2] * m.array[11] -
                 m.array[5] * m.array[3] * m.array[10] -
                 m.array[9] * m.array[2] * m.array[7] +
                 m.array[9] * m.array[3] * m.array[6];

    a.array[7] = m.array[0] * m.array[6] * m.array[11] -
                 m.array[0] * m.array[7] * m.array[10] -
                 m.array[4] * m.array[2] * m.array[11] +
                 m.array[4] * m.array[3] * m.array[10] +
                 m.array[8] * m.array[2] * m.array[7] -
                 m.array[8] * m.array[3] * m.array[6];

    a.array[11] = -m.array[0] * m.array[5] * m.array[11] +
                  m.array[0] * m.array[7] * m.array[9] +
                  m.array[4] * m.array[1] * m.array[11] -
                  m.array[4] * m.array[3] * m.array[9] -
                  m.array[8] * m.array[1] * m.array[7] +
                  m.array[8] * m.array[3] * m.array[5];

    a.array[15] = m.array[0] * m.array[5] * m.array[10] -
                  m.array[0] * m.array[6] * m.array[9] -
                  m.array[4] * m.array[1] * m.array[10] +
                  m.array[4] * m.array[2] * m.array[9] +
                  m.array[8] * m.array[1] * m.array[6] -
                  m.array[8] * m.array[2] * m.array[5];

    *det = m.array[0] * a.array[0] + m.array[1] * a.array[4] +
           m.array[2] * a.array[8] + m.array[3] * a.array[12];

    return a;
}


/* Matrix inverse, m must be invertible (see mat4_try_inverse) */
static inline mat4 mat4_inverse(mat4 m)
{
    float det;
    mat4 a = mat4_adjugate(m, &det);
    return mat4_scale(1 / det, a);
}


/* Matrix inverse, returns false and leaves res untouched if m is singular */
static inline bool mat4_try_inverse(mat4 m, mat4* res)
{
    float det;
    mat4 a = mat4_adjugate(m, &det);

    /* Plain comparisons instead of isfinite(), which -ffast-math may remove.
     * Written so that NaN also fails the check. */
    float abs_det = fabsf(det);
    if (!(abs_det >= FLT_MIN && abs_det <= FLT_MAX)) {
        return false;
    }
    *res = mat4_scale(1 / det, a);
    return true;
}


/* Scale transform matrix */
static inline mat4 mat4_trs_scale(vec3 v1)
{
    return (mat4){
        {{v1.x, 0, 0, 0}, {0, v1.y, 0, 0}, {0, 0, v1.z, 0}, {0, 0, 0, 1}}};
}


/* Rotation transform matrix */
static inline mat4 mat4_trs_rotate(float angle, vec3 axis)
{
    axis = vec3_normalize(axis);
    return mat4_transpose((mat4){{
        {powf(axis.x, 2) + (1 - powf(axis.x, 2)) * cosf(angle),
         axis.x * axis.y * (1 - cosf(angle)) - axis.z * sinf(angle),
         axis.x * axis.z * (1 - cosf(angle)) + axis.y * sinf(angle), 0},
        {axis.x * axis.y * (1 - cosf(angle)) + axis.z * sinf(angle),
         powf(axis.y, 2) + (1 - powf(axis.y, 2)) * cosf(angle),
         axis.y * axis.z * (1 - cosf(angle)) - axis.x * sinf(angle), 0},
        {axis.x * axis.z * (1 - cosf(angle)) - axis.y * sinf(angle),
         axis.y * axis.z * (1 - cosf(angle)) + axis.x * sinf(angle),
         powf(axis.z, 2) + (1 - powf(axis.z, 2)) * cosf(angle), 0},
        {0, 0, 0, 1},
    }});
}


/* Translation transform matrix */
static inline mat4 mat4_trs_translate(vec3 v1)
{
    return (mat4){{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {v1.x, v1.y, v1.z, 1.0f},
    }};
}


/* Rotate v around axis with angle */
static inline vec3 vec3_rotate(vec3 v, float angle, vec3 axis)
{
    axis = vec3_normalize(axis);
    vec3 q = vec3_scale(sinf(angle / 2.0f), axis);
    vec3 t = vec3_cross(vec3_scale(2.0f, q), v);
    return vec3_add(vec3_add(v, vec3_scale(cosf(angle / 2.0f), t)),
                    vec3_cross(q, t));
}


/* Quaternions
 *
 * Conventions:
 *  - Hamilton quaternions (i^2 = j^2 = k^2 = ijk = -1), stored as (x, y, z, w)
 *    with w as the scalar part.
 *  - Rotations are active and right-handed, the same as mat4_trs_rotate().
 *  - quat_mul(a, b) applies b first and then a, the same as mat4_mul().
 *  - Functions that rotate assume unit quaternions. Renormalize with
 *    quat_normalize() after long chains of multiplications.
 *  - q and -q represent the same rotation.
 */

/* Create a quaternion from its components, in storage order */
static inline quat quat_make(float x, float y, float z, float w)
{
    return (quat){.sse = _mm_set_ps(w, z, y, x)};
}

/* Unit quaternion rotating angle radians around axis, which must be non-zero */
static inline quat quat_from_axis_angle(float angle, vec3 axis)
{
    axis = vec3_normalize(axis);
    float s = sinf(angle / 2.0f);
    return quat_make(s * axis.x, s * axis.y, s * axis.z, cosf(angle / 2.0f));
}


/* Quaternion multiplication, the rotation b followed by a */
static inline quat quat_mul(quat a, quat b)
{
    /* a * b = aw * (bx,  by,  bz, bw) + ax * ( bw, -bz,  by, -bx)
     *       + ay * (bz,  bw, -bx, -by) + az * (-by,  bx,  bw, -bz)
     * The signs are flipped with xor masks. They are built from integer bits,
     * as -ffast-math may turn a -0.0f constant into 0.0f and break the mask. */
    static const union {
        unsigned int bits[3][4];
        __m128 sse[3];
    } signs = {{
        {0, 0x80000000u, 0, 0x80000000u},
        {0, 0, 0x80000000u, 0x80000000u},
        {0x80000000u, 0, 0, 0x80000000u},
    }};
    __m128 ax = _mm_shuffle_ps(a.sse, a.sse, _MM_SHUFFLE(0, 0, 0, 0));
    __m128 ay = _mm_shuffle_ps(a.sse, a.sse, _MM_SHUFFLE(1, 1, 1, 1));
    __m128 az = _mm_shuffle_ps(a.sse, a.sse, _MM_SHUFFLE(2, 2, 2, 2));
    __m128 aw = _mm_shuffle_ps(a.sse, a.sse, _MM_SHUFFLE(3, 3, 3, 3));
    __m128 b_wzyx = _mm_shuffle_ps(b.sse, b.sse, _MM_SHUFFLE(0, 1, 2, 3));
    __m128 b_zwxy = _mm_shuffle_ps(b.sse, b.sse, _MM_SHUFFLE(1, 0, 3, 2));
    __m128 b_yxwz = _mm_shuffle_ps(b.sse, b.sse, _MM_SHUFFLE(2, 3, 0, 1));
    __m128 tw = _mm_mul_ps(aw, b.sse);
    __m128 tx = _mm_xor_ps(_mm_mul_ps(ax, b_wzyx), signs.sse[0]);
    __m128 ty = _mm_xor_ps(_mm_mul_ps(ay, b_zwxy), signs.sse[1]);
    __m128 tz = _mm_xor_ps(_mm_mul_ps(az, b_yxwz), signs.sse[2]);
    return (quat){.sse = _mm_add_ps(_mm_add_ps(tw, tx), _mm_add_ps(ty, tz))};
}


/* Dot product of two quaternions */
static inline float quat_dot(quat a, quat b)
{
    return vec4_dot((vec4){.sse = a.sse}, (vec4){.sse = b.sse});
}

/* Calculate the norm of a quaternion */
static inline float quat_norm(quat q)
{
    return sqrtf(quat_dot(q, q));
}

/* Normalization of a quaternion */
static inline quat quat_normalize(quat q)
{
    return (quat){.sse = vec4_normalize((vec4){.sse = q.sse}).sse};
}


/* Conjugate of a quaternion, which is the inverse of a unit quaternion */
static inline quat quat_conjugate(quat q)
{
    __m128 signs = _mm_set_ps(1.0f, -1.0f, -1.0f, -1.0f);
    return (quat){.sse = _mm_mul_ps(q.sse, signs)};
}

/* Inverse of a quaternion, which must be non-zero */
static inline quat quat_inverse(quat q)
{
    __m128 n = _mm_set_ps1(quat_dot(q, q));
    return (quat){.sse = _mm_div_ps(quat_conjugate(q).sse, n)};
}


/* Rotate a vec3 by a unit quaternion */
static inline vec3 quat_rotate_vec3(quat q, vec3 v)
{
    vec3 u = vec3_make(q.x, q.y, q.z);
    vec3 t = vec3_scale(2.0f, vec3_cross(u, v));
    return vec3_add(vec3_add(v, vec3_scale(q.w, t)), vec3_cross(u, t));
}


/* Rotation matrix of a unit quaternion */
static inline mat4 mat4_from_quat(quat q)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    return (mat4){{
        {1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy), 0.0f},
        {2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx), 0.0f},
        {2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
    }};
}


/* Normalized linear interpolation between two unit quaternions along the
 * shortest path. Cheaper than quat_slerp(), but the angular speed is not
 * constant over t. */
static inline quat quat_nlerp(quat a, quat b, float t)
{
    /* q and -q are the same rotation, pick the one closest to a */
    float sign = quat_dot(a, b) < 0.0f ? -1.0f : 1.0f;
    __m128 wa = _mm_set_ps1(1.0f - t);
    __m128 wb = _mm_set_ps1(sign * t);
    quat q = {.sse = _mm_add_ps(_mm_mul_ps(wa, a.sse), _mm_mul_ps(wb, b.sse))};
    return quat_normalize(q);
}

/* Spherical linear interpolation between two unit quaternions along the
 * shortest path, with constant angular speed over t */
static inline quat quat_slerp(quat a, quat b, float t)
{
    /* q and -q are the same rotation, pick the one closest to a */
    float d = quat_dot(a, b);
    float sign = 1.0f;
    if (d < 0.0f) {
        d = -d;
        sign = -1.0f;
    }

    /* Nearly parallel: sin(theta) is close to zero, fall back to nlerp */
    if (d > 0.9995f) {
        return quat_nlerp(a, b, t);
    }

    float theta = acosf(d);
    float s = sinf(theta);
    __m128 wa = _mm_set_ps1(sinf((1.0f - t) * theta) / s);
    __m128 wb = _mm_set_ps1(sign * sinf(t * theta) / s);
    return (quat){
        .sse = _mm_add_ps(_mm_mul_ps(wa, a.sse), _mm_mul_ps(wb, b.sse))};
}


/* Return a orthographic projection matrix */
static inline mat4 mat4_orthographic(float right, float top, float zNear,
                                     float zFar)
{
    return mat4_transpose((mat4){{
        {1.0f / right, 0.0f, 0.0f, 0.0f},
        {0.0f, -1.0f / top, 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f / (zFar - zNear), -zNear / (zFar - zNear)},
        {0.0f, 0.0f, 0.0f, 1.0f},
    }});
}


/* Return a perspective projection matrix */
static inline mat4 mat4_perspective(int width, int height, float zNear,
                                    float zFar, float fov)
{
    float f = tanf(1.57079632679f - 0.5f * fov);
    float aspect = (float)width / (float)height;
    float depth = (-zFar) / (zFar - zNear);
    return mat4_transpose((mat4){{{f / aspect, 0.0f, 0.0f, 0.0f},
                                  {0.0f, -f, 0.0f, 0.0f},
                                  {0.0f, 0.0f, depth, zNear * depth},
                                  {0.0f, 0.0f, -1.0f, 0.0f}}});
}


/* Return a rotation matrix oriented towards the target */
static inline mat4 mat4_lookat(vec3 pos, vec3 target, vec3 up)
{
    vec3 f = vec3_normalize(vec3_sub(pos, target));
    vec3 u = vec3_normalize(up);
    vec3 s = vec3_normalize(vec3_cross(u, f));
    u = vec3_cross(f, s);

    return mat4_transpose((mat4){{{s.x, s.y, s.z, -vec3_dot(s, pos)},
                                  {u.x, u.y, u.z, -vec3_dot(u, pos)},
                                  {f.x, f.y, f.z, -vec3_dot(f, pos)},
                                  {0.0f, 0.0f, 0.0f, 1.0f}}});
}
