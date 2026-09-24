#define VECMAT_USE_GENERICS
#include "vecmat.h"

#include <assert.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>

#define EPSILON 2.0f * FLT_EPSILON

bool equal(float a, float b)
{
    return fabsf(a - b) < EPSILON;
}

/* Compare all elements of two matrices with the given tolerance */
bool matrices_close(mat4 a, mat4 b, float tolerance)
{
    for (int i = 0; i < 16; i++) {
        if (fabsf(a.array[i] - b.array[i]) >= tolerance) {
            return false;
        }
    }
    return true;
}

void test_add()
{
    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 u2 = vec2_make(3.0f, 4.0f);
    vec2 r2 = vec2_add(v2, u2);

    assert(equal(r2.x, 4.0f));
    assert(equal(r2.y, 6.0f));

    /* Vector 2 generic */
    vec2 g2 = vm_add(v2, u2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 u3 = vec3_make(4.0f, 5.0f, 6.0f);
    vec3 r3 = vec3_add(v3, u3);

    assert(equal(r3.x, 5.0f));
    assert(equal(r3.y, 7.0f));
    assert(equal(r3.z, 9.0f));

    /* Vector 3 generic */
    vec3 g3 = vm_add(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 u4 = vec4_make(5.0f, 6.0f, 7.0f, 8.0f);
    vec4 r4 = vec4_add(v4, u4);

    assert(equal(r4.x, 6.0f));
    assert(equal(r4.y, 8.0f));
    assert(equal(r4.z, 10.0f));
    assert(equal(r4.w, 12.0f));

    /* Vector 4 generic */
    vec4 g4 = vm_add(v4, u4);
    assert(equal(g4.x, r4.x));
    assert(equal(g4.y, r4.y));
    assert(equal(g4.z, r4.z));
    assert(equal(g4.w, r4.w));

    /* Matrix 4x4 */
    mat4 m4x4 = {v4, v4, v4, v4};
    mat4 n4x4 = {u4, u4, u4, u4};
    mat4 r4x4 = vm_add(m4x4, n4x4);
    assert(equal(r4x4.array[0], r4.x));
    assert(equal(r4x4.array[1], r4.y));
    assert(equal(r4x4.array[2], r4.z));
    assert(equal(r4x4.array[3], r4.w));
    assert(equal(r4x4.array[4], r4.x));
    assert(equal(r4x4.array[5], r4.y));
    assert(equal(r4x4.array[6], r4.z));
    assert(equal(r4x4.array[7], r4.w));
    assert(equal(r4x4.array[8], r4.x));
    assert(equal(r4x4.array[9], r4.y));
    assert(equal(r4x4.array[10], r4.z));
    assert(equal(r4x4.array[11], r4.w));
    assert(equal(r4x4.array[12], r4.x));
    assert(equal(r4x4.array[13], r4.y));
    assert(equal(r4x4.array[14], r4.z));
    assert(equal(r4x4.array[15], r4.w));

    /* Matrix 4x4 generic */
    mat4 g4x4 = vm_add(m4x4, n4x4);
    assert(equal(g4x4.array[0], r4.x));
    assert(equal(g4x4.array[1], r4.y));
    assert(equal(g4x4.array[2], r4.z));
    assert(equal(g4x4.array[3], r4.w));
    assert(equal(g4x4.array[4], r4.x));
    assert(equal(g4x4.array[5], r4.y));
    assert(equal(g4x4.array[6], r4.z));
    assert(equal(g4x4.array[7], r4.w));
    assert(equal(g4x4.array[8], r4.x));
    assert(equal(g4x4.array[9], r4.y));
    assert(equal(g4x4.array[10], r4.z));
    assert(equal(g4x4.array[11], r4.w));
    assert(equal(g4x4.array[12], r4.x));
    assert(equal(g4x4.array[13], r4.y));
    assert(equal(g4x4.array[14], r4.z));
    assert(equal(g4x4.array[15], r4.w));
}

void test_sub()
{
    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 u2 = vec2_make(3.0f, 4.0f);
    vec2 r2 = vec2_sub(v2, u2);

    assert(equal(r2.x, -2.0f));
    assert(equal(r2.y, -2.0f));

    /* Vector 2 generic */
    vec2 g2 = vm_sub(v2, u2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 u3 = vec3_make(4.0f, 5.0f, 6.0f);
    vec3 r3 = vec3_sub(v3, u3);

    assert(equal(r3.x, -3.0f));
    assert(equal(r3.y, -3.0f));
    assert(equal(r3.z, -3.0f));

    /* Vector 3 generic */
    vec3 g3 = vm_sub(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 u4 = vec4_make(5.0f, 6.0f, 7.0f, 8.0f);
    vec4 r4 = vec4_sub(v4, u4);

    assert(equal(r4.x, -4.0f));
    assert(equal(r4.y, -4.0f));
    assert(equal(r4.z, -4.0f));
    assert(equal(r4.w, -4.0f));

    /* Vector 4 generic */
    vec4 g4 = vm_sub(v4, u4);
    assert(equal(g4.x, r4.x));
    assert(equal(g4.y, r4.y));
    assert(equal(g4.z, r4.z));
    assert(equal(g4.w, r4.w));

    /* Matrix 4x4 */
    mat4 m4x4 = {v4, v4, v4, v4};
    mat4 n4x4 = {u4, u4, u4, u4};
    mat4 r4x4 = vm_sub(m4x4, n4x4);
    assert(equal(r4x4.array[0], r4.x));
    assert(equal(r4x4.array[1], r4.y));
    assert(equal(r4x4.array[2], r4.z));
    assert(equal(r4x4.array[3], r4.w));
    assert(equal(r4x4.array[4], r4.x));
    assert(equal(r4x4.array[5], r4.y));
    assert(equal(r4x4.array[6], r4.z));
    assert(equal(r4x4.array[7], r4.w));
    assert(equal(r4x4.array[8], r4.x));
    assert(equal(r4x4.array[9], r4.y));
    assert(equal(r4x4.array[10], r4.z));
    assert(equal(r4x4.array[11], r4.w));
    assert(equal(r4x4.array[12], r4.x));
    assert(equal(r4x4.array[13], r4.y));
    assert(equal(r4x4.array[14], r4.z));
    assert(equal(r4x4.array[15], r4.w));

    /* Matrix 4x4 generic */
    mat4 g4x4 = vm_sub(m4x4, n4x4);
    assert(equal(g4x4.array[0], r4.x));
    assert(equal(g4x4.array[1], r4.y));
    assert(equal(g4x4.array[2], r4.z));
    assert(equal(g4x4.array[3], r4.w));
    assert(equal(g4x4.array[4], r4.x));
    assert(equal(g4x4.array[5], r4.y));
    assert(equal(g4x4.array[6], r4.z));
    assert(equal(g4x4.array[7], r4.w));
    assert(equal(g4x4.array[8], r4.x));
    assert(equal(g4x4.array[9], r4.y));
    assert(equal(g4x4.array[10], r4.z));
    assert(equal(g4x4.array[11], r4.w));
    assert(equal(g4x4.array[12], r4.x));
    assert(equal(g4x4.array[13], r4.y));
    assert(equal(g4x4.array[14], r4.z));
    assert(equal(g4x4.array[15], r4.w));
}

void test_scale()
{
    float s = 2.0f;

    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 r2 = vec2_scale(s, v2);

    assert(equal(r2.x, 2.0f));
    assert(equal(r2.y, 4.0f));

    /* Vector 2 generic */
    vec2 g2 = vm_scale(s, v2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 r3 = vec3_scale(s, v3);

    assert(equal(r3.x, 2.0f));
    assert(equal(r3.y, 4.0f));
    assert(equal(r3.z, 6.0f));

    /* Vector 3 generic */
    vec3 g3 = vm_scale(s, v3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 r4 = vec4_scale(s, v4);

    assert(equal(r4.x, 2.0f));
    assert(equal(r4.y, 4.0f));
    assert(equal(r4.z, 6.0f));
    assert(equal(r4.w, 8.0f));

    /* Vector 4 generic */
    vec4 g4 = vm_scale(s, v4);
    assert(equal(g4.x, r4.x));
    assert(equal(g4.y, r4.y));
    assert(equal(g4.z, r4.z));
    assert(equal(g4.w, r4.w));

    /* Matrix 4x4 */
    mat4 m4x4 = {v4, v4, v4, v4};
    mat4 r4x4 = mat4_scale(s, m4x4);
    assert(equal(r4x4.array[0], r4.x));
    assert(equal(r4x4.array[1], r4.y));
    assert(equal(r4x4.array[2], r4.z));
    assert(equal(r4x4.array[3], r4.w));
    assert(equal(r4x4.array[4], r4.x));
    assert(equal(r4x4.array[5], r4.y));
    assert(equal(r4x4.array[6], r4.z));
    assert(equal(r4x4.array[7], r4.w));
    assert(equal(r4x4.array[8], r4.x));
    assert(equal(r4x4.array[9], r4.y));
    assert(equal(r4x4.array[10], r4.z));
    assert(equal(r4x4.array[11], r4.w));
    assert(equal(r4x4.array[12], r4.x));
    assert(equal(r4x4.array[13], r4.y));
    assert(equal(r4x4.array[14], r4.z));
    assert(equal(r4x4.array[15], r4.w));

    /* Matrix 4x4 generic */
    mat4 g4x4 = vm_scale(s, m4x4);
    assert(equal(g4x4.array[0], r4.x));
    assert(equal(g4x4.array[1], r4.y));
    assert(equal(g4x4.array[2], r4.z));
    assert(equal(g4x4.array[3], r4.w));
    assert(equal(g4x4.array[4], r4.x));
    assert(equal(g4x4.array[5], r4.y));
    assert(equal(g4x4.array[6], r4.z));
    assert(equal(g4x4.array[7], r4.w));
    assert(equal(g4x4.array[8], r4.x));
    assert(equal(g4x4.array[9], r4.y));
    assert(equal(g4x4.array[10], r4.z));
    assert(equal(g4x4.array[11], r4.w));
    assert(equal(g4x4.array[12], r4.x));
    assert(equal(g4x4.array[13], r4.y));
    assert(equal(g4x4.array[14], r4.z));
    assert(equal(g4x4.array[15], r4.w));
}

void test_dot()
{
    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 u2 = vec2_make(3.0f, 4.0f);
    float r2 = vec2_dot(v2, u2);

    assert(equal(r2, 11.0f));

    /* Vector 2 generic */
    float g2 = vm_dot(v2, u2);
    assert(equal(g2, r2));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 u3 = vec3_make(4.0f, 5.0f, 6.0f);
    float r3 = vec3_dot(v3, u3);

    assert(equal(r3, 32.0f));

    /* Vector 3 generic */
    float g3 = vm_dot(v3, u3);
    assert(equal(g3, r3));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 u4 = vec4_make(5.0f, 6.0f, 7.0f, 8.0f);
    float r4 = vec4_dot(v4, u4);

    assert(equal(r4, 70.0f));

    /* Vector 4 generic */
    float g4 = vm_dot(v4, u4);
    assert(equal(g4, r4));
}

void test_cross()
{
    vec3 v3 = vec3_make(1.0f, 0.0f, 0.0f);
    vec3 u3 = vec3_make(0.0f, 1.0f, 0.0f);
    vec3 r3 = vec3_cross(v3, u3);

    assert(equal(r3.x, 0.0f));
    assert(equal(r3.y, 0.0f));
    assert(equal(r3.z, 1.0f));

    vec3 g3 = vm_cross(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));
}

void test_norm()
{
    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 0.0f);
    float r2 = vec2_norm(v2);
    assert(equal(r2, 1.0f));

    /* Vector 2 generic */
    float g2 = vm_norm(v2);
    assert(equal(g2, r2));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 0.0f, 0.0f);
    float r3 = vec3_norm(v3);
    assert(equal(r3, 1.0f));

    /* Vector 3 generic */
    float g3 = vm_norm(v3);
    assert(equal(g3, r3));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 0.0f, 0.0f, 0.0f);
    float r4 = vec4_norm(v4);
    assert(equal(r4, 1.0f));

    /* Vector 4 generic */
    float g4 = vm_norm(v4);
    assert(equal(g4, r4));
}

void test_normalize()
{
    /* Vector 2 */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 r2 = vec2_normalize(v2);
    assert(equal(vm_norm(r2), 1.0f));

    /* Vector 2 generic */
    vec2 g2 = vm_normalize(v2);
    assert(equal(vm_norm(g2), vm_norm(r2)));

    /* Vector 3 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 r3 = vec3_normalize(v3);
    assert(equal(vm_norm(r3), 1.0f));

    /* Vector 3 generic */
    vec3 g3 = vm_normalize(v3);
    assert(equal(vm_norm(g3), vm_norm(r3)));

    /* Vector 4 */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 r4 = vec4_normalize(v4);
    assert(equal(vm_norm(r4), 1.0f));

    /* Vector 4 generic */
    vec4 g4 = vm_normalize(v4);
    assert(equal(vm_norm(g4), vm_norm(r4)));
}

void test_packed()
{
    /* Sizes and array strides match the GPU vertex formats */
    vec2_packed a2[2];
    vec3_packed a3[2];
    assert(sizeof(vec2_packed) == 8);
    assert(sizeof(vec3_packed) == 12);
    assert((char *)&a2[1] - (char *)&a2[0] == 8);
    assert((char *)&a3[1] - (char *)&a3[0] == 12);

    /* Vector 2 pack */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2_packed p2 = vec2_pack(v2);
    assert(equal(p2.x, 1.0f));
    assert(equal(p2.y, 2.0f));

    /* Vector 2 unpack, with the unused lanes set to zero */
    vec2 u2 = vec2_unpack(p2);
    assert(equal(u2.x, 1.0f));
    assert(equal(u2.y, 2.0f));
    assert(u2.array[2] == 0.0f);
    assert(u2.array[3] == 0.0f);

    /* Vector 3 pack */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3_packed p3 = vec3_pack(v3);
    assert(equal(p3.x, 1.0f));
    assert(equal(p3.y, 2.0f));
    assert(equal(p3.z, 3.0f));

    /* Vector 3 unpack, with the unused lane set to zero */
    vec3 u3 = vec3_unpack(p3);
    assert(equal(u3.x, 1.0f));
    assert(equal(u3.y, 2.0f));
    assert(equal(u3.z, 3.0f));
    assert(u3.array[3] == 0.0f);

    /* Packed arrays are contiguous floats */
    a3[0] = vec3_pack(vec3_make(1.0f, 2.0f, 3.0f));
    a3[1] = vec3_pack(vec3_make(4.0f, 5.0f, 6.0f));
    float *f = a3[0].array;
    for (int i = 0; i < 6; i++) {
        assert(equal(f[i], (float)(i + 1)));
    }

    /* Math on unpacked values survives a round trip */
    vec3 r3 = vec3_add(vec3_unpack(a3[0]), vec3_unpack(a3[1]));
    vec3_packed q3 = vec3_pack(r3);
    assert(equal(q3.x, 5.0f));
    assert(equal(q3.y, 7.0f));
    assert(equal(q3.z, 9.0f));
}

void test_convert()
{
    /* Vector 3 to vector 4 */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec4 r4 = vec4_from_vec3(v3, 4.0f);
    assert(equal(r4.x, 1.0f));
    assert(equal(r4.y, 2.0f));
    assert(equal(r4.z, 3.0f));
    assert(equal(r4.w, 4.0f));

    /* Vector 4 to vector 3, with the unused lane set to zero */
    vec4 v4 = vec4_make(5.0f, 6.0f, 7.0f, 8.0f);
    vec3 r3 = vec3_from_vec4(v4);
    assert(equal(r3.x, 5.0f));
    assert(equal(r3.y, 6.0f));
    assert(equal(r3.z, 7.0f));
    assert(r3.array[3] == 0.0f);

    /* Round trip */
    vec3 g3 = vec3_from_vec4(vec4_from_vec3(v3, 1.0f));
    assert(equal(g3.x, v3.x));
    assert(equal(g3.y, v3.y));
    assert(equal(g3.z, v3.z));
}

void test_mat4_mul_vec4()
{
    /* Columns (1, 2, 3, 4), (5, 6, 7, 8), (9, 10, 11, 12), (13, 14, 15, 16) */
    mat4 m = {{
        vec4_make(1.0f, 2.0f, 3.0f, 4.0f),
        vec4_make(5.0f, 6.0f, 7.0f, 8.0f),
        vec4_make(9.0f, 10.0f, 11.0f, 12.0f),
        vec4_make(13.0f, 14.0f, 15.0f, 16.0f),
    }};

    /* A unit vector picks out a column */
    vec4 c1 = mat4_mul_vec4(m, vec4_make(0.0f, 1.0f, 0.0f, 0.0f));
    assert(equal(c1.x, 5.0f));
    assert(equal(c1.y, 6.0f));
    assert(equal(c1.z, 7.0f));
    assert(equal(c1.w, 8.0f));

    /* General case: 1 * col0 + 2 * col1 + 3 * col2 + 4 * col3 */
    vec4 r4 = mat4_mul_vec4(m, vec4_make(1.0f, 2.0f, 3.0f, 4.0f));
    assert(equal(r4.x, 90.0f));
    assert(equal(r4.y, 100.0f));
    assert(equal(r4.z, 110.0f));
    assert(equal(r4.w, 120.0f));

    /* Identity leaves the vector unchanged */
    vec4 v4 = vec4_make(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 i4 = mat4_mul_vec4(MAT4_IDENTITY, v4);
    assert(equal(i4.x, v4.x));
    assert(equal(i4.y, v4.y));
    assert(equal(i4.z, v4.z));
    assert(equal(i4.w, v4.w));

    /* Translation moves points (w = 1) but not directions (w = 0) */
    mat4 t = mat4_trs_translate(vec3_make(10.0f, 20.0f, 30.0f));
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec4 p = mat4_mul_vec4(t, vec4_from_vec3(v3, 1.0f));
    assert(equal(p.x, 11.0f));
    assert(equal(p.y, 22.0f));
    assert(equal(p.z, 33.0f));
    assert(equal(p.w, 1.0f));
    vec4 d = mat4_mul_vec4(t, vec4_from_vec3(v3, 0.0f));
    assert(equal(d.x, 1.0f));
    assert(equal(d.y, 2.0f));
    assert(equal(d.z, 3.0f));
    assert(equal(d.w, 0.0f));

    /* Rotating x by 90 degrees about z gives y */
    mat4 r = mat4_trs_rotate(1.57079632679f, vec3_make(0.0f, 0.0f, 1.0f));
    vec4 x = mat4_mul_vec4(r, vec4_make(1.0f, 0.0f, 0.0f, 0.0f));
    assert(equal(x.x, 0.0f));
    assert(equal(x.y, 1.0f));
    assert(equal(x.z, 0.0f));
    assert(equal(x.w, 0.0f));
}

void test_mat4_mul()
{
    /* Columns (1, 2, 3, 4), (5, 6, 7, 8), (9, 10, 11, 12), (13, 14, 15, 16) */
    mat4 m = {{
        vec4_make(1.0f, 2.0f, 3.0f, 4.0f),
        vec4_make(5.0f, 6.0f, 7.0f, 8.0f),
        vec4_make(9.0f, 10.0f, 11.0f, 12.0f),
        vec4_make(13.0f, 14.0f, 15.0f, 16.0f),
    }};

    /* Identity on either side leaves the matrix unchanged */
    assert(matrices_close(mat4_mul(MAT4_IDENTITY, m), m, EPSILON));
    assert(matrices_close(mat4_mul(m, MAT4_IDENTITY), m, EPSILON));

    /* Column j of the result is m times column j of n */
    mat4 n = {{
        vec4_make(1.0f, 0.0f, 0.0f, 0.0f),
        vec4_make(0.0f, 2.0f, 0.0f, 0.0f),
        vec4_make(0.0f, 0.0f, 3.0f, 0.0f),
        vec4_make(1.0f, 1.0f, 1.0f, 1.0f),
    }};
    mat4 expected = {{
        vec4_make(1.0f, 2.0f, 3.0f, 4.0f),
        vec4_make(10.0f, 12.0f, 14.0f, 16.0f),
        vec4_make(27.0f, 30.0f, 33.0f, 36.0f),
        vec4_make(28.0f, 32.0f, 36.0f, 40.0f),
    }};
    assert(matrices_close(mat4_mul(m, n), expected, EPSILON));

    /* The right-hand matrix is applied first: T * S scales, then translates */
    mat4 t = mat4_trs_translate(vec3_make(1.0f, 2.0f, 3.0f));
    mat4 s = mat4_trs_scale(vec3_make(2.0f, 2.0f, 2.0f));
    vec4 p = vec4_make(1.0f, 1.0f, 1.0f, 1.0f);

    vec4 ts = mat4_mul_vec4(mat4_mul(t, s), p);
    assert(equal(ts.x, 3.0f));
    assert(equal(ts.y, 4.0f));
    assert(equal(ts.z, 5.0f));
    assert(equal(ts.w, 1.0f));

    vec4 st = mat4_mul_vec4(mat4_mul(s, t), p);
    assert(equal(st.x, 4.0f));
    assert(equal(st.y, 6.0f));
    assert(equal(st.z, 8.0f));
    assert(equal(st.w, 1.0f));
}

void test_mat4_inverse()
{
    /* Identity is its own inverse */
    assert(matrices_close(mat4_inverse(MAT4_IDENTITY), MAT4_IDENTITY, EPSILON));

    /* Inverse of a translation translates back */
    mat4 t = mat4_trs_translate(vec3_make(1.0f, 2.0f, 3.0f));
    mat4 ti = mat4_trs_translate(vec3_make(-1.0f, -2.0f, -3.0f));
    assert(matrices_close(mat4_inverse(t), ti, EPSILON));

    /* Inverse of a scale divides */
    mat4 s = mat4_trs_scale(vec3_make(2.0f, 4.0f, 8.0f));
    mat4 si = mat4_trs_scale(vec3_make(0.5f, 0.25f, 0.125f));
    assert(matrices_close(mat4_inverse(s), si, EPSILON));

    /* A general transform times its inverse gives identity, on either side.
     * Rounding in the 4x4 inverse needs a looser tolerance than EPSILON. */
    mat4 r = mat4_trs_rotate(0.7f, vec3_make(1.0f, 1.0f, 0.0f));
    mat4 m = mat4_mul(t, mat4_mul(r, mat4_trs_scale(vec3_make(2.0f, 3.0f, 4.0f))));
    mat4 mi = mat4_inverse(m);
    assert(matrices_close(mat4_mul(m, mi), MAT4_IDENTITY, 1e-5f));
    assert(matrices_close(mat4_mul(mi, m), MAT4_IDENTITY, 1e-5f));
}

void test_mat4_try_inverse()
{
    /* Invertible: succeeds and matches mat4_inverse */
    mat4 m = mat4_mul(mat4_trs_translate(vec3_make(1.0f, 2.0f, 3.0f)),
                      mat4_trs_rotate(0.7f, vec3_make(0.0f, 1.0f, 0.0f)));
    mat4 res;
    assert(mat4_try_inverse(m, &res));
    assert(matrices_close(res, mat4_inverse(m), EPSILON));
    assert(matrices_close(mat4_mul(m, res), MAT4_IDENTITY, 1e-5f));

    /* Singular matrices: fails and leaves the result untouched */
    mat4 zero = {0};

    mat4 zero_col = MAT4_IDENTITY;
    zero_col.cols[2] = vec4_make(0.0f, 0.0f, 0.0f, 0.0f);

    mat4 dup_col = MAT4_IDENTITY;
    dup_col.cols[1] = dup_col.cols[0];

    /* Invertible in theory, but the determinant (1e-48) underflows to zero */
    mat4 tiny = mat4_scale(1e-12f, MAT4_IDENTITY);

    /* The determinant (1e-39) is not zero, but its reciprocal overflows */
    mat4 subnormal = MAT4_IDENTITY;
    subnormal.cr[3][3] = 1e-39f;

    mat4 singular[] = {zero, zero_col, dup_col, tiny, subnormal};
    for (int i = 0; i < 5; i++) {
        mat4 untouched = m;
        assert(!mat4_try_inverse(singular[i], &untouched));
        assert(matrices_close(untouched, m, EPSILON));
    }

    /* NaN and infinity are undefined behavior under -ffast-math */
#ifndef __FAST_MATH__
    /* A NaN element makes the determinant NaN */
    mat4 nan = MAT4_IDENTITY;
    nan.cr[1][1] = NAN;

    /* The determinant (1e40) overflows to infinity */
    mat4 huge = mat4_scale(1e10f, MAT4_IDENTITY);

    mat4 invalid[] = {nan, huge};
    for (int i = 0; i < 2; i++) {
        mat4 untouched = m;
        assert(!mat4_try_inverse(invalid[i], &untouched));
        assert(matrices_close(untouched, m, EPSILON));
    }
#endif
}

int main()
{
    printf("Testing vm_add()\n");
    test_add();

    printf("Testing vm_sub()\n");
    test_sub();

    printf("Testing vm_scale()\n");
    test_scale();

    printf("Testing vm_dot()\n");
    test_dot();

    printf("Testing vm_cross()\n");
    test_cross();

    printf("Testing vm_norm()\n");
    test_norm();

    printf("Testing vm_normalize()\n");
    test_normalize();

    printf("Testing packed types\n");
    test_packed();

    printf("Testing vec4_from_vec3() and vec3_from_vec4()\n");
    test_convert();

    printf("Testing mat4_mul_vec4()\n");
    test_mat4_mul_vec4();

    printf("Testing mat4_mul()\n");
    test_mat4_mul();

    printf("Testing mat4_inverse()\n");
    test_mat4_inverse();

    printf("Testing mat4_try_inverse()\n");
    test_mat4_try_inverse();

    printf("=== VECMAT TESTING COMPLETED ===\n");
    return 0;
}
