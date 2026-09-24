# vecmat

This is a small header-only library for dealing with vectors and matrices in computer graphics.
It is written in C11 and uses intrinsics internally to vectorize the execution.

## Usage

Copy the header file `vecmat.h` to your repository and include it in the files where you want to use it.
The header defines all the functions as `static inline` and therefore do not need to define the implementation anywhere, like some other header-only libraries do.
It only requires SSE, which is always available on x86-64, so no extra compiler flags are needed.

The library has support for `vec2`, `vec3`, `vec4`, and `mat4` (4-by-4 matrices) with single floating point precision (32-bit).
All vector types are stored in a 16-byte SIMD register, so `vec2` and `vec3` have unused lanes.
Prefer creating them with `vec2_make()` and `vec3_make()`, which set the unused lanes to zero; brace initialization like `vec3 v = {1, 2, 3};` leaves them unspecified.
The library features some vector and matrix manipulation functions that you might expect like adding, subtracting, dot-product and transpose.
For a full reference, check the header file and the `test.c` file.

Because of the unused lanes, an array of `vec3` has a stride of 16 bytes and cannot be used directly as a tightly packed vertex buffer (`VK_FORMAT_R32G32B32_SFLOAT` expects 12 bytes).
For GPU data, use the packed storage types `vec2_packed` (8 bytes) and `vec3_packed` (12 bytes), and convert at the boundary:

```C
    vec3_packed vertices[3];

    /* Do the math with vec3... */
    vec3 p = vec3_scale(2.0f, vec3_make(1.0f, 2.0f, 3.0f));

    /* ...and store it packed */
    vertices[0] = vec3_pack(p);

    /* Load it back for more math */
    vec3 q = vec3_unpack(vertices[0]);
```

Many of the functions exist for several of the types and the library can also expose them though macros using `_Generic`.
To use generic calls, `VECMAT_USE_GENERICS` has to be defined before including the header file:

```C
#define VECMAT_USE_GENERICS
#include "vecmat.h"
```

This allows to use the same macro for different types:

```C
    /* Adding two vec2 using the vec2_add */
    vec2 v2 = vec2_make(1.0f, 2.0f);
    vec2 u2 = vec2_make(3.0f, 4.0f);
    vec2 r2 = vec2_add(v2, u2);

    /* Adding using the generic add macro */
    vec2 g2 = vm_add(v2, u2);

    /* Adding two vec3 using vec3_add */
    vec3 v3 = vec3_make(1.0f, 2.0f, 3.0f);
    vec3 u3 = vec3_make(4.0f, 5.0f, 6.0f);
    vec3 r3 = vec3_add(v3, u3);

    /* Or add using the generic add macro */
    vec3 g3 = vm_add(v3, u3);
```

Rotations can also be stored as quaternions with the `quat` type, stored as `(x, y, z, w)` with `w` as the scalar part.
Quaternions follow the same conventions as the matrices: rotations are right-handed, and `quat_mul(a, b)` applies `b` first and then `a`, just like `mat4_mul()`.

```C
    /* 90 degrees around the z-axis, then 45 degrees around the x-axis */
    quat qz = quat_from_axis_angle(1.5708f, vec3_make(0.0f, 0.0f, 1.0f));
    quat qx = quat_from_axis_angle(0.7854f, vec3_make(1.0f, 0.0f, 0.0f));
    quat q = quat_mul(qx, qz);

    vec3 v = quat_rotate_vec3(q, vec3_make(1.0f, 0.0f, 0.0f));
    mat4 m = mat4_from_quat(q);

    /* Interpolate along the shortest path */
    quat halfway = quat_slerp(QUAT_IDENTITY, q, 0.5f);
```

Quaternions can also be created from Euler angles, where the order is always explicit, from a direction to look along, or from the rotation part of a matrix.
A full translate-rotate-scale matrix can be built directly with `mat4_trs()`:

```C
    /* Rotate around x, then y, then z, all around the fixed world axes */
    quat e = quat_from_euler(vec3_make(0.1f, 0.2f, 0.3f), VECMAT_EULER_XYZ);

    /* Turn -z towards a direction, like a camera and mat4_lookat() */
    quat look = quat_lookat(vec3_make(1.0f, 0.0f, -1.0f),
                            vec3_make(0.0f, 1.0f, 0.0f));

    /* Scale, then rotate, then translate */
    mat4 model = mat4_trs(vec3_make(0.0f, 1.0f, 0.0f), e, vec3_make(2.0f, 2.0f, 2.0f));

    /* Get the rotation back, ignoring translation and positive scale */
    quat r = quat_from_mat4(model);
```

The library also contains some functions for creating translate-rotate-scale transformations that are commonly used in computer graphics.
They are prefixed with `mat4_trs_*`.

Orthographic and perspective projections are also provided as `mat4_orthographic()` and `mat4_perspective()` respectively, as well as the ubiquitous look-at transform `mat4_lookat()`.
The coordinate system has been designed to work with Vulkan.

## License

`vecmat` is released under the MIT License.
