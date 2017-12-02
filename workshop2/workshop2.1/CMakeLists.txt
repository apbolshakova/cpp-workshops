add_executable(workshop2.1 main.cpp)

target_compile_features(workshop2.1 PUBLIC cxx_std_17) 
target_compile_definitions(workshop2.1 PRIVATE SFML_STATIC)
target_link_libraries(workshop2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})