# This is not meant to be included by the top-level.
cmake_minimum_required (VERSION 2.8.7)
project(NEOVIM_DEPS)

if(NOT DEPS_DIR)
  get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
  set(DEPS_DIR ${PARENT_DIR}/.deps)
endif()

set(DEPS_INSTALL_DIR "${DEPS_DIR}/usr")
set(DEPS_BIN_DIR "${DEPS_DIR}/usr/bin")
set(DEPS_LIB_DIR "${DEPS_DIR}/usr/lib")
set(DEPS_BUILD_DIR "${DEPS_DIR}/build")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads")

option(USE_BUNDLED_LIBUV "Use the bundled libuv." ON)
option(USE_BUNDLED_MSGPACK "Use the bundled msgpack." ON)
option(USE_BUNDLED_LUAJIT "Use the bundled version of luajit." ON)
option(USE_BUNDLED_LUAROCKS "Use the bundled version of luarocks." ON)

# TODO: add windows support

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

# When using make, use the $(MAKE) variable to avoid warning about the job
# server.
if(CMAKE_GENERATOR MATCHES "Makefiles")
  set(MAKE_PRG "$(MAKE)")
endif()


include(ExternalProject)

set(LIBUV_URL https://github.com/joyent/libuv/archive/v0.11.23.tar.gz)
set(LIBUV_MD5 e02a3da9fba9ebe72a84e4abd312ee4d)

set(MSGPACK_URL https://github.com/msgpack/msgpack-c/releases/download/cpp-0.5.8/msgpack-0.5.8.tar.gz)
set(MSGPACK_MD5 ea0bee0939d2980c0df91f0e4843ccc4)

set(LUAJIT_URL http://luajit.org/download/LuaJIT-2.0.3.tar.gz)
set(LUAJIT_MD5 f14e9104be513913810cd59c8c658dc0)

set(LUAROCKS_URL http://github.com/keplerproject/luarocks/archive/v2.1.2.tar.gz)
set(LUAROCKS_MD5 df591c00a85d51fb754ec08c77896aad)

if (CMAKE_CROSSCOMPILING)
  set(AUTOCONF_HOST --host=${CROSS_TARGET})
endif()

if(USE_BUNDLED_LIBUV)
  ExternalProject_Add(libuv
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LIBUV_URL}
    URL_MD5 ${LIBUV_MD5}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/libuv
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/libuv
      -DURL=${LIBUV_URL}
      -DEXPECTED_MD5=${LIBUV_MD5}
      -DTARGET=libuv
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND sh ${DEPS_BUILD_DIR}/src/libuv/autogen.sh &&
      ${DEPS_BUILD_DIR}/src/libuv/configure --with-pic --disable-shared
        --prefix=${DEPS_INSTALL_DIR} ${AUTOCONF_HOST} CC=${CMAKE_C_COMPILER}
    INSTALL_COMMAND ${MAKE_PRG} install)
  list(APPEND THIRD_PARTY_DEPS libuv)
endif()

if(USE_BUNDLED_MSGPACK)
  ExternalProject_Add(msgpack
    PREFIX ${DEPS_BUILD_DIR}
    URL ${MSGPACK_URL}
    URL_MD5 ${MSGPACK_MD5}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/msgpack
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/msgpack
      -DURL=${MSGPACK_URL}
      -DEXPECTED_MD5=${MSGPACK_MD5}
      -DTARGET=msgpack
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ${DEPS_BUILD_DIR}/src/msgpack/configure --disable-shared
    --with-pic --prefix=${DEPS_INSTALL_DIR} ${AUTOCONF_HOST} CC=${CMAKE_C_COMPILER}
    INSTALL_COMMAND ${MAKE_PRG} install)
  list(APPEND THIRD_PARTY_DEPS msgpack)
endif()

if(USE_BUNDLED_LUAJIT)
  if (CMAKE_CROSSCOMPILING)
	  set(LUAJIT_INSTALL_CMD ${MAKE_PRG} HOST_CC=${HOST_C_COMPILER}
            HOST_CFLAGS=${HOST_C_FLAGS}
            HOSTLINK=${HOST_EXE_LINKER}
            HOST_LDFLAGS=${HOST_EXE_LINKER_FLAGS}
            TARGET_SYS=${CMAKE_SYSTEM_NAME}
            CROSS=${CROSS_TARGET}-
            PREFIX=${DEPS_INSTALL_DIR}
            BUILDMODE=static
            FILE_T=luajit.exe
            install)
  else()
    set(LUAJIT_INSTALL_CMD ${MAKE_PRG} CC=${CMAKE_C_COMPILER}
                                PREFIX=${DEPS_INSTALL_DIR}
                                BUILDMODE=static
                                install)
  endif()

  # This builds the TARGET luajit
  ExternalProject_Add(luajit
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LUAJIT_URL}
    URL_MD5 ${LUAJIT_MD5}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/luajit
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/luajit
      -DURL=${LUAJIT_URL}
      -DEXPECTED_MD5=${LUAJIT_MD5}
      -DTARGET=luajit
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ""
    INSTALL_COMMAND ${LUAJIT_INSTALL_CMD})
  list(APPEND THIRD_PARTY_DEPS luajit)

  # Build the HOST luajit
  if (CMAKE_CROSSCOMPILING)
    ExternalProject_Add(luajit-host
      PREFIX ${DEPS_BUILD_DIR}
      URL ${LUAJIT_URL}
      URL_MD5 ${LUAJIT_MD5}
      DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/luajit-host
      DOWNLOAD_COMMAND ${CMAKE_COMMAND}
        -DPREFIX=${DEPS_BUILD_DIR}
        -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/luajit-host
        -DURL=${LUAJIT_URL}
        -DEXPECTED_MD5=${LUAJIT_MD5}
        -DTARGET=luajit-host
        -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
      CONFIGURE_COMMAND ""
      BUILD_IN_SOURCE 1
      BUILD_COMMAND ""
      INSTALL_COMMAND ${MAKE_PRG} CC=${HOST_C_COMPILER}
                                PREFIX=${DEPS_INSTALL_DIR}/host
                                BUILDMODE=static
                                install)
  endif()

endif()

if(USE_BUNDLED_LUAROCKS)
  if(USE_BUNDLED_LUAJIT)
    if (CMAKE_CROSSCOMPILING)
      list(APPEND LUAROCKS_OPTS
        --with-lua=${DEPS_INSTALL_DIR}/host
        --with-lua-include=${DEPS_INSTALL_DIR}/include/luajit-2.0)
    else()
      list(APPEND LUAROCKS_OPTS
        --with-lua=${DEPS_INSTALL_DIR}
        --with-lua-include=${DEPS_INSTALL_DIR}/include/luajit-2.0)
    endif()
  endif()

  # Luarocks must live in the same PREFIX as HOST/luajit
  if (CMAKE_CROSSCOMPILING)
    set(LUAROCKS_PREFIX ${DEPS_INSTALL_DIR}/host)
    set(LUAROCKS_BIN "${DEPS_DIR}/usr/host/bin")
  else()
    set(LUAROCKS_PREFIX ${DEPS_INSTALL_DIR})
    set(LUAROCKS_BIN ${DEPS_BIN_DIR})
  endif()

  ExternalProject_Add(luarocks
    PREFIX ${DEPS_BUILD_DIR}
    URL ${LUAROCKS_URL}
    URL_MD5 ${LUAROCKS_MD5}
    DOWNLOAD_DIR ${DEPS_DOWNLOAD_DIR}/luarocks
    DOWNLOAD_COMMAND ${CMAKE_COMMAND}
      -DPREFIX=${DEPS_BUILD_DIR}
      -DDOWNLOAD_DIR=${DEPS_DOWNLOAD_DIR}/luarocks
      -DURL=${LUAROCKS_URL}
      -DEXPECTED_MD5=${LUAROCKS_MD5}
      -DTARGET=luarocks
      -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/DownloadAndExtractFile.cmake
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${DEPS_BUILD_DIR}/src/luarocks/configure
      --prefix=${LUAROCKS_PREFIX} --force-config ${LUAROCKS_OPTS}
      --lua-suffix=jit
    BUILD_COMMAND ""
    INSTALL_COMMAND ${MAKE_PRG} bootstrap)
  list(APPEND THIRD_PARTY_DEPS luarocks)
  if(USE_BUNDLED_LUAJIT)
    add_dependencies(luarocks luajit)
  endif()

  add_custom_command(OUTPUT ${LUAROCKS_BIN}/moon ${LUAROCKS_BIN}/moonc
    COMMAND ${LUAROCKS_BIN}/luarocks ARGS install moonscript
            --server=http://rocks.moonscript.org
    DEPENDS luarocks)
  add_custom_target(moonscript
    DEPENDS ${LUAROCKS_BIN}/moon ${LUAROCKS_BIN}/moonc)

  # Busted doesn't depend on luarocks, but luarocks is unhappy to have two
  # instances running in parallel.  So we depend on moonscript to force it
  # to be serialized.
  add_custom_command(OUTPUT ${LUAROCKS_BIN}/busted
    COMMAND ${LUAROCKS_BIN}/luarocks ARGS install busted 1.10.0
            --server=http://rocks.moonscript.org
    DEPENDS moonscript)
  add_custom_target(busted
    DEPENDS ${LUAROCKS_BIN}/busted)

  # Like busted dependency on moonscript, we add a dependency on busted
  # to serialize the install
  add_custom_command(OUTPUT ${DEPS_LIB_DIR}/luarocks/rocks/lua-cmsgpack
    COMMAND ${LUAROCKS_BIN}/luarocks ARGS install lua-cmsgpack
    DEPENDS busted)
  add_custom_target(lua-cmsgpack
    DEPENDS ${DEPS_LIB_DIR}/luarocks/rocks/lua-cmsgpack)

  # lpeg is a moonscript dependency, but since it is also required for
  # normal compilation(even without unit testing) we better add it explicitly.
  # Like before, depend on cmsgpack to ensure serialization of install commands
  add_custom_command(OUTPUT ${DEPS_LIB_DIR}/luarocks/rocks/lpeg
    COMMAND ${LUAROCKS_BIN}/luarocks ARGS install lpeg
    DEPENDS lua-cmsgpack)
  add_custom_target(lpeg
    DEPENDS ${DEPS_LIB_DIR}/luarocks/rocks/lpeg)

  list(APPEND THIRD_PARTY_DEPS moonscript busted lua-cmsgpack lpeg)
endif()

add_custom_target(third-party ALL
  COMMAND ${CMAKE_COMMAND} -E touch .third-party
  DEPENDS ${THIRD_PARTY_DEPS})
