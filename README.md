<p align="center">
    <a href="https://github.com/Tugamer89/Maze" target="_blank"><img src="https://wakatime.com/badge/user/423e1479-325a-4958-8d21-2d5f97c11efb/project/018eacf7-4f01-4fd4-b2dd-6399812721de.svg?" alt="time"></a>
</p>

# Maze

A little maze manually rendered using Raycasting and C++ with SFML.

## Prerequisites

To build this project, you will need:

- A C++ compiler that supports C++17 (GCC, Clang, MSVC).
- **CMake** (version 3.14 or higher).
- *No need to install SFML manually*: CMake will automatically download and build the correct version (2.6.x) during the configuration step!

## Build and Installation

1. Clone the repository:

   ```bash
   git clone [https://github.com/Tugamer89/Maze.git](https://github.com/Tugamer89/Maze.git)
   cd Maze
   ```

2. Configure the project with CMake (this step will automatically download SFML):

    ```bash
    cmake -B build
    ```

3. Build the game:

    ```bash
    cmake --build build --config Release
    ```

## Running the Game

After a successful build, you can start the game by executing the compiled binary located in the `build` directory.

**On Linux / macOS:**

```bash
./build/maze
```

**On Windows:**

```DOS
.\build\Release\maze.exe
```

### Controls

- **W, A, S, D:** Move the character
- **Right Arrow / Left Arrow:** Rotate the camera
- **F11 / Esc:** Toggle Fullscreen mode
