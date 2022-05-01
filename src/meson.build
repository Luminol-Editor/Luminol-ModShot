boost = dependency('boost', version: '>=1.49', modules: ['program_options'])
physfs = dependency('physfs', version: '>=2.1')
openal = dependency('openal')
vorbisfile = dependency('vorbisfile')
vorbis = dependency('vorbis')
ogg = dependency('ogg')
sdl2 = dependency('SDL2')
sdl_sound = compilers['cpp'].find_library('SDL2_sound')
sdl2_ttf = dependency('SDL2_ttf')
sdl2_image = dependency('SDL2_image')
sigcxx = dependency('sigc++-2.0')
pixman = dependency('pixman-1')
png = dependency('libpng')
jpeg = dependency('libjpeg')
zlib = dependency('zlib')
nsgif = dependency('libnsgif')

if host_system == 'windows'
    bz2 = dependency('bzip2')
	iconv = compilers['cpp'].find_library('iconv')
else
    bz2 = compilers['cpp'].find_library('bz2')
	iconv = compilers['cpp'].find_library('iconv')
    gtk = dependency('gtk+-2.0')
    xfconf = dependency('libxfconf-0')

	global_dependencies += [gtk, xfconf]
endif

# Windows needs to be treated like a special needs child here
explicit_libs = ''
if host_system == 'windows'
    # Newer versions of Ruby will refuse to link without these
    explicit_libs += 'libmsvcrt;libgcc;libmingwex;libgmp;'
endif

foreach l : explicit_libs.split(';')
        if l != ''
            global_link_args += '-l:' + l + '.a'
        endif
endforeach

global_include_dirs += include_directories('.',
    'audio/headers',
    'filesystem/headers',
    'graphics/headers',
    'input/headers',
    'opengl/headers'
)

global_dependencies += [boost, bz2, openal, zlib,  sdl2, sdl_sound, pixman, physfs, vorbisfile, vorbis, iconv, ogg, sdl2_ttf, sigcxx, sdl2_image, png, jpeg, nsgif]
if host_system == 'windows'
    global_dependencies += compilers['cpp'].find_library('wsock32')
    global_dependencies += compilers['cpp'].find_library('winmm')
    global_dependencies += compilers['cpp'].find_library('Secur32')
    global_dependencies += compilers['cpp'].find_library('Shlwapi')
endif

main_source = files(
    'audio/source/alstream.cpp',
	'audio/source/audiostream.cpp',
	'audio/source/audiochannels.cpp',
	'audio/source/audio.cpp',
	'audio/source/soundemitter.cpp',
	'audio/source/sdlsoundsource.cpp',
	'audio/source/vorbissource.cpp',
	'graphics/source/autotiles.cpp',
	'graphics/source/bitmap.cpp',
	'graphics/source/graphics.cpp',
	'graphics/source/font.cpp',
	'graphics/source/sprite.cpp',
	'graphics/source/scene.cpp',
	'graphics/source/tilemap.cpp',
	'graphics/source/tileatlas.cpp',
	'opengl/source/glstate.cpp',
	'opengl/source/gl-debug.cpp',
	'opengl/source/gl-fun.cpp',
	'opengl/source/gl-meta.cpp',
	'opengl/source/plane.cpp',
	'opengl/source/shader.cpp',
	'opengl/source/texpool.cpp',
	'opengl/source/vertex.cpp',
	'opengl/source/tilequad.cpp',
	'opengl/source/window.cpp',
	'opengl/source/screen.cpp',
	'opengl/source/viewport.cpp',
	'opengl/source/table.cpp',
	'input/source/input.cpp',
	'input/source/keybindings.cpp',
	'filesystem/source/filesystem.cpp',
	'filesystem/source/rgssad.cpp',
	'main.cpp',
	'eventthread.cpp',
	'etc.cpp',
	'config.cpp',
	'settingsmenu.cpp',
	'sharedstate.cpp',
	'oneshot.cpp',
	'i18n.cpp',
	'crash-handler.cpp'
)

global_sources += main_source

if steam == true
    global_sources += files(
        'steam/steam.cpp',
        '../steamshim/steamshim_child.c'
    )
    global_include_dirs += include_directories(
        'steam',
        '../steamshim'
    )

    global_args += '-DSTEAM'
endif

if host_system == 'windows'
else
    global_sources += files('xdg-user-dir-lookup.c')
endif
