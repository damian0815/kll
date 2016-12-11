project(ofApp)
set(APP ofApp)

cmake_minimum_required(VERSION 2.8)

include(../of/openFrameworks.cmake)

ofxaddon(ofxMidi)
find_library(COREMIDI CoreMIDI)

set(ADDONS_LIBRARIES ${COREMIDI})
set(APP_LIBRARIES fmt)

set(SOURCES
    src/main.cpp
    src/ofApp.cpp
        src/MidiTriggers.cpp src/MidiTriggers.h src/FeedbackTunnel.cpp src/FeedbackTunnel.h src/kll/PercussionVisuals.cpp src/kll/PercussionVisuals.h src/kll/Environment.cpp src/kll/Environment.h src/kll/Object.cpp src/kll/Object.h src/kll/Block.cpp src/kll/Block.h src/3rdparty/par_shapes.h src/kll/Mesh.cpp src/kll/Mesh.h src/3rdparty/par_shapes.c src/kll/ImplodeBehaviour.cpp src/kll/ImplodeBehaviour.h src/kll/Behaviour.cpp src/kll/Behaviour.h src/kll/FallBehaviour.cpp src/kll/FallBehaviour.h src/kll/kll.h src/kll/kll.cpp)

add_executable(
    ${APP}
    MACOSX_BUNDLE
    ${SOURCES}
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
