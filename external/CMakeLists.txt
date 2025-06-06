# Required system packages
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)

# Header-only libraries
add_library(vma INTERFACE)
target_include_directories(vma INTERFACE vma)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
set_target_properties(glm PROPERTIES FOLDER "engine/external")

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
set_target_properties(stb_image PROPERTIES FOLDER "engine/external")

# vkbootstrap
add_library(vkbootstrap STATIC)

target_sources(vkbootstrap PRIVATE 
  vkbootstrap/VkBootstrap.h
  vkbootstrap/VkBootstrap.cpp
  )

target_include_directories(vkbootstrap PUBLIC vkbootstrap)
target_link_libraries(vkbootstrap PUBLIC Vulkan::Vulkan $<$<BOOL:UNIX>:${CMAKE_DL_LIBS}>)
set_property(TARGET vkbootstrap PROPERTY CXX_STANDARD 20)

# SDL3
add_subdirectory(SDL)  
# Organize all SDL-related targets under "engine/external"
get_property(SDL_TARGETS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SDL PROPERTY BUILDSYSTEM_TARGETS)
foreach(tgt IN LISTS SDL_TARGETS)
    if (TARGET ${tgt})
        set_target_properties(${tgt} PROPERTIES FOLDER "engine/external")
    endif()
endforeach()


# fmt
add_subdirectory(fmt EXCLUDE_FROM_ALL)
target_link_libraries(tiny_ape_light_engine PRIVATE fmt::fmt)
set_target_properties(fmt PROPERTIES FOLDER "engine/external")

# glad
add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set_target_properties(glad PROPERTIES FOLDER "engine/external")

# imgui
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/backends/imgui_impl_vulkan.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_sdl3.cpp
)
set_target_properties(imgui PROPERTIES FOLDER "engine/external")

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
target_link_libraries(imgui PUBLIC Vulkan::Vulkan SDL3::SDL3 OpenGL::GL)


# Disable all warnings for targets using VMA
if(MSVC)
    target_compile_options(vma INTERFACE /W0)  # MSVC: disable all warnings
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|Intel")
    target_compile_options(vma INTERFACE -w)   # GCC/Clang/Intel: disable all warnings
endif()

