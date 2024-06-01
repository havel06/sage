if host_machine.system() == 'windows'
  raylib_lib = meson.get_compiler('cpp').find_library('raylib', dirs : meson.source_root() / 'vendor/raylib/lib-windows/')
else
  raylib_lib = meson.get_compiler('cpp').find_library('raylib', dirs : meson.source_root() / 'vendor/raylib/lib-linux/')
endif

vendor_inc = [
  'vendor/raylib/include',
  'vendor/cjson',
  'vendor/imgui',
  'vendor/rlImGui'
]

vendor_src = [
  'cjson/cJSON.c',
  'imgui/imgui.cpp',
  'imgui/imgui_draw.cpp',
  'imgui/imgui_tables.cpp',
  'imgui/imgui_widgets.cpp',
  'rlImGui/rlImGui.cpp'
]

vendor_lib = static_library('vendor',
  vendor_src,
  include_directories : ['raylib/include/', 'imgui/'],
  override_options : ['warning_level=0'])
