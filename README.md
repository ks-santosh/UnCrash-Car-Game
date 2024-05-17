# ELEC5620M Mini-Project - UnCrash

## UnCrash - An Obstacle Avoidance Car Game

**UnCrash** is an engaging and dynamic car obstacle avoidance game developed for the DE1-SoC platform. The game challenges players to navigate a vehicle continuously moving through a road filled with obstacles while collecting coins, employing a variety of hardware functionalities of the DE1-SoC platform.

---

#### Table of Contents
1. [Project Contents](#project-contents)
2. [Game Features](#game-features)
3. [Hardware Requirements](#hardware-requirements)
4. [Gameplay](#gameplay)
5. [Technical Details](#technical-details)
6. [Contributors](#contributors)

---
### Project Contents
The following game files are provided to run the game
| File | Purpose |
| ---  | --- |
| `main.c`         | Main function for the UnCrash game |
| `UnCrashLibrary/CheckCollision.c`     | Source - Checks for collision between the car and other objects |
| `UnCrashLibrary/CheckCollision.h`     | Header - Checks for collision between the car and other objects |
| `UnCrashLibrary/Font.c`     | Source - Contains alphanumeric character image array definitions |
| `UnCrashLibrary/Font.h`     | Header - Contains alphanumeric character image array declarations |
| `UnCrashLibrary/PlayAudio.c`     | Source - Plays audio from sounds.c file, and sounds using the DDS technique |
| `UnCrashLibrary/PlayAudio.h`     | Header - Plays audio from sounds.c file, and sounds using the DDS technique |
| `UnCrashLibrary/RenderCar.c`     | Source - Definition of functions to render car and move on key press |
| `UnCrashLibrary/RenderCar.h`     | Header - Declaration of functions to render car and move on key pres |
| `UnCrashLibrary/RenderText.c`     | Source - Definition of functions to render text on LT24 screen  |
| `UnCrashLibrary/RenderText.h`     | Header - Definition of functions to render text on LT24 screen |
| `UnCrashLibrary/RenderWorld.c`     | Source - Definition of functions to manage game world on LT24 screen |
| `UnCrashLibrary/RenderWorld.h`     | Header - Declaration of functions to manage game world on LT24 screen |
| `UnCrashLibrary/SetSevenSegDisp.c`     | Source - Definition of functions to display the score on seven-segment displays |
| `UnCrashLibrary/SetSevenSegDisp.h`     | Header - Declaration of functions to display the score on seven-segment displays |
| `UnCrashLibrary/Sounds.c`     | Source - Contains audio data array definition |
| `UnCrashLibrary/Sounds.h`     | Header - Contains audio data array declaration |
| `UnCrashLibrary/Sprites.c`     | Source - Contains sprites image array definitions |
| `UnCrashLibrary/Sprites.h`     | Header - Contains sprites image array definitions |
---

#### Game Features

- **Graphics Rendering**: Utilizes the LT24 QVGA display for vibrant game graphics.
- **Sound Effects**: Employs the WM8731 audio codec for auditory feedback during gameplay events.
- **Control Mechanisms**: Involves interactive controls using the DE1-SoC's built-in buttons to move the car and navigate through the game.
- **Score Display**: Scores are shown using the Seven Segment display.
- **Speed Control**: The game speed and audio playback are consistently managed across different processor performances using the ARM A9's private timer.

---

#### Hardware Requirements

- **DE1-SoC Board**: Equipped with a Cyclone V SoC and an embedded ARM A9 processor.
- **LT24 Display**: For rendering the game interface.
- **WM8731 Audio Codec**: To handle game sounds.
- **Physical Input**: Buttons on the DE1-SoC used for game controls.

---

#### Gameplay

- **Starting the Game**: Press Key2 to start the game from the start screen.
- **Navigating the Car**: Use Key-3 and Key-0 to move the car left and right.
- **Objective**: Avoid obstacles and collect coins to increase your score.
- **Ending the Game**: The game ends when you crash into an obstacle or reach the maximum score limit of 9999.
- **Game Demonstration**

https://github.com/leeds-embedded-systems/ELEC5620M-Mini-Project-Group-20/assets/159156207/0870e211-42fc-4de3-b663-71328756b652

---

#### Technical Details

- **Game World Rendering**: The game environment is dynamically generated using a random number generator and rendered in blocks of 64x64 pixels.
- **Collision Detection**: Employs pixel-based collision detection algorithms to determine interactions between the car and game objects.
- **Audio Management**: Sounds are generated using Direct Digital Synthesis (DDS) and managed through the audio codec.
- **Text Rendering**: Utilizes custom pixel fonts rendered on the LT24 display to provide high-contrast visibility.
- **Debugging and Verification**: Detailed debugging processes were implemented to ensure stability and performance on the actual hardware.

---

#### Contributors

- **Santosh Kutuwa Shivaram**: Game design, world building, collision checks, text rendering.
- **Aakash Rao**: Car movement and display handling.
- **Yeuhan You**: Game scoring system and display on seven-segment displays.
- **Nikhilesh Bhaskar**: Audio output library for game events.

---
