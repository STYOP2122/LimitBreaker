cmake_minimum_required(VERSION 3.15)


project(RemoveLimits)


include(FetchContent)


FetchContent_Declare(
	xbyak    
	GIT_REPOSITORY https://github.com/herumi/xbyak.git
	GIT_TAG ce083a0dcc306c1717685a81f577a4e050193919
)

FetchContent_Declare( 
	ktsignal
	GIT_REPOSITORY https://github.com/kin4stat/ktsignal.git
	GIT_TAG f08a19d9a00ad5284871bf44178d835da7b26ebf
)

FetchContent_Declare( 
	kthook
	GIT_REPOSITORY https://github.com/kin4stat/kthook.git
	GIT_TAG 21ca70481273d1efcc98ca49063178e46277009b
)

FetchContent_Declare( 
	memwrapper
	GIT_REPOSITORY https://github.com/The-Musaigen/memwrapper.git
	GIT_TAG 7d51e3134d8f955651ef7dda8bab44b0efb0665f
)

FetchContent_MakeAvailable(xbyak ktsignal kthook memwrapper)



add_library(${PROJECT_NAME} SHARED
    src/main.cpp
)



add_library(memwrapper INTERFACE)
target_include_directories(${PROJECT_NAME} PUBLIC ${memwrapper_SOURCE_DIR})


target_link_libraries(${PROJECT_NAME}
	kthook
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX .asi
    CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)