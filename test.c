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

void test_add()
{
    /* Vector 2 */
    vec2 v2 = {1.0f, 2.0f};
    vec2 u2 = {3.0f, 4.0f};
    vec2 r2 = vec2_add(v2, u2);

    assert(equal(r2.x, 4.0f));
    assert(equal(r2.y, 6.0f));

    /* Vector 2 generic */
    vec2 g2 = add(v2, u2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 u3 = {4.0f, 5.0f, 6.0f};
    vec3 r3 = vec3_add(v3, u3);

    assert(equal(r3.x, 5.0f));
    assert(equal(r3.y, 7.0f));
    assert(equal(r3.z, 9.0f));

    /* Vector 3 generic */
    vec3 g3 = add(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = {1.0f, 2.0f, 3.0f, 4.0f};
    vec4 u4 = {5.0f, 6.0f, 7.0f, 8.0f};
    vec4 r4 = vec4_add(v4, u4);

    assert(equal(r4.x, 6.0f));
    assert(equal(r4.y, 8.0f));
    assert(equal(r4.z, 10.0f));
    assert(equal(r4.w, 12.0f));

    /* Vector 4 generic */
    vec4 g4 = add(v4, u4);
    assert(equal(g4.x, r4.x));
    assert(equal(g4.y, r4.y));
    assert(equal(g4.z, r4.z));
    assert(equal(g4.w, r4.w));

    /* Matrix 4x4 */
    mat4 m4x4 = {v4, v4, v4, v4};
    mat4 n4x4 = {u4, u4, u4, u4};
    mat4 r4x4 = mat4_add(m4x4, n4x4);
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
    mat4 g4x4 = add(m4x4, n4x4);
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
    vec2 v2 = {1.0f, 2.0f};
    vec2 u2 = {3.0f, 4.0f};
    vec2 r2 = vec2_sub(v2, u2);

    assert(equal(r2.x, -2.0f));
    assert(equal(r2.y, -2.0f));

    /* Vector 2 generic */
    vec2 g2 = sub(v2, u2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 u3 = {4.0f, 5.0f, 6.0f};
    vec3 r3 = vec3_sub(v3, u3);

    assert(equal(r3.x, -3.0f));
    assert(equal(r3.y, -3.0f));
    assert(equal(r3.z, -3.0f));

    /* Vector 3 generic */
    vec3 g3 = sub(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = {1.0f, 2.0f, 3.0f, 4.0f};
    vec4 u4 = {5.0f, 6.0f, 7.0f, 8.0f};
    vec4 r4 = vec4_sub(v4, u4);

    assert(equal(r4.x, -4.0f));
    assert(equal(r4.y, -4.0f));
    assert(equal(r4.z, -4.0f));
    assert(equal(r4.w, -4.0f));

    /* Vector 4 generic */
    vec4 g4 = sub(v4, u4);
    assert(equal(g4.x, r4.x));
    assert(equal(g4.y, r4.y));
    assert(equal(g4.z, r4.z));
    assert(equal(g4.w, r4.w));

    /* Matrix 4x4 */
    mat4 m4x4 = {v4, v4, v4, v4};
    mat4 n4x4 = {u4, u4, u4, u4};
    mat4 r4x4 = mat4_sub(m4x4, n4x4);
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
    mat4 g4x4 = sub(m4x4, n4x4);
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
    vec2 v2 = {1.0f, 2.0f};
    vec2 r2 = vec2_scale(s, v2);

    assert(equal(r2.x, 2.0f));
    assert(equal(r2.y, 4.0f));

    /* Vector 2 generic */
    vec2 g2 = scale(s, v2);
    assert(equal(g2.x, r2.x));
    assert(equal(g2.y, r2.y));

    /* Vector 3 */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 r3 = vec3_scale(s, v3);

    assert(equal(r3.x, 2.0f));
    assert(equal(r3.y, 4.0f));
    assert(equal(r3.z, 6.0f));

    /* Vector 3 generic */
    vec3 g3 = scale(s, v3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));

    /* Vector 4 */
    vec4 v4 = {1.0f, 2.0f, 3.0f, 4.0f};
    vec4 r4 = vec4_scale(s, v4);

    assert(equal(r4.x, 2.0f));
    assert(equal(r4.y, 4.0f));
    assert(equal(r4.z, 6.0f));
    assert(equal(r4.w, 8.0f));

    /* Vector 4 generic */
    vec4 g4 = scale(s, v4);
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
    mat4 g4x4 = scale(s, m4x4);
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
    vec2 v2 = {1.0f, 2.0f};
    vec2 u2 = {3.0f, 4.0f};
    float r2 = vec2_dot(v2, u2);

    assert(equal(r2, 11.0f));

    /* Vector 2 generic */
    float g2 = dot(v2, u2);
    assert(equal(g2, r2));

    /* Vector 3 */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 u3 = {4.0f, 5.0f, 6.0f};
    float r3 = vec3_dot(v3, u3);

    assert(equal(r3, 32.0f));

    /* Vector 3 generic */
    float g3 = dot(v3, u3);
    assert(equal(g3, r3));

    /* Vector 4 */
    vec4 v4 = {1.0f, 2.0f, 3.0f, 4.0f};
    vec4 u4 = {5.0f, 6.0f, 7.0f, 8.0f};
    float r4 = vec4_dot(v4, u4);

    assert(equal(r4, 70.0f));

    /* Vector 4 generic */
    float g4 = dot(v4, u4);
    assert(equal(g4, r4));
}

void test_cross()
{
    vec3 v3 = {1.0f, 0.0f, 0.0f};
    vec3 u3 = {0.0f, 1.0f, 0.0f};
    vec3 r3 = vec3_cross(v3, u3);

    assert(equal(r3.x, 0.0f));
    assert(equal(r3.y, 0.0f));
    assert(equal(r3.z, 1.0f));

    vec3 g3 = cross(v3, u3);
    assert(equal(g3.x, r3.x));
    assert(equal(g3.y, r3.y));
    assert(equal(g3.z, r3.z));
}

void test_norm()
{
    /* Vector 2 */
    vec2 v2 = {1.0f, 0.0f};
    float r2 = vec2_norm(v2);
    assert(equal(r2, 1.0f));

    /* Vector 2 generic */
    float g2 = norm(v2);
    assert(equal(g2, r2));

    /* Vector 3 */
    vec3 v3 = {1.0f, 0.0f, 0.0f};
    float r3 = vec3_norm(v3);
    assert(equal(r3, 1.0f));

    /* Vector 3 generic */
    float g3 = norm(v3);
    assert(equal(g3, r3));

    /* Vector 4 */
    vec4 v4 = {1.0f, 0.0f, 0.0f, 0.0f};
    float r4 = vec4_norm(v4);
    assert(equal(r4, 1.0f));

    /* Vector 4 generic */
    float g4 = norm(v4);
    assert(equal(g4, r4));
}

void test_normalize()
{
    /* Vector 2 */
    vec2 v2 = {1.0f, 2.0f};
    vec2 r2 = vec2_normalize(v2);
    assert(equal(norm(r2), 1.0f));

    /* Vector 2 generic */
    vec2 g2 = normalize(v2);
    assert(equal(norm(g2), norm(r2)));

    /* Vector 3 */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 r3 = vec3_normalize(v3);
    assert(equal(norm(r3), 1.0f));

    /* Vector 3 generic */
    vec3 g3 = normalize(v3);
    assert(equal(norm(g3), norm(r3)));

    /* Vector 4 */
    vec4 v4 = {1.0f, 2.0f, 3.0f, 4.0f};
    vec4 r4 = vec4_normalize(v4);
    assert(equal(norm(r4), 1.0f));

    /* Vector 4 generic */
    vec4 g4 = normalize(v4);
    assert(equal(norm(g4), norm(r4)));
}

int main()
{
    printf("Testing add()\n");
    test_add();

    printf("Testing sub()\n");
    test_sub();

    printf("Testing scale()\n");
    test_scale();

    printf("Testing dot()\n");
    test_dot();

    printf("Testing cross()\n");
    test_cross();

    printf("Testing norm()\n");
    test_norm();

    printf("Testing normalize()\n");
    test_normalize();

    printf("=== VECMAT TESTING COMPLETED ===\n");
    return 0;
}
