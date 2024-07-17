# vecmath
>C++ header-only library for vector and matrix math

This project provides the following functionalities:
- constanst (_PI_, _EULER_, _GOLEN_RATIO_, ...)
- arithmetic (_abs_, _floor_, _ceil_, _exp_, _max_, ...)
- vector and matrix math (_Vec<T, N, M>_, _Mat<T, N, M>_)
- 3D math (_RotationMatrix_, _PerspectiveMatrix_, ...)
- curves (_lerp_, _quadratic_, _cubic_ ...)

These functionalities are _optimized_ for readability, not performance.

## Dependancies
- beaver (optional, for error logging), see https://github.com/fburgerdev/beaver

## Usage
```cpp
#include "vecmath/vecmath.hpp"

int main() {
    Math::Vec3F vec = Math::normalize(Math::Vec3F(1, 2, 3));
    
    Math::Mat3F mat = Math::Identity<float, 3>();
    mat.at(0, 1) = 2;
    
    std::cout << Math::transpose(mat * vec) << std::endl;
    return EXIT_SUCCESS;
}
```

## Include this Library
In your c++ project
- add _include/vecmath_ to your include directories

optionally, to use precompiled templates
- add _lib/[config]_ to your library directories (depending on your configuration)
- link the library _libvecmath.a_ (for linux) and _vecmath.lib_ (for windows)

In order to resolve the dependancies
- for beaver (optional, for error logging)
    - add _modules/beaver/lib/[config]_ to your include directories
    - link the library _libbeaver.a_ or _beaver.lib_

## Build (Optional)
#### Using Linux (Debian)
Locate the _build_ folder, then execute the following command in the console:
``` console
make config=[config]
```
If you have not installed _make_:
``` console
sudo apt-get install make -y
```

#### Using Windows
Open the _build/vecmath.sln_ solution with Visual Studio.

After selecting your desired configuration, click on _Build > Build Solution_.

__Note:__ Make sure you have the _Desktop developement with C++_ workload installed.