project('sage', ['cpp', 'c'], default_options : ['cpp_std=c++2a', 'buildtype=debug', 'warning_level=3', 'werror=true'])

subdir('vendor')

src = [
  'src/main.cpp',
  'src/application.cpp',
  'src/game.cpp',
  'src/graphics/sprite.cpp',
  'src/map/map.cpp',
  'src/map/tile_layer.cpp',
]

deps = [
  raylib_lib,
]

executable('out', src, dependencies : deps, include_directories : [vendor_inc, 'src'])
