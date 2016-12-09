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
        src/MidiTriggers.cpp src/MidiTriggers.h src/FeedbackTunnel.cpp src/FeedbackTunnel.h src/PercussionVisuals.cpp src/PercussionVisuals.h)

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

cotire(${APP})
