# This is not meant to be included by the top-level.
cmake_minimum_required (VERSION 2.8.7)
project(NEOVIM_DEPS)

if(NOT DEPS_DIR)
  get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
  set(DEPS_DIR ${PARENT_DIR}/.deps)
endif()

set(DEPS_HOST_DIR "${DEPS_DIR}/host")
set(DEPS_INSTALL_DIR "${DEPS_DIR}/usr")
set(DEPS_BIN_DIR "${DEPS_DIR}/usr/bin")
set(DEPS_LIB_DIR "${DEPS_DIR}/usr/lib")
set(DEPS_BUILD_DIR "${DEPS_DIR}/build")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads")

option(USE_BUNDLED "Use bundled dependencies." ON)

option(USE_BUNDLED_LIBUNIBILIUM "Use the bundled libunibilium." ${USE_BUNDLED})
option(USE_BUNDLED_LIBTERMKEY "Use the bundled libtermkey." ${USE_BUNDLED})
option(USE_BUNDLED_LIBTICKIT "Use the bundled libtickit." ${USE_BUNDLED})
option(USE_BUNDLED_LIBUV "Use the bundled libuv." ${USE_BUNDLED})
option(USE_BUNDLED_MSGPACK "Use the bundled msgpack." ${USE_BUNDLED})
option(USE_BUNDLED_LUAJIT "Use the bundled version of luajit." ${USE_BUNDLED})
option(USE_BUNDLED_LUAROCKS "Use the bundled version of luarocks." ${USE_BUNDLED})

if (UNIX)
  # In Unix need GNU Make
  find_program(MAKE_PRG NAMES gmake make)
  if(MAKE_PRG)
    execute_process(
      COMMAND "${MAKE_PRG}" --version
      OUTPUT_VARIABLE MAKE_VERSION_INFO)
    if(NOT "${OUTPUT_VARIABLE}" MATCHES ".*GNU.*")
      unset(MAKE_PRG)
    endif()
  endif()
  if(NOT MAKE_PRG)
    message(FATAL_ERROR "GNU Make is required to build the dependencies.")
  else()
    message(STATUS "Found GNU Make at ${MAKE_PRG}")
  endif()
endif()

# When using make, use the $(MAKE) variable to avoid warning about the job
# server.
if(CMAKE_GENERATOR MATCHES "Makefiles")
  set(MAKE_PRG "$(MAKE)")
endif()

if(CMAKE_C_COMPILER_ARG1)
  set(DEPS_C_COMPILER "${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1}")
else()
  set(DEPS_C_COMPILER "${CMAKE_C_COMPILER}")
endif()

include(ExternalProject)

set(LIBUV_URL https://github.com/libuv/libuv/archive/v0.11.28.tar.gz)
set(LIBUV_SHA1 3b70b65467ee693228b8b8385665a52690d74092)
set(LIBUV_MD5 1a849ba4fc571d531482ed74bc7aabc4)

set(MSGPACK_URL https://github.com/msgpack/msgpack-c/archive/ecf4b09acd29746829b6a02939db91dfdec635b4.tar.gz)
set(MSGPACK_SHA1 c160ff99f20d9d0a25bea0a57f4452f1c9bde370)
set(MSGPACK_MD5 3599eaf904b8ba0c36cea7ed80973364)

set(LUAJIT_URL http://luajit.org/download/LuaJIT-2.0.3.tar.gz)
set(LUAJIT_SHA1 2db39e7d1264918c2266b0436c313fbd12da4ceb)
set(LUAJIT_MD5 f14e9104be513913810cd59c8c658dc0)

set(LUAROCKS_URL https://github.com/keplerproject/luarocks/archive/0587afbb5fe8ceb2f2eea16f486bd6183bf02f29.tar.gz)
set(LUAROCKS_SHA1 61a894fd5d61987bf7e7f9c3e0c5de16ba4b68c4)
set(LUAROCKS_MD5 0f53f42909fbcd2c88be303e8f970516)

set(LIBUNIBILIUM_URL https://github.com/mauke/unibilium/archive/v1.1.0.tar.gz)
set(LIBUNIBILIUM_SHA1 edda116e736396315abb33397f7815103e2d4fe4)
set(LIBUNIBILIUM_MD5 60f3e6db236daf12cbc92f0b60d9eddc)

set(LIBTERMKEY_URL https://github.com/neovim/libtermkey/archive/neovim.tar.gz)
set(LIBTERMKEY_SHA1 a309038a2297fe4905f03a8807723a9aa07c272a)
set(LIBTERMKEY_MD5 c99e5546da0063fa26dfa7d7f1d5a26f)

set(LIBTICKIT_URL https://github.com/neovim/libtickit/archive/neovim.tar.gz)
set(LIBTICKIT_SHA1 49e609de29c3bdc3b40d2ade76e69fde6e0d74bc)
set(LIBTICKIT_MD5 71a5d36d0ef6688d79828aabaf27eb36)

if(USE_BUNDLED_LIBUNIBILIUM)
  ExternalProject_Add(libunibilium
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LIBUNIBILIUM_URL}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/libunibilium
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/libunibilium
      -DURL=${LIBUNIBILIUM_URL}
      -DEXPECTED_SHA1=${LIBUNIBILIUM_SHA1}
      -DEXPECTED_MD5=${LIBUNIBILIUM_MD5}
      -DTARGET=libunibilium
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${MAKE_PRG} CC=${DEPS_C_COMPILER}
                              PREFIX=${DEPS_INSTALL_DIR}
                              CFLAGS=-fPIC
    INSTALL_COMMAND ${MAKE_PRG} PREFIX=${DEPS_INSTALL_DIR} install)
  list(APPEND THIRD_PARTY_DEPS libunibilium)
endif()

if(USE_BUNDLED_LIBTERMKEY AND WIN32)
  ExternalProject_Add(libtermkey
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LIBTERMKEY_URL}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/libtermkey
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/libtermkey
      -DURL=${LIBTERMKEY_URL}
      -DEXPECTED_SHA1=${LIBTERMKEY_SHA1}
      -DEXPECTED_MD5=${LIBTERMKEY_MD5}
      -DTARGET=libtermkey
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ""
    INSTALL_COMMAND ${MAKE_PRG} CC=${DEPS_C_COMPILER}
                                PREFIX=${DEPS_INSTALL_DIR}
                                PKG_CONFIG_PATH=${DEPS_LIB_DIR}/pkgconfig
                                CFLAGS=-fPIC
                                install)
  list(APPEND THIRD_PARTY_DEPS libtermkey)
  add_dependencies(libtermkey libunibilium)
endif()

if(USE_BUNDLED_LIBTICKIT AND WIN32)
  ExternalProject_Add(libtickit
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LIBTICKIT_URL}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/libtickit
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/libtickit
      -DURL=${LIBTICKIT_URL}
      -DEXPECTED_SHA1=${LIBTICKIT_SHA1}
      -DEXPECTED_MD5=${LIBTICKIT_MD5}
      -DTARGET=libtickit
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ""
    INSTALL_COMMAND ${MAKE_PRG} CC=${DEPS_C_COMPILER}
                                PREFIX=${DEPS_INSTALL_DIR}
                                PKG_CONFIG_PATH=${DEPS_LIB_DIR}/pkgconfig
                                CFLAGS=-fPIC
                                install)
  list(APPEND THIRD_PARTY_DEPS libtickit)
  add_dependencies(libtickit libtermkey)
endif()

if(USE_BUNDLED_LIBUV)
  function(BuildLibUv TARGET_NAME)
    ExternalProject_Add(${TARGET_NAME}
      PREFIX ${DEPS_BUILD_DIR}
      URL ${LIBUV_URL}
      DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/${TARGET_NAME}
      DOWNLOAD_COMMAND ${CMAKE_COMMAND}
        -DPREFIX=${DEPS_BUILD_DIR}
	-DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/${TARGET_NAME}
        -DURL=${LIBUV_URL}
        -DEXPECTED_SHA1=${LIBUV_SHA1}
        -DEXPECTED_MD5=${LIBUV_MD5}
	-DTARGET=${TARGET_NAME}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
	# FIXME(equalsraf): Not very happy with this, but function arguments
	# were not working for me
	CONFIGURE_COMMAND "${LIBUV_CONFIGURE_COMMAND}"
	BUILD_COMMAND "${LIBUV_BUILD_COMMAND}"
	INSTALL_COMMAND "${LIBUV_INSTALL_COMMAND}"
	)
  endfunction()

  # configure is mostly the same for Unix/cross-Mingw
  set(LIBUV_CFGCMD_UNIX sh ${DEPS_BUILD_DIR}/src/libuv/autogen.sh && ${DEPS_BUILD_DIR}/src/libuv/configure --with-pic --disable-shared --prefix=${DEPS_INSTALL_DIR} CC=${DEPS_C_COMPILER})

  if (UNIX)
    set(LIBUV_CONFIGURE_COMMAND ${LIBUV_CFGCMD_UNIX})
    set(LIBUV_BUILD_COMMAND "")
    set(LIBUV_INSTALL_COMMAND ${MAKE_PRG} install)
    BuildLibUv(libuv)
  elseif(WIN32 AND CMAKE_CROSSCOMPILING AND MINGW)

    # Build libuv for the host
    set(LIBUV_CONFIGURE_COMMAND sh ${DEPS_BUILD_DIR}/src/libuv_host/autogen.sh && ${DEPS_BUILD_DIR}/src/libuv_host/configure --with-pic --disable-shared --prefix=${DEPS_HOST_DIR} CC=${HOST_C_COMPILER})
    set(LIBUV_BUILD_COMMAND "")
    set(LIBUV_INSTALL_COMMAND ${MAKE_PRG} install)
    BuildLibUv(libuv_host)

    # Build libuv for the target
    set(LIBUV_CONFIGURE_COMMAND ${LIBUV_CFGCMD_UNIX} --host=${CROSS_TARGET})
    BuildLibUv(libuv)
  elseif(WIN32 AND MSVC)

    find_package(PythonInterp 2.6 REQUIRED)
    if (NOT PYTHONINTERP_FOUND OR PYTHON_VERSION_MAJOR GREATER 2)
      message(FATAL_ERROR "Python2 is required to build libuv on windows, use -DPYTHON_EXECUTABLE to set a python interpreter")
    endif()

    # FIXME: by default this creates Debug builds
    set(LIBUV_CONFIGURE_COMMAND "")
    set(LIBUV_BUILD_COMMAND set PYTHON=${PYTHON_EXECUTABLE} COMMAND ${DEPS_BUILD_DIR}/src/libuv/vcbuild.bat static)
    set(LIBUV_INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPS_INSTALL_DIR}/lib
	    COMMAND ${CMAKE_COMMAND} -E copy ${DEPS_BUILD_DIR}/src/libuv/Debug/lib/libuv.lib ${DEPS_INSTALL_DIR}/lib
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPS_INSTALL_DIR}/include
	    COMMAND ${CMAKE_COMMAND} -E copy_directory ${DEPS_BUILD_DIR}/src/libuv/include ${DEPS_INSTALL_DIR}/include)
 
    BuildLibUv(libuv)
  endif()

  list(APPEND THIRD_PARTY_DEPS libuv)
endif()

if(USE_BUNDLED_MSGPACK)

  function(BuildMsgpack TARGET_NAME)
    ExternalProject_Add(${TARGET_NAME}
      PREFIX ${DEPS_BUILD_DIR}
      URL ${MSGPACK_URL}
      DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/msgpack
      DOWNLOAD_COMMAND ${CMAKE_COMMAND}
        -DPREFIX=${DEPS_BUILD_DIR}
        -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/msgpack
        -DURL=${MSGPACK_URL}
        -DEXPECTED_SHA1=${MSGPACK_SHA1}
        -DEXPECTED_MD5=${MSGPACK_MD5}
	-DTARGET=${TARGET_NAME}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
      CONFIGURE_COMMAND "${MSGPACK_CONFIGURE_COMMAND}"
      BUILD_COMMAND "${MSGPACK_BUILD_COMMAND}"
      INSTALL_COMMAND "${MSGPACK_INSTALL_COMMAND}")
  endfunction()

  set(MSGPACK_CONFIGURE_COMMAND cmake ${DEPS_BUILD_DIR}/src/msgpack
         -DMSGPACK_ENABLE_CXX=OFF
         -DMSGPACK_BUILD_TESTS=OFF
         -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
         -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
         "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_COMPILER_ARG1} -fPIC")
  set(MSGPACK_BUILD_COMMAND ${CMAKE_COMMAND} --build .)
  set(MSGPACK_INSTALL_COMMAND ${CMAKE_COMMAND}
        -DREMOVE_FILE_GLOB=${DEPS_INSTALL_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}msgpack*${CMAKE_SHARED_LIBRARY_SUFFIX}*
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/InstallMsgpack.cmake)

  if (WIN32 AND CMAKE_CROSSCOMPILING AND MINGW)
    get_filename_component(TOOLCHAIN ${CMAKE_TOOLCHAIN_FILE} REALPATH)
    set(MSGPACK_CONFIGURE_COMMAND cmake ${DEPS_BUILD_DIR}/src/msgpack
      -DMSGPACK_ENABLE_CXX=OFF
      -DMSGPACK_BUILD_TESTS=OFF
      -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
      # Pass toolchain
      -DCMAKE_TOOLCHAIN_FILE=${TOOLCHAIN}
      # Hack to avoid -rdynamic in Mingw
      -DCMAKE_SHARED_LIBRARY_LINK_C_FLAGS="")
  elseif(WIN32 AND MSVC)
    # Same as UNIX without fPIC
    set(MSGPACK_CONFIGURE_COMMAND cmake ${DEPS_BUILD_DIR}/src/msgpack
           -DMSGPACK_ENABLE_CXX=OFF
           -DMSGPACK_BUILD_TESTS=OFF
           -DCMAKE_INSTALL_PREFIX=${DEPS_INSTALL_DIR}
           -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
           "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_COMPILER_ARG1} -fPIC")
  endif()
  BuildMsgpack(msgpack)

  list(APPEND THIRD_PARTY_DEPS msgpack)
endif()

if(USE_BUNDLED_LUAJIT)
  function(BuildLuaJit TARGET_NAME)
    ExternalProject_Add(${TARGET_NAME}
        PREFIX ${DEPS_BUILD_DIR}
        URL ${LUAJIT_URL}
        DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/${TARGET_NAME}
        DOWNLOAD_COMMAND ${CMAKE_COMMAND}
          -DPREFIX=${DEPS_BUILD_DIR}
          -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/${TARGET_NAME}
          -DURL=${LUAJIT_URL}
          -DEXPECTED_SHA1=${LUAJIT_SHA1}
          -DEXPECTED_MD5=${LUAJIT_MD5}
          -DTARGET=${TARGET_NAME}
          -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
        BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND "${LUAJIT_CONFIGURE_COMMAND}"
	BUILD_COMMAND "${LUAJIT_BUILD_COMMAND}"
	INSTALL_COMMAND "${LUAJIT_INSTALL_COMMAND}"
	)
  endfunction()
  
  set(LUAJIT_INSTALLCMD_UNIX ${MAKE_PRG} CC=${DEPS_C_COMPILER}
                                    PREFIX=${DEPS_INSTALL_DIR}
                                    CFLAGS=-fPIC
                                    BUILDMODE=static
                                    install)
  if (UNIX)
    set(LUAJIT_CONFIGURE_COMMAND "")
    set(LUAJIT_BUILD_COMMAND "")
    set(LUAJIT_INSTALL_COMMAND ${LUAJIT_INSTALLCMD_UNIX})
    BuildLuaJit(luajit)
  elseif(WIN32 AND CMAKE_CROSSCOMPILING AND MINGW)
    # Build luajit for the host
    set(LUAJIT_CONFIGURE_COMMAND "")
    set(LUAJIT_BUILD_COMMAND "")
    set(LUAJIT_INSTALL_COMMAND ${LUAJIT_INSTALLCMD_UNIX} PREFIX=${DEPS_HOST_DIR} CC=${HOST_C_COMPILER})
    BuildLuaJit(luajit_host)

    # Build luajit for the target
    set(LUAJIT_INSTALL_COMMAND ${LUAJIT_INSTALLCMD_UNIX}
	      TARGET_SYS=${CMAKE_SYSTEM_NAME}
              HOST_CC=${HOST_C_COMPILER} HOST_CFLAGS=${HOST_C_FLAGS}
              HOST_LDFLAGS=${HOST_EXE_LINKER_FLAGS}
              FILE_T=luajit.exe
              INSTALL_TSYMNAME=luajit.exe)
    BuildLuaJit(luajit)
  elseif(WIN32 AND MSVC)
    set(LUAJIT_CONFIGURE_COMMAND "")
    set(LUAJIT_BUILD_COMMAND cd src && msvcbuild)
    set(LUAJIT_INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPS_INSTALL_DIR}/bin
	    COMMAND ${CMAKE_COMMAND} -E copy ${DEPS_BUILD_DIR}/src/luajit/src/luajit.exe ${DEPS_INSTALL_DIR}/bin
	    COMMAND ${CMAKE_COMMAND} -E copy ${DEPS_BUILD_DIR}/src/luajit/src/lua51.dll ${DEPS_INSTALL_DIR}/bin
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPS_INSTALL_DIR}/lib
	    COMMAND ${CMAKE_COMMAND} -E copy ${DEPS_BUILD_DIR}/src/luajit/src/lua51.lib ${DEPS_INSTALL_DIR}/lib
	    COMMAND ${CMAKE_COMMAND} -E make_directory ${DEPS_INSTALL_DIR}/include/luajit-2.0
	    # FIXME: Copy only the necessary headers, but cmake does not accept wildcards
	    COMMAND ${CMAKE_COMMAND} -E copy_directory ${DEPS_BUILD_DIR}/src/luajit/src/ ${DEPS_INSTALL_DIR}/include/luajit-2.0)
    BuildLuaJit(luajit)
  endif()

  list(APPEND THIRD_PARTY_DEPS luajit)
endif()

if(USE_BUNDLED_LUAROCKS)
  if(USE_BUNDLED_LUAJIT)
    if (CMAKE_CROSSCOMPILING)
      list(APPEND LUAROCKS_OPTS
        --with-lua=${DEPS_HOST_DIR}
        --with-lua-include=${DEPS_HOST_DIR}/include/luajit-2.0)
    else()
      list(APPEND LUAROCKS_OPTS
        --with-lua=${DEPS_INSTALL_DIR}
        --with-lua-include=${DEPS_INSTALL_DIR}/include/luajit-2.0)
    endif()
  endif()

  # Luarocks is only built for the host
  if (CMAKE_CROSSCOMPILING)
    set(LUAROCKS_BIN_DIR ${DEPS_HOST_DIR}/bin)
    set(LUAROCKS_LIB_DIR ${DEPS_HOST_DIR}/lib)
    set(LUAROCKS_INSTALL_DIR ${DEPS_HOST_DIR})
    set(LUAROCKS_C_COMPILER ${HOST_C_COMPILER})
  else()
    set(LUAROCKS_BIN_DIR ${DEPS_BIN_DIR})
    set(LUAROCKS_LIB_DIR ${DEPS_LIB_DIR})
    set(LUAROCKS_INSTALL_DIR ${DEPS_INSTALL_DIR})
    set(LUAROCKS_C_COMPILER ${DEPS_C_COMPILER})
  endif()

  ExternalProject_Add(luarocks
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LUAROCKS_URL}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/luarocks
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/luarocks
      -DURL=${LUAROCKS_URL}
      -DEXPECTED_SHA1=${LUAROCKS_SHA1}
      -DEXPECTED_MD5=${LUAROCKS_MD5}
      -DTARGET=luarocks
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${DEPS_BUILD_DIR}/src/luarocks/configure
      --prefix=${LUAROCKS_INSTALL_DIR} --force-config ${LUAROCKS_OPTS}
      --lua-suffix=jit
    BUILD_COMMAND ""
    INSTALL_COMMAND ${MAKE_PRG} bootstrap)
  list(APPEND THIRD_PARTY_DEPS luarocks)
  if(USE_BUNDLED_LUAJIT)
    add_dependencies(luarocks luajit)
  endif()

  add_custom_command(OUTPUT ${LUAROCKS_BIN_DIR}/busted
    COMMAND ${LUAROCKS_BIN_DIR}/luarocks
    ARGS build busted 2.0.rc3 CC=${LUAROCKS_C_COMPILER} LD=${LUAROCKS_C_COMPILER}
    DEPENDS luarocks)
  add_custom_target(busted
    DEPENDS ${LUAROCKS_BIN_DIR}/busted)

  # lua-messagepack doesn't depend on busted, but luarocks is unhappy to have
  # two instances running in parallel.  So we depend on busted to force it to
  # be serialized.
  add_custom_command(OUTPUT ${LUAROCKS_LIB_DIR}/luarocks/rocks/lua-messagepack
    COMMAND ${LUAROCKS_BIN_DIR}/luarocks
    ARGS build lua-messagepack CC=${LUAROCKS_C_COMPILER} LD=${LUAROCKS_C_COMPILER}
    DEPENDS busted)
  add_custom_target(lua-messagepack
    DEPENDS ${LUAROCKS_LIB_DIR}/luarocks/rocks/lua-messagepack)

  # Like before, depend on lua-messagepack to ensure serialization of install
  # commands
  add_custom_command(OUTPUT ${LUAROCKS_LIB_DIR}/luarocks/rocks/lpeg
    COMMAND ${LUAROCKS_BIN_DIR}/luarocks
    ARGS build lpeg CC=${LUAROCKS_C_COMPILER} LD=${LUAROCKS_C_COMPILER}
    DEPENDS lua-messagepack)
  add_custom_target(lpeg
    DEPENDS ${LUAROCKS_LIB_DIR}/luarocks/rocks/lpeg)

  add_custom_command(OUTPUT ${LUAROCKS_LIB_DIR}/luarocks/rocks/nvim-client
    COMMAND ${LUAROCKS_BIN_DIR}/luarocks
    ARGS build https://raw.githubusercontent.com/neovim/lua-client/0aefb79d8f60fd180594f376d20144414e1f37a4/nvim-client-0.0.1-3.rockspec CC=${LUAROCKS_C_COMPILER} LD=${LUAROCKS_C_COMPILER} LIBUV_DIR=${LUAROCKS_INSTALL_DIR}
    DEPENDS lpeg libuv)
  add_custom_target(nvim-client
    DEPENDS ${LUAROCKS_LIB_DIR}/luarocks/rocks/nvim-client)

  list(APPEND THIRD_PARTY_DEPS busted lua-messagepack lpeg nvim-client)
endif()

add_custom_target(third-party ALL
  COMMAND ${CMAKE_COMMAND} -E touch .third-party
  DEPENDS ${THIRD_PARTY_DEPS})
