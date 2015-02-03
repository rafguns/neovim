. "$CI_SCRIPTS/common.sh"

# When Travis gets a recent version of Mingw-w64 switch to this
#sudo apt-get install binutils-mingw-w64-i686 gcc-mingw-w64-i686 g++-mingw-w64-i686 mingw-w64-dev mingw-w64-tools wine 

# mingw-w64 build from http://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/rubenvb/gcc-4.8-release/
wget "http://downloads.sourceforge.net/project/mingw-w64/Toolchains%20targetting%20Win32/Personal%20Builds/rubenvb/gcc-4.8-release/i686-w64-mingw32-gcc-4.8.0-linux64_rubenvb.tar.xz?r=http%3A%2F%2Fsourceforge.net%2Fprojects%2Fmingw-w64%2Ffiles%2FToolchains%2520targetting%2520Win32%2FPersonal%2520Builds%2Frubenvb%2Fgcc-4.8-release%2F&ts=1422959985&use_mirror=heanet"
sudo tar -axf i686-w64-mingw32-gcc-4.8.0-linux64_rubenvb.tar.xz -C /opt

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


