set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Graphics)
add_subdirectory(SDLSupport)
add_subdirectory(AppEvents)


set_target_properties (SDLSupport PROPERTIES FOLDER libs)
set_target_properties (Graphics PROPERTIES FOLDER libs)
set_target_properties (AppEvents-h PROPERTIES FOLDER libs)

