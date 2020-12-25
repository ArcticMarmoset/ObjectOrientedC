add_executable(vector_example
	vector_example.c
)

target_link_libraries(vector_example
	PUBLIC
		objects
)

add_executable(vehicle_example
	vehicle_example.c
)

target_link_libraries(vehicle_example
	PUBLIC
		objects
)
