
if host_machine.system() == 'windows'
  raylib_lib = meson.get_compiler('cpp').find_library('raylib', dirs : meson.source_root() / 'vendor/raylib/lib-windows/')
else
  raylib_lib = meson.get_compiler('cpp').find_library('raylib', dirs : meson.source_root() / 'vendor/raylib/lib-linux/')
endif

vendor_inc = [
  'vendor/raylib/include',
  'vendor/cjson'
]

vendor_src = [
  'vendor/cjson/cJSON.c'
]
