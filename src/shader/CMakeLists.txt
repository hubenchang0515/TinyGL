set(SHADER_LIST "default_2d_vertex_shader" "default_2d_fragment_shader" "default_2d_texture_vertex_shader" "default_2d_texture_fragment_shader")

foreach (SHADER ${SHADER_LIST})
    add_custom_target(${SHADER} COMMAND xxd -i ${SHADER}.glsl > ${SHADER}.c WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach (SHADER ${SHADER_LIST})

add_custom_target(shader DEPENDS ${SHADER_LIST})