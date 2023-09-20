# CSCI_5229
Homework assignments for Computer Graphics

----- INSTRUCTIONS FOR COMPILING THIS PROJECT ON WINDOWS -----

--- I.) INSTALL MSYS & OPENGL LIBRARIES ---
1.) Download the MSYS2 installer from here: https://www.msys2.org/
2.) Install using the GUI with all default options & locations
3.) Launch MSYS terminal from the start menu (search for 'MSYS2 MINGW64' in the start bar)
4.) When the terminal comes up, update all packages to the latest version with the pacman command:
    pacman -Syu
5.) Install compiler toolchain (use 'all' option):
    pacman -S --needed base-devel mingw-w64-x86_64-toolchain
6.) Install GLUT and GLEW:
    pacman -S mingw-w64-x86_64-freeglut
    pacman -S mingw-w64-x86_64-glew
7.) Install GLFW:
    pacman -S mingw-w64-x86_64-glfw
8.) Install SDL 1.2:
    pacman -S mingw-w64-x86_64-SDL mingw-w64-x86_64-SDL_mixer mingw-w64-x86_64-SDL_image
9.) Install Vulkan:
    pacman -S mingw-w64-x86_64-vulkan-devel

-- II.) COMPILE PROJECT AND RUN IT ---
1.) Launch MSYS terminal from the start menu (search for 'MSYS2 MINGW64' in the start bar)
2.) Change directories into the location where you cloned this repository:
    cd <location>/CSCI_5229/hw1
3.) Run the make command:
    make
4.) Run the newly-created executable file stored in the hw1 directory:
    <location>/CSCI_5229/hello_world/hello_world.exe
