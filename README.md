# vecmat

This is a small header-only library for dealing with vectors and matrices in computer graphics.
It is written in C11 and uses intrinsics internally to vectorize the execution.

## Usage

Copy the header file `vacmat.h` to your repository and include it in the files where you want to use it.
The header defines all the functions as `static inline` and therefore do not need to define the implementation anywhere, like some other header-only libraries do.

The library has support for `vec2`, `vec3`, `vec4`, and `mat4` (4-by-4 matrices) with single floating point precision (32-bit).
The library features some vector and matrix manipulation functions that you might expect like adding, subtracting, dot-product and transpose.
For a full reference, check the header file and the `test.c` file.

Many of the functions exist for several of the types and the library can also expose them though macros using `_Generic`.
To use generic calls, `VECMAT_USE_GENERICS` has to be defined before including the header file:

```C
#define VECMAT_USE_GENERICS
#include "vecmat.h"
```

This allows to use the same macro for different types:

```C
    /* Adding two vec2 using the vec2_add */
    vec2 v2 = {1.0f, 2.0f};
    vec2 u2 = {3.0f, 4.0f};
    vec2 r2 = vec2_add(v2, u2);

    /* Adding using the generic add macro */
    vec2 g2 = add(v2, u2);

    /* Adding two vec3 using vec3_add */
    vec3 v3 = {1.0f, 2.0f, 3.0f};
    vec3 u3 = {4.0f, 5.0f, 6.0f};
    vec3 r3 = vec3_add(v3, u3);

    /* Or add using the generic add macro */
    vec3 g3 = add(v3, u3);
```

The library also contains some functions for creating translate-rotate-scale transformations that are commonly used in computer graphics.
They are prefixed with `mat4_trs_*`.

Orthographic and perspective projections are also provided as `mat4_orthographic()` and `mat4_perspective()` respectively, as well as the ubiquitous look-at transform `mat4_lookat()`.
The coordinate system has been designed to work with Vulkan.

## License

`vecmat` is released under the MIT License.
