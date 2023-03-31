# force-manifold
use openvdb to create a manifold mesh from an arbitrary mesh

# Usage 

force-manifold.exe path_to_input.obj path_to_output.obj scale(default = 10.0)

# TO-DO

- [ ] expose this as a lib instead of an executable 
- [ ] general polish


# Build 

use cmake and vcpkg.
copy this batch file to go quicker, change the vcpkg path  
```
@echo off
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/repos/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release --target force_manifold --parallel
cd ..
```
