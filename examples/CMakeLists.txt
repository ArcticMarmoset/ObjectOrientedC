add_executable(vector_example
	vector_example.c
)

get_target_property(CONTAINERS_INCLUDES containers INCLUDE_DIRECTORIES)

target_link_libraries(vector_example
	PUBLIC
		containers
)
