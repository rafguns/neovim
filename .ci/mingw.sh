. "$CI_SCRIPTS/common.sh"

sudo apt-get install binutils-mingw-w64-i686 gcc-mingw-w64-i686 g++-mingw-w64-i686 mingw-w64-dev mingw-w64-tools wine 

i686-w64-mingw32-gcc --version
mkdir .deps
cd .deps
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw32-w64-cross-travis.toolchain.cmake ../third-party/
cmake --build . -- VERBOSE=1
cd ..

mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw32-w64-cross-travis.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-DMIN_LOG_LEVEL=0 -pg" ..
cmake --build . -- VERBOSE=1
wine bin/neovim.exe --version


