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

set(SOURCES
    src/main.cpp
    src/ofApp.cpp
        src/kll/MidiTriggers.cpp src/kll/MidiTriggers.h src/FeedbackTunnel.cpp src/FeedbackTunnel.h src/kll/PercussionVisuals.cpp src/kll/PercussionVisuals.h src/kll/Environment.cpp src/kll/Environment.h src/kll/Object.cpp src/kll/Object.h src/kll/Block.cpp src/kll/Block.h src/3rdparty/par_shapes.h src/kll/Mesh.cpp src/kll/Mesh.h src/3rdparty/par_shapes.c src/kll/Behaviours/ImplodeBehaviour.cpp src/kll/Behaviours/ImplodeBehaviour.h src/kll/Behaviours/Behaviour.cpp src/kll/Behaviours/Behaviour.h src/kll/Behaviours/FallBehaviour.cpp src/kll/Behaviours/FallBehaviour.h src/kll/kll.h src/kll/kll.cpp src/kll/Behaviours/AddRotationBehaviour.cpp src/kll/Behaviours/AddRotationBehaviour.h src/kll/Clock.cpp src/kll/Clock.h src/kll/LuaMidiSender.cpp src/kll/LuaMidiSender.h src/kll/Engine.cpp src/kll/Engine.h)

set(SWIG_OUTPUT src/swig/Environment_wrap.cxx)

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
cotire(${APP})
