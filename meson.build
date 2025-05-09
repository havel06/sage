project('sage', ['cpp', 'c'], default_options : ['cpp_std=c++2a', 'buildtype=release'])

subdir('vendor')

src = [
  'src/application.cpp',
  'src/argument_parser.cpp',
  'src/combat/battle.cpp',
  'src/combat/battle_turn.cpp',
  'src/combat/combat.cpp',
  'src/combat/combat_ai.cpp',
  'src/combat/combat_controller.cpp',
  'src/combat/combat_unit.cpp',
  'src/combat/stances.cpp',
  'src/console.cpp',
  'src/dev_tools/dev_tools.cpp',
  'src/dev_tools/entity_list.cpp',
  'src/dev_tools/entity_detail.cpp',
  'src/dev_tools/header.cpp',
  'src/dev_tools/main_widget.cpp',
  'src/dev_tools/map_dialog.cpp',
  'src/dev_tools/mode_entity.cpp',
  'src/dev_tools/mode_items.cpp',
  'src/dev_tools/mode_sequence.cpp',
  'src/dev_tools/sequence_detail.cpp',
  'src/dev_tools/sequence_list.cpp',
  'src/editor/editor.cpp',
  'src/editor/main_widget.cpp',
  'src/editor/mode_gui.cpp',
  'src/editor/mode_gui_open_dialog.cpp',
  'src/game/game.cpp',
  'src/game/game_facade.cpp',
  'src/game/game_logic.cpp',
  'src/game/game_logic_state_combat.cpp',
  'src/game/game_logic_state_normal.cpp',
  'src/graphics/animated_sprite.cpp',
  'src/graphics/camera.cpp',
  'src/graphics/camera_controller.cpp',
  'src/graphics/combat_renderer/combat_renderer.cpp',
  'src/graphics/combat_renderer/combat_renderer_unit.cpp',
  'src/graphics/debug_entity_renderer.cpp',
  'src/graphics/editor_ui/context.cpp',
  'src/graphics/editor_ui/data/font_data.cpp',
  'src/graphics/editor_ui/data/icon_data.cpp',
  'src/graphics/editor_ui/factories/button.cpp',
  'src/graphics/editor_ui/factories/card.cpp',
  'src/graphics/editor_ui/factories/column.cpp',
  'src/graphics/editor_ui/factories/constrained_container.cpp',
  'src/graphics/editor_ui/factories/dialog.cpp',
  'src/graphics/editor_ui/factories/divider.cpp',
  'src/graphics/editor_ui/factories/dummy.cpp',
  'src/graphics/editor_ui/factories/image.cpp',
  'src/graphics/editor_ui/factories/input_integer.cpp',
  'src/graphics/editor_ui/factories/input_number.cpp',
  'src/graphics/editor_ui/factories/input_text.cpp',
  'src/graphics/editor_ui/factories/nav_rail.cpp',
  'src/graphics/editor_ui/factories/progress_bar.cpp',
  'src/graphics/editor_ui/factories/relative_pane.cpp',
  'src/graphics/editor_ui/factories/row.cpp',
  'src/graphics/editor_ui/factories/scroll.cpp',
  'src/graphics/editor_ui/factories/stateful.cpp',
  'src/graphics/editor_ui/factories/text.cpp',
  'src/graphics/editor_ui/factories/tooltip.cpp',
  'src/graphics/editor_ui/icon_resource.cpp',
  'src/graphics/editor_ui/widgets/absolute_pane.cpp',
  'src/graphics/editor_ui/widgets/block.cpp',
  'src/graphics/editor_ui/widgets/button.cpp',
  'src/graphics/editor_ui/widgets/card.cpp',
  'src/graphics/editor_ui/widgets/column.cpp',
  'src/graphics/editor_ui/widgets/dialog.cpp',
  'src/graphics/editor_ui/widgets/divider.cpp',
  'src/graphics/editor_ui/widgets/dummy.cpp',
  'src/graphics/editor_ui/widgets/icon.cpp',
  'src/graphics/editor_ui/widgets/input.cpp',
  'src/graphics/editor_ui/widgets/input_state.cpp',
  'src/graphics/editor_ui/widgets/image.cpp',
  'src/graphics/editor_ui/widgets/nav_rail.cpp',
  'src/graphics/editor_ui/widgets/progress_bar.cpp',
  'src/graphics/editor_ui/widgets/relative_pane.cpp',
  'src/graphics/editor_ui/widgets/row.cpp',
  'src/graphics/editor_ui/widgets/scroll.cpp',
  'src/graphics/editor_ui/widgets/scroll_state.cpp',
  'src/graphics/editor_ui/widgets/stateful.cpp',
  'src/graphics/editor_ui/widgets/text.cpp',
  'src/graphics/editor_ui/widgets/tooltip.cpp',
  'src/graphics/editor_ui/system.cpp',
  'src/graphics/inventory_renderer.cpp',
  'src/graphics/main_menu_renderer.cpp',
  'src/graphics/map_renderer.cpp',
  'src/graphics/quest_log_renderer.cpp',
  'src/graphics/scriptable_gui.cpp',
  'src/graphics/shader.cpp',
  'src/graphics/sprite.cpp',
  'src/graphics/text_box_renderer.cpp',
  'src/graphics/game_ui/formatted_text.cpp',
  'src/graphics/game_ui/layout.cpp',
  'src/graphics/game_ui/size.cpp',
  'src/graphics/game_ui/widget.cpp',
  'src/graphics/game_ui/widgets/box.cpp',
  'src/graphics/game_ui/widgets/button.cpp',
  'src/graphics/game_ui/widgets/image.cpp',
  'src/graphics/game_ui/widgets/text.cpp',
  'src/graphics/game_ui/widget_factories/box.cpp',
  'src/graphics/game_ui/widget_factories/button.cpp',
  'src/graphics/game_ui/widget_factories/image.cpp',
  'src/graphics/game_ui/widget_factories/text.cpp',
  'src/graphics/game_ui/widget_factory.cpp',
  'src/input/input_event.cpp',
  'src/input/user_input.cpp',
  'src/io/character_profile_loader.cpp',
  'src/io/json_types.cpp',
  'src/io/gui_loader.cpp',
  'src/io/item_registry_loader.cpp',
  'src/io/parameter_parser.cpp',
  'src/io/project_loader.cpp',
  'src/io/resource/character_profile_manager.cpp',
  'src/io/resource/font_manager.cpp',
  'src/io/resource/map_manager.cpp',
  'src/io/resource/resource_system.cpp',
  'src/io/resource/sequence_manager.cpp',
  'src/io/resource/sound_manager.cpp',
  'src/io/resource/texture_manager.cpp',
  'src/io/savegame/combat_saveloader.cpp',
  'src/io/savegame/game_saveloader.cpp',
  'src/io/savegame/inventory_saveloader.cpp',
  'src/io/savegame/quest_saveloader.cpp',
  'src/io/savegame/map_saveloader.cpp',
  'src/io/savegame/saveload_system.cpp',
  'src/io/savegame/sequence_saveloader.cpp',
  'src/io/sequence/condition_parser.cpp',
  'src/io/sequence/sequence_loader.cpp',
  'src/io/sequence/event_parser.cpp',
  'src/io/template.cpp',
  'src/io/tmj.cpp',
  'src/io/user_directory_provider.cpp',
  'src/item/inventory.cpp',
  'src/item/item_registry.cpp',
  'src/main.cpp',
  'src/map/entity.cpp',
  'src/map/map.cpp',
  'src/map/position.cpp',
  'src/map/tile_layer.cpp',
  'src/map/tile_layers.cpp',
  'src/music_player.cpp',
  'src/party.cpp',
  'src/quest/quest_log.cpp',
  'src/replay/replay.cpp',
  'src/replay/replay_player.cpp',
  'src/replay/replay_recorder.cpp',
  'src/sequence/conditions/and.cpp',
  'src/sequence/conditions/has_item.cpp',
  'src/sequence/conditions/is_in_combat.cpp',
  'src/sequence/conditions/is_passable.cpp',
  'src/sequence/conditions/not.cpp',
  'src/sequence/conditions/player_is_looking.cpp',
  'src/sequence/condition_factories/and.cpp',
  'src/sequence/condition_factories/has_item.cpp',
  'src/sequence/condition_factories/is_in_combat.cpp',
  'src/sequence/condition_factories/is_passable.cpp',
  'src/sequence/condition_factories/not.cpp',
  'src/sequence/condition_factories/player_is_looking.cpp',
  'src/sequence/event_factories/activate_sequence.cpp',
  'src/sequence/event_factories/add_quest.cpp',
  'src/sequence/event_factories/add_to_party.cpp',
  'src/sequence/event_factories/change_all_ally_units_hp.cpp',
  'src/sequence/event_factories/change_all_enemy_units_hp.cpp',
  'src/sequence/event_factories/change_current_unit_hp.cpp',
  'src/sequence/event_factories/change_current_unit_sprite.cpp',
  'src/sequence/event_factories/change_map.cpp',
  'src/sequence/event_factories/change_sprite.cpp',
  'src/sequence/event_factories/change_target_hp.cpp',
  'src/sequence/event_factories/delay.cpp',
  'src/sequence/event_factories/disable_player_actions.cpp',
  'src/sequence/event_factories/display_text.cpp',
  'src/sequence/event_factories/echo.cpp',
  'src/sequence/event_factories/enable_player_actions.cpp',
  'src/sequence/event_factories/end_turn.cpp',
  'src/sequence/event_factories/enter_combat.cpp',
  'src/sequence/event_factories/finish_quest.cpp',
  'src/sequence/event_factories/give_item.cpp',
  'src/sequence/event_factories/hide_gui.cpp',
  'src/sequence/event_factories/move_camera.cpp',
  'src/sequence/event_factories/move_entity.cpp',
  'src/sequence/event_factories/play_music.cpp',
  'src/sequence/event_factories/play_sound.cpp',
  'src/sequence/event_factories/remove_item.cpp',
  'src/sequence/event_factories/remove_sprite.cpp',
  'src/sequence/event_factories/reset_current_unit_sprite.cpp',
  'src/sequence/event_factories/rotate_entity.cpp',
  'src/sequence/event_factories/rotate_player.cpp',
  'src/sequence/event_factories/select_target.cpp',
  'src/sequence/event_factories/set_layer_opacity.cpp',
  'src/sequence/event_factories/show_gui.cpp',
  'src/sequence/event_factories/teleport_camera_to_player.cpp',
  'src/sequence/event_factories/teleport_entity.cpp',
  'src/sequence/event_factories/teleport_player.cpp',
  'src/sequence/event_factories/zoom_camera.cpp',
  'src/sequence/events/activate_sequence.cpp',
  'src/sequence/events/add_quest.cpp',
  'src/sequence/events/add_to_party.cpp',
  'src/sequence/events/change_all_ally_units_hp.cpp',
  'src/sequence/events/change_all_enemy_units_hp.cpp',
  'src/sequence/events/change_current_unit_hp.cpp',
  'src/sequence/events/change_current_unit_sprite.cpp',
  'src/sequence/events/change_map.cpp',
  'src/sequence/events/change_sprite.cpp',
  'src/sequence/events/change_target_hp.cpp',
  'src/sequence/events/delay.cpp',
  'src/sequence/events/disable_player_actions.cpp',
  'src/sequence/events/display_text.cpp',
  'src/sequence/events/echo.cpp',
  'src/sequence/events/enable_player_actions.cpp',
  'src/sequence/events/end_turn.cpp',
  'src/sequence/events/enter_combat.cpp',
  'src/sequence/events/finish_quest.cpp',
  'src/sequence/events/give_item.cpp',
  'src/sequence/events/hide_gui.cpp',
  'src/sequence/events/move_camera.cpp',
  'src/sequence/events/move_entity.cpp',
  'src/sequence/events/play_music.cpp',
  'src/sequence/events/play_sound.cpp',
  'src/sequence/events/remove_item.cpp',
  'src/sequence/events/remove_sprite.cpp',
  'src/sequence/events/reset_current_unit_sprite.cpp',
  'src/sequence/events/rotate_entity.cpp',
  'src/sequence/events/rotate_player.cpp',
  'src/sequence/events/select_target.cpp',
  'src/sequence/events/set_layer_opacity.cpp',
  'src/sequence/events/show_gui.cpp',
  'src/sequence/events/teleport_camera_to_player.cpp',
  'src/sequence/events/teleport_entity.cpp',
  'src/sequence/events/teleport_player.cpp',
  'src/sequence/events/zoom_camera.cpp',
  'src/sequence/sequence.cpp',
  'src/templating/templated.cpp',
  'src/text_box.cpp',
  'src/utils/colour.cpp',
  'src/utils/file.cpp',
  'src/utils/filesystem.cpp',
  'src/utils/fuzzy_match.cpp',
  'src/utils/json.cpp',
  'src/utils/log.cpp',
  'src/utils/string.cpp',
  'src/version.cpp',
]

deps = [
  raylib_lib,
]

# Custom options
build_options = []

# Custom options for Windows cross-compiling
if host_machine.system() == 'windows'
  deps += meson.get_compiler('cpp').find_library('winmm')
  build_options = ['werror=false', 'unity=on', 'buildtype=release']
endif

# Custom options for release builds
if get_option('buildtype') == 'release'
  build_options = ['werror=false', 'unity=on', 'warning_level=0']
endif

# Custom options for debug builds
if get_option('buildtype') == 'debug'
  build_options = ['werror=true', 'unity=off', 'warning_level=3']
endif

executable('sage', src,
  dependencies : deps,
  include_directories : [vendor_inc, 'src'],
  override_options : build_options,
  #cpp_args : '-ftime-trace',
  link_args : '-lm',
  link_with : vendor_lib
)
