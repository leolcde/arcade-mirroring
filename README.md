```text

 @@@@@@   @@@@@@@    @@@@@@@   @@@@@@   @@@@@@@   @@@@@@@@
@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@
@@!  @@@  @@!  @@@  !@@       @@!  @@@  @@!  @@@  @@!
!@!  @!@  !@!  @!@  !@!       !@!  @!@  !@!  @!@  !@!
@!@!@!@!  @!@!!@!   !@!       @!@!@!@!  @!@  !@!  @!!!:!
!!!@!!!!  !!@!@!    !!!       !!!@!!!!  !@!  !!!  !!!!!:
!!:  !!!  !!: :!!   :!!       !!:  !!!  !!:  !!!  !!:
:!:  !:!  :!:  !:!  :!:       :!:  !:!  :!:  !:!  :!:
::   :::  ::   :::   ::: :::  ::   :::   :::: ::   :: ::::
 :   : :   :   : :   :: :: :   :   : :  :: :  :   : :: ::

```

First group interface leader : jules.nourdin@epitech.eu<br>
Second group interface leader : noe.becquer@epitech.eu<br>

## Overview & How it works
The Arcade project is an extensible and modular retro-gaming platform. It is split into three main components:
- **The Core**: The main program (`./arcade`). It handles the main loop, menu, user input routing, and dynamic library loading. The Core never directly depends on any specific graphics library (no direct inclusion of ncurses, SDL2, etc.).
- **Game Modules**: Dynamic libraries (`.so`) representing individual games (e.g., Snake, Nibbler). They handle game logic, scoring, and entity updates.
- **Graphics Modules**: Dynamic libraries (`.so`) handling visual rendering and input collection (e.g., Ncurses, SDL2, SFML, LibCaca).

By loading these libraries at runtime, the project can switch games and graphical displays on the fly without recompiling!

## The Concept of Compatibility
A major goal of the Arcade project is compatibility with other groups. This is achieved via two main concepts:
1. **Shared Interfaces (`IGame.hpp` and `IDisplay.hpp`)**: We agreed on generic interfaces that define a strict contract. Any library strictly implementing these interfaces will perfectly plug into our Core program.
2. **DLLoader**: An encapsulated C++ class handling the C-style `libdl` functions (`dlopen`, `dlsym`, `dlclose`). This isolates the dynamic loading logic and guarantees safe integration of external `.so` files at runtime.

## Installation & Usage

**Dependencies for graphics libraries:**
```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
# Additional dependencies for SFML, Ncurses, and LibCaca may be required depending on your OS.
```

**Compilation:**
```bash
make
```

**Running the program:**
```bash
./arcade lib/<arcade_lib_name>.so
```
*Example:* `./arcade lib/arcade_ncurses.so`

### Available Modules
**Games :**
- Snake (`arcade_snake.so`)
- Nibbler (`arcade_nibbler.so`)

**Libraries :**
- Ncurses (`arcade_ncurses.so`)
- SDL2 (`arcade_sdl2.so`)
- SFML (`arcade_sfml.so`)
- LibCaca (`arcade_libcaca.so`)

---

## Documentation: How to implement new libraries

Extending the Arcade system is straightforward. You only need to create a new shared library (`.so`) that inherits from either `IGame` or `IDisplay` and exports an `entryPoint` function so the Core can instantiate it via `dlsym`.

### 1. Implementing a new Game Library
Your game class must inherit from the `IGame` interface defined in `include/IGame.hpp`.

```cpp
#include "IGame.hpp"

class MyCustomGame : public IGame {
public:
    void init() override;
    void stop() override;
    std::string getName() override;

    // Core game loop methods
    void update(Input input) override;
    std::vector<Entity> &getEntities() override;
    std::vector<Text> &getTexts() override;
    int getScore() override;
    bool isGameOver() override;
};

// EXPORT FUNCTION (Required for dlsym)
extern "C" {
    IGame *entryPoint() {
        return new MyCustomGame();
    }
}
```
Compile your game as a dynamic library object (e.g., `arcade_mygame.so`) and place it in the designated `games/` or `lib/` folder.

### 2. Implementing a new Graphics Library
Your display class must inherit from the `IDisplay` interface defined in `include/IDisplay.hpp`.

```cpp
#include "IDisplay.hpp"

class MyCustomDisplay : public IDisplay {
public:
    void init() override;
    void stop() override;
    std::string getName() override;

    // Display module methods
    void clear() override;
    void display() override;
    void drawEntity(const Entity &entity) override;
    void drawText(const Text &text) override;
    Input getInput() override;
};

// EXPORT FUNCTION (Required for dlsym)
extern "C" {
    IDisplay *entryPoint() {
        return new MyCustomDisplay();
    }
}
```
In your implementation, map your specific library's behaviors (e.g., drawing rects, handling keyboard events) to Arcade's generic `Entity`, `Text`, and `Input` structures. Compile this into a shared object (e.g., `arcade_mydisplay.so`).