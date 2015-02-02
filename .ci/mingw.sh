. "$CI_SCRIPTS/common.sh"


sudo apt-get install binutils-mingw-w64-i686 gcc-mingw-w64-i686 g++-mingw-w64-i686 wine

# Build third-party deps
mkdir .deps
cd .deps
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw32-w64-cross-travis.toolchain.cmake ../third-party/
cmake --build . -- VERBOSE=1
cd ..

# Build Neovim
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/mingw32-w64-cross-travis.toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_FLAGS="-DMIN_LOG_LEVEL=0 -pg" .. 
cmake --build . -- VERBOSE=1
wine bin/nvim.exe --version

