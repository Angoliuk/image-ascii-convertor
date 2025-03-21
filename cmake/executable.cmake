set(HEADERS
        ./editor/include/editor/utils.hpp
        ./editor/include/editor/image.hpp
        ./editor/include/editor/ascii-preview.hpp
        ./editor/include/editor/components/checkbox.hpp
        ./editor/include/editor/edited-image-preview.hpp
        ./editor/include/editor/filters-container.hpp
        ./editor/include/editor/image-container.hpp
        ./editor/include/editor/image-editor-container.hpp
        ./editor/include/editor/image-picker.hpp
        ./editor/include/editor/main-window.hpp
        ./editor/include/editor/original-image-preview.hpp
        ./editor/include/editor/components/slider.hpp
)

set(SOURCES
        ./editor/src/main.cpp
        ./editor/src/image.cpp
        ./editor/src/ascii-preview.cpp
        ./editor/src/components/checkbox.cpp
        ./editor/src/edited-image-preview.cpp
        ./editor/src/filters-container.cpp
        ./editor/src/image-container.cpp
        ./editor/src/image-editor-container.cpp
        ./editor/src/image-picker.cpp
        ./editor/src/main-window.cpp
        ./editor/src/original-image-preview.cpp
        ./editor/src/components/slider.cpp
)

qt_add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
)

target_include_directories(${PROJECT_NAME} PUBLIC ./editor/include/)
