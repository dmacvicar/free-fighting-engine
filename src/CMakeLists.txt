
find_package(Allegro)

set(koflinux_SRCS
  2xsai.c
  auto_conf.c
  background_output.c
  background_process.c
  battle_output.c
  battle_process.c
  choice_output.c
  choice_process.c
  effects.c
  initfiles.c
  input_reader.c
  keyconfig_output.c
  keyconfig_process.c
  load_characters.c
  loader.c
  load_fight_fx.c
  loads.c
  load_sprites.c
  logger.c
  main.c
  main_output.c
  main_process.c
  moves.c
  mp3.c
  option_output.c
  option_process.c
  player_output.c
  player_process.c
  read_config.c
  refresh.c
  select_output.c
  select_process.c
  sensei_config.c
  sound_fx_manager.c
  storyboard_output.c
  storyboard_process.c
  story_output.c
  story_process.c
  vs_output.c
  vs_process.c
)

add_executable(koflinux ${koflinux_SRCS})
target_link_libraries(koflinux ${ALLEGRO_LIBRARY})

