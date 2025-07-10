find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(booksim_config_parser config.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
            COMPILE_FLAGS "-y -d --file-prefix=${CMAKE_CURRENT_BINARY_DIR}/y")
FLEX_TARGET(booksim_config_lexer config.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
ADD_FLEX_BISON_DEPENDENCY(booksim_config_lexer booksim_config_parser)

set_source_files_properties(
    ${BISON_booksim_config_parser_OUTPUT_SOURCE}                  
    ${FLEX_booksim_config_lexer_OUTPUTS}
    PROPERTIES LANGUAGE CXX
)

list(APPEND booksim_incs 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/allocators
    ${CMAKE_CURRENT_SOURCE_DIR}/arbiters
    ${CMAKE_CURRENT_SOURCE_DIR}/networks
    ${CMAKE_CURRENT_SOURCE_DIR}/power
    ${CMAKE_CURRENT_SOURCE_DIR}/routers
)

list(APPEND booksim_srcs
    # FLEX/BISON Generated Sources
    ${BISON_booksim_config_parser_OUTPUT_SOURCE}
    ${FLEX_booksim_config_lexer_OUTPUTS}
    # Allocators
    allocators/allocator.cpp
    allocators/islip.cpp
    allocators/loa.cpp
    allocators/maxsize.cpp
    allocators/pim.cpp
    allocators/selalloc.cpp
    allocators/separable_input_first.cpp
    allocators/separable_output_first.cpp
    allocators/separable.cpp
    allocators/wavefront.cpp
    # Arbiters
    arbiters/arbiter.cpp
    arbiters/matrix_arb.cpp
    arbiters/prio_arb.cpp
    arbiters/roundrobin_arb.cpp
    arbiters/tree_arb.cpp
    # Networks
    networks/anynet.cpp
    networks/cmesh.cpp
    networks/dragonfly.cpp
    networks/fattree.cpp
    networks/flatfly_onchip.cpp
    networks/fly.cpp
    networks/kncube.cpp
    networks/network.cpp
    networks/qtree.cpp
    networks/tree4.cpp
    # Power
    power/buffer_monitor.cpp
    power/power_module.cpp
    power/switch_monitor.cpp
    # Routers
    routers/chaos_router.cpp
    routers/event_router.cpp
    routers/iq_router.cpp
    routers/router.cpp
    # Others
    batchtrafficmanager.cpp
    booksim_config.cpp
    buffer_state.cpp
    buffer.cpp
    config_utils.cpp
    credit.cpp
    flit.cpp
    flitchannel.cpp
    # gputrafficmanager.cpp
    injection.cpp
    # interconnect_interface.cpp
    main.cpp
    misc_utils.cpp
    module.cpp
    mta_trafficmanager.cpp  # ADDED SOURCE CODE
    outputset.cpp
    packet_reply_info.cpp
    random_utils.cpp
    rng_double_wrapper.cpp
    rng_wrapper.cpp
    routefunc.cpp
    stats.cpp
    traffic.cpp
    trafficmanager.cpp
    vc.cpp
)

# # TARGET: Standalone Booksim Executable
# # list(REMOVE_ITEM ${booksim_srcs} interconnect_interface.cpp)
# add_executable(booksim2_main ${booksim_srcs})
# target_include_directories(booksim2_main PUBLIC  ${booksim_incs})
# target_include_directories(booksim2_main PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
# # # Remove globally set TRACING_ON flag
# # target_compile_options(booksim2_main PRIVATE -UTRACING_ON)

# TARGET: Booksim Library (libbooksim2.a)
add_library(booksim2 STATIC ${booksim_srcs})
target_include_directories(booksim2 PUBLIC  ${booksim_incs})
target_include_directories(booksim2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(booksim2 PRIVATE CREATE_LIBRARY)
set_target_properties(booksim2 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
# # Remove globally set TRACING_ON flag
# target_compile_options(booksim2 PRIVATE -UTRACING_ON)
