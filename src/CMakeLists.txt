# Все .cpp файлы из всех подпапок
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Исполняемый файл
add_executable(HeatPipe ${SOURCES})

# Подключаем заголовки
target_include_directories(HeatPipe PRIVATE ${CMAKE_SOURCE_DIR}/include)