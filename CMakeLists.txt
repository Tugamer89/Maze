cmake_minimum_required(VERSION 3.14)

# Nome del progetto e linguaggio
project(MazeGame CXX)

# Richiedi C++17 (consigliato per lo sviluppo moderno con SFML)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Gestione delle dipendenze: Scarica SFML automaticamente
# -----------------------------------------------------------------------------
include(FetchContent)

message(STATUS "Scaricamento di SFML 2.6.x in corso...")
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.x # Usa l'ultimo branch stabile della versione 2
)

# Disabilita la compilazione di moduli SFML che non ti servono (audio, network)
set(SFML_BUILD_AUDIO FALSE CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK FALSE CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

# -----------------------------------------------------------------------------
# Configurazione dell'eseguibile
# -----------------------------------------------------------------------------

# Elenco dei file sorgente
set(SOURCES
    source/main.cpp
    source/drawer.cpp
    source/global.cpp
    source/maze.cpp
    source/player.cpp
    source/ray.cpp
)

# Crea l'eseguibile
add_executable(maze ${SOURCES})

# Includi la cartella degli header
target_include_directories(maze PRIVATE source/headers)

# Collega le librerie SFML necessarie
target_link_libraries(maze PRIVATE sfml-graphics sfml-window sfml-system)

# -----------------------------------------------------------------------------
# Gestione degli Asset (Font)
# -----------------------------------------------------------------------------
# Copia il file OpenSans.ttf nella directory di build in modo che l'eseguibile possa trovarlo
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/OpenSans.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
