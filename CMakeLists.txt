cmake_minimum_required(VERSION 2.8.11)
Project(luminol)

option(STEAM "Build for Steam" OFF)
option(DEBUG "Debug mode" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_RPATH "lib")

IF("${CMAKE_SYSTEM}" MATCHES "Linux")
	SET(LINUX ON)
ENDIF()

IF(WORKDIR_CURRENT)
	list(APPEND DEFINES
		WORKDIR_CURRENT
	)
ENDIF()

set(CMAKE_SKIP_BUILD_RPATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH ${BIN_RPATH})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

set(MRI_VERSION "3.1" CACHE STRING "Version of MRI to link with")

find_package(PkgConfig REQUIRED)

pkg_check_modules(SIGCXX        REQUIRED sigc++-2.0)
pkg_check_modules(PIXMAN        REQUIRED pixman-1)
pkg_check_modules(PHYSFS        REQUIRED physfs>=2.1)
pkg_check_modules(VORBISFILE    REQUIRED vorbisfile)
pkg_check_modules(SDL2          REQUIRED sdl2)
pkg_check_modules(SDL2_TTF      REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE    REQUIRED SDL2_image)
pkg_check_modules(SDL_SOUND     REQUIRED SDL_sound)
pkg_check_modules(MRI REQUIRED ruby-3.1)
pkg_check_modules(OGG REQUIRED ogg)
pkg_check_modules(SPEEX REQUIRED speex)
pkg_check_modules(MODPLUG REQUIRED libmodplug)

find_package(Boost 1.49 COMPONENTS program_options REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ZLIB REQUIRED)

set(SRC_AUDIO_HEADER_PATH src/audio/headers)
set(SRC_GRAPHICS_HEADER_PATH src/graphics/headers)
set(SRC_OPENGL_HEADER_PATH src/opengl/headers)
set(SRC_INPUT_HEADER_PATH src/input/headers)
set(SRC_FS_HEADER_PATH src/filesystem/headers)

set(SRC_AUDIO_SOURCE_PATH src/audio/source)
set(SRC_GRAPHICS_SOURCE_PATH src/graphics/source)
set(SRC_OPENGL_SOURCE_PATH src/opengl/source)
set(SRC_INPUT_SOURCE_PATH src/input/source)
set(SRC_FS_SOURCE_PATH src/filesystem/source)

set(SRC_STEAM_PATH src/steam)

set(MAIN_HEADERS
	# Audio
	${SRC_AUDIO_HEADER_PATH}/audio.h
	${SRC_AUDIO_HEADER_PATH}/al-util.h
	${SRC_AUDIO_HEADER_PATH}/aldatasource.h
	${SRC_AUDIO_HEADER_PATH}/alstream.h
	${SRC_AUDIO_HEADER_PATH}/audiostream.h
	${SRC_AUDIO_HEADER_PATH}/audiochannels.h
	${SRC_AUDIO_HEADER_PATH}/soundemitter.h

	# Graphics
	${SRC_GRAPHICS_HEADER_PATH}/bitmap.h
	${SRC_GRAPHICS_HEADER_PATH}/graphics.h
	${SRC_GRAPHICS_HEADER_PATH}/disposable.h
	${SRC_GRAPHICS_HEADER_PATH}/font.h
	${SRC_GRAPHICS_HEADER_PATH}/sprite.h
	${SRC_GRAPHICS_HEADER_PATH}/scene.h
	${SRC_GRAPHICS_HEADER_PATH}/tilemap.h
	${SRC_GRAPHICS_HEADER_PATH}/tilemap-common.h
	${SRC_GRAPHICS_HEADER_PATH}/tileatlas.h
	${SRC_GRAPHICS_HEADER_PATH}/flashable.h

	# OpenGL
	${SRC_OPENGL_HEADER_PATH}/glstate.h
	${SRC_OPENGL_HEADER_PATH}/gl-debug.h
	${SRC_OPENGL_HEADER_PATH}/gl-util.h
	${SRC_OPENGL_HEADER_PATH}/gl-fun.h
	${SRC_OPENGL_HEADER_PATH}/gl-meta.h
	${SRC_OPENGL_HEADER_PATH}/quadarray.h
	${SRC_OPENGL_HEADER_PATH}/plane.h
	${SRC_OPENGL_HEADER_PATH}/shader.h
	${SRC_OPENGL_HEADER_PATH}/quad.h
	${SRC_OPENGL_HEADER_PATH}/texpool.h
	${SRC_OPENGL_HEADER_PATH}/tilequad.h
	${SRC_OPENGL_HEADER_PATH}/vertex.h
	${SRC_OPENGL_HEADER_PATH}/window.h
	${SRC_OPENGL_HEADER_PATH}/sdl-util.h
	${SRC_OPENGL_HEADER_PATH}/viewport.h
	${SRC_OPENGL_HEADER_PATH}/table.h
	${SRC_OPENGL_HEADER_PATH}/transform.h

	# Input
	${SRC_INPUT_HEADER_PATH}/input.h
	${SRC_INPUT_HEADER_PATH}/keybindings.h

	# Filesystem
	${SRC_FS_HEADER_PATH}/filesystem.h
	${SRC_FS_HEADER_PATH}/rgssad.h

	src/display.h
	src/binding.h
	src/etc.h
	src/etc-internal.h
	src/eventthread.h
	src/serializable.h
	src/global-ibo.h
	src/exception.h
	src/serial-util.h
	src/intrulist.h
	src/binding.h
	src/util.h
	src/config.h
	src/settingsmenu.h
	src/sharedstate.h
	src/boost-hash.h
	src/debugwriter.h
	src/oneshot.h
	src/pipe.h
	src/i18n.h
)

set(MAIN_SOURCE
	# Audio
	${SRC_AUDIO_SOURCE_PATH}/alstream.cpp
	${SRC_AUDIO_SOURCE_PATH}/audiostream.cpp
	${SRC_AUDIO_SOURCE_PATH}/audiochannels.cpp
	${SRC_AUDIO_SOURCE_PATH}/audio.cpp
	${SRC_AUDIO_SOURCE_PATH}/soundemitter.cpp
	${SRC_AUDIO_SOURCE_PATH}/sdlsoundsource.cpp
	${SRC_AUDIO_SOURCE_PATH}/vorbissource.cpp

	# Graphics
	${SRC_GRAPHICS_SOURCE_PATH}/autotiles.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/bitmap.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/graphics.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/font.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/sprite.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/scene.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/tilemap.cpp
	${SRC_GRAPHICS_SOURCE_PATH}/tileatlas.cpp

	# OpenGL
	${SRC_OPENGL_SOURCE_PATH}/glstate.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-debug.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-fun.cpp
	${SRC_OPENGL_SOURCE_PATH}/gl-meta.cpp
	${SRC_OPENGL_SOURCE_PATH}/plane.cpp
	${SRC_OPENGL_SOURCE_PATH}/shader.cpp
	${SRC_OPENGL_SOURCE_PATH}/texpool.cpp
	${SRC_OPENGL_SOURCE_PATH}/vertex.cpp
	${SRC_OPENGL_SOURCE_PATH}/tilequad.cpp
	${SRC_OPENGL_SOURCE_PATH}/window.cpp
	${SRC_OPENGL_SOURCE_PATH}/screen.cpp
	${SRC_OPENGL_SOURCE_PATH}/viewport.cpp
	${SRC_OPENGL_SOURCE_PATH}/table.cpp

	# Input
	${SRC_INPUT_SOURCE_PATH}/input.cpp
	${SRC_INPUT_SOURCE_PATH}/keybindings.cpp

	# Filesystem
	${SRC_FS_SOURCE_PATH}/filesystem.cpp
	${SRC_FS_SOURCE_PATH}/rgssad.cpp

	src/main.cpp
	src/display.cpp
	src/eventthread.cpp
	src/etc.cpp
	src/config.cpp
	src/settingsmenu.cpp
	src/sharedstate.cpp
	src/oneshot.cpp
	src/i18n.cpp
)

if(WIN32)
	list(APPEND MAIN_SOURCE assets/resources.rc)
	list(APPEND DEFINES UNICODE)
	list(APPEND PLATFORM_LIBRARIES Secur32 Shlwapi)
	include_directories(
		${CMAKE_CURRENT_BINARY_DIR}/windows
	)
else()
	if(NOT MSYS2)
        pkg_check_modules(LINUXPKGS REQUIRED gtk+-2.0 libxfconf-0)
    endif()
	include_directories(${LINUXPKGS_INCLUDE_DIRS})
	add_compile_options(${LINUXPKGS_CFLAGS_OTHER} -g)
	list(APPEND PLATFORM_LIBRARIES ${LINUXPKGS_LDFLAGS})
	list(APPEND MAIN_SOURCE src/xdg-user-dir-lookup.c)
	list(APPEND MAIN_HEADERS src/xdg-user-dir-lookup.h)
endif()

if (STEAM)
	list(APPEND MAIN_HEADERS
		${SRC_STEAM_PATH}/steam.h
		steamshim/steamshim_child.h
	)
	list(APPEND MAIN_SOURCE
		${SRC_STEAM_PATH}/steam.cpp
		steamshim/steamshim_child.c
	)
	list(APPEND DEFINES
		STEAM
	)
endif()

source_group("MKXP Source" FILES ${MAIN_SOURCE} ${MAIN_HEADERS})

set(EMBEDDED_INPUT
	shader/common.h
	shader/transSimple.frag
	shader/trans.frag
	shader/hue.frag
	shader/sprite.frag
	shader/plane.frag
	shader/gray.frag
	shader/bitmapBlit.frag
	shader/flatColor.frag
	shader/simple.frag
	shader/simpleColor.frag
	shader/simpleAlpha.frag
	shader/simpleAlphaUni.frag
	shader/flashMap.frag
	shader/obscured.frag
	shader/minimal.vert
	shader/simple.vert
	shader/simpleColor.vert
	shader/sprite.vert
	shader/tilemap.vert
	shader/blur.frag
	shader/blurH.vert
	shader/blurV.vert
	shader/mask.frag
	shader/mask.vert
	shader/crt.frag
	shader/crt_sprite.frag
	shader/simpleMatrix.vert
	shader/chronos.frag
	shader/cubic_lens.frag
	shader/water.frag
	shader/zoom.vert
	shader/tone.frag
	shader/binary_glitch.frag
	assets/icon.png
	assets/gamecontrollerdb.txt
)

if (RGSS2)
	list(APPEND DEFINES
		RGSS2
	)
endif()

if (MSVC)
	list(APPEND DEFINES
		_CRT_SECURE_NO_WARNINGS
		NOMINMAX
	)
endif()

find_program(XXD_EXE xxd
	DOC "Location of the xxd executable"
)

macro(ProcessWithXXD outvar inputfile outdir)
	get_filename_component(basefile ${inputfile} NAME)
	set(outputfile ${outdir}/${basefile}.xxd)
	set_source_files_properties(${outputfile} PROPERTIES HEADER_ONLY TRUE)
	add_custom_command(
		OUTPUT ${outputfile}
		COMMAND ${XXD_EXE} -i ${inputfile} ${outputfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${inputfile}
		COMMENT "Generating XXD for ${inputfile}"
	)
	list(APPEND ${outvar}
		${outputfile}
	)
endmacro()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/xxdhack)
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}/xxdhack
)

foreach(item ${EMBEDDED_INPUT})
	ProcessWithXXD(EMBEDDED_SOURCE ${item} ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

source_group("Embedded Source" FILES ${EMBEDDED_INPUT} ${EMBEDDED_SOURCE})

list(APPEND DEFINES
	BINDING_MRI
)
set(BINDING_HEADERS
	binding-mri/binding-util.h
	binding-mri/binding-types.h
	binding-mri/serializable-binding.h
	binding-mri/disposable-binding.h
	binding-mri/sceneelement-binding.h
	binding-mri/viewportelement-binding.h
	binding-mri/flashable-binding.h
)
set(BINDING_SOURCE
	binding-mri/binding-mri.cpp
	binding-mri/binding-util.cpp
	binding-mri/table-binding.cpp
	binding-mri/etc-binding.cpp
	binding-mri/bitmap-binding.cpp
	binding-mri/font-binding.cpp
	binding-mri/graphics-binding.cpp
	binding-mri/input-binding.cpp
	binding-mri/sprite-binding.cpp
	binding-mri/viewport-binding.cpp
	binding-mri/plane-binding.cpp
	binding-mri/window-binding.cpp
	binding-mri/tilemap-binding.cpp
	binding-mri/audio-binding.cpp
	binding-mri/filesystem-binding.cpp
	binding-mri/oneshot-binding.cpp
	binding-mri/steam-binding.cpp
	binding-mri/wallpaper-binding.cpp
	binding-mri/journal-binding.cpp
	binding-mri/niko-binding.cpp
	binding-mri/modshot-window-binding.cpp
	binding-mri/aleffect-binding.cpp
	binding-mri/pathcache-binding.cpp
	binding-mri/screen-binding.cpp
	binding-mri/display-binding.cpp
)

source_group("Binding Source" FILES ${BINDING_SOURCE} ${BINDING_HEADERS})

link_directories(
	${SIGCXX_LIBRARY_DIRS}
	${PIXMAN_LIBRARY_DIRS}
	${PHYSFS_LIBRARY_DIRS}
	${SDL2_LIBRARY_DIRS} # Blindly assume other SDL bits are in same directory
	${Boost_LIBRARY_DIR}
	${MRI_LIBDIR}
)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
	${MAIN_HEADERS}
	${MAIN_SOURCE}
	${BINDING_HEADERS}
	${BINDING_SOURCE}
	${EMBEDDED_SOURCE}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    ${DEFINES}
)
target_include_directories(${PROJECT_NAME} PRIVATE 
    src 
    ${SRC_STEAM_PATH} 
    ${SRC_AUDIO_HEADER_PATH} 
    ${SRC_GRAPHICS_HEADER_PATH} 
    ${SRC_OPENGL_HEADER_PATH} 
    ${SRC_INPUT_HEADER_PATH} 
    ${SRC_FS_HEADER_PATH}

    ${SIGCXX_INCLUDE_DIRS}
	${PIXMAN_INCLUDE_DIRS}
	${PHYSFS_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS} # Blindly assume other SDL bits are in same directory
	${SDL_SOUND_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
	${MRI_INCLUDE_DIRS}
	${VORBISFILE_INCLUDE_DIRS}
	${FLUID_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	${SIGCXX_LIBRARIES}
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	${SDL2_TTF_LIBRARIES}
	${SDL_SOUND_LIBRARIES}
	${PHYSFS_LIBRARIES}
	${PIXMAN_LIBRARIES}
	${Boost_LIBRARIES}
	${MRI_LIBRARIES}
	${VORBISFILE_LIBRARIES}
	${FLUID_LIBRARIES}
	${OPENAL_LIBRARY}
	${ZLIB_LIBRARY}

    ${OGG_LIBRARIES}
    ${SPEEX_LIBRARIES}
    ${MODPLUG_LIBRARIES}

	${PLATFORM_LIBRARIES}
)

if(WIN32)
target_link_libraries(${PROJECT_NAME}
    winmm.lib
)
endif()


if(WIN32 AND NOT STEAM)
	add_executable("luminol-shim" WIN32
	"${CMAKE_SOURCE_DIR}/windows/shim.c"
	"${CMAKE_SOURCE_DIR}/assets/resources.rc")
endif()
