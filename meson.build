project('sage', ['cpp', 'c'], default_options : ['cpp_std=c++2a', 'buildtype=debug', 'warning_level=3', 'werror=true'])

subdir('vendor')

src = [
  'src/application.cpp',
  'src/game.cpp',
  'src/graphics/map_renderer.cpp',
  'src/graphics/sprite.cpp',
  'src/io/project_loader.cpp',
  'src/main.cpp',
  'src/map/map.cpp',
  'src/map/tile_layer.cpp',
  'src/io/resource_manager.cpp',
  'src/io/sequence_loader.cpp',
  'src/sequence/events/echo.cpp',
  'src/sequence/sequence.cpp',
  'src/utils/file.cpp',
  'src/utils/log.cpp',
  'src/utils/string.cpp',
]

deps = [
  raylib_lib,
]

executable('out', [src, vendor_src], dependencies : deps, include_directories : [vendor_inc, 'src'])
