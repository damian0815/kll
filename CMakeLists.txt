project(ofApp)
set(APP ofApp)

cmake_minimum_required(VERSION 2.8)

include(../of/openFrameworks.cmake)

ofxaddon(ofxMidi)
find_library(COREMIDI CoreMIDI)

ofxaddon(ofxLua)
# manually remove ios and linux lua bindings
list(REMOVE_ITEM OFXADDONS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ofxLua/src/bindings/ios/ofxLuaBindings.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ofxLua/src/bindings/linuxarm/ofxLuaBindings.cpp)

set(ADDONS_LIBRARIES ${COREMIDI})
set(APP_LIBRARIES fmt)


# swig
set(SWIG_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/swig/Environment.i)
set(SWIG_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/swig/Environment_wrap.cxx)
set(SWIG_DEPENDENCIES ${SWIG_INPUT} ${CMAKE_CURRENT_SOURCE_DIR}/src/kll/Engine/Environment.h)

add_custom_command(
        OUTPUT ${SWIG_OUTPUT}
        COMMAND swig -lua -c++ -I/usr/local/include -o ${SWIG_OUTPUT} ${SWIG_INPUT}
        DEPENDS ${SWIG_DEPENDENCIES}
)


set(SOURCES
    src/main.cpp
    src/ofApp.cpp
        src/kll/Engine/MidiTriggers.cpp src/kll/Engine/MidiTriggers.h src/FeedbackTunnel.cpp src/FeedbackTunnel.h src/kll/PercussionVisuals.cpp src/kll/PercussionVisuals.h src/kll/Engine/Environment.cpp src/kll/Engine/Environment.h src/kll/Object.cpp src/kll/Object.h src/kll/Block.cpp src/kll/Block.h src/3rdparty/par_shapes.h src/kll/Mesh.cpp src/kll/Mesh.h src/3rdparty/par_shapes.c src/kll/Behaviours/ImplodeBehaviour.cpp src/kll/Behaviours/ImplodeBehaviour.h src/kll/Behaviours/Behaviour.cpp src/kll/Behaviours/Behaviour.h src/kll/Behaviours/FallBehaviour.cpp src/kll/Behaviours/FallBehaviour.h src/kll/kll.h src/kll/kll.cpp src/kll/Behaviours/AddRotationBehaviour.cpp src/kll/Behaviours/AddRotationBehaviour.h src/kll/Engine/Clock.cpp src/kll/Engine/Clock.h src/kll/Engine/LuaMidiSender.cpp src/kll/Engine/LuaMidiSender.h src/kll/Engine/Engine.cpp src/kll/Engine/Engine.h src/kll/Engine/FileWatcher.cpp src/kll/Engine/FileWatcher.h
        src/3rdparty/picosha2.h)

add_executable(
    ${APP}
    MACOSX_BUNDLE
    ${SOURCES}
    ${SWIG_OUTPUT}
    ${OFXADDONS_SOURCES}
)

target_link_libraries(
        ${APP}
        ${APP_LIBRARIES}
        ${ADDONS_LIBRARIES}
        ${OPENFRAMEWORKS_LIBRARIES}
)

set_target_properties(
    ${APP} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST
    "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)


set_target_properties(${APP} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
#cotire(${APP})
