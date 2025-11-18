#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"
#include <filesystem>
#include <vector>
#include <iostream>

/**
 * @file globals.hxx
 * @brief This file contains global constants, utility functions, and external references for the game system.
 * @details
 * This file defines some globally accessible constants, utility functions, and external variables used throughout the game system.
 * 
 * It includes paths for resources such as textures, which are located in the `/resources/textures` directory. 
 * These paths are defined relative to the executable's location, and they allow easy access to external assets like textures.
 * 
 * This file also contains a reference to the `SceneManager` object, which is used for managing the game's scenes, as well as constants for controlling the draw order of game objects.
 */


/**
 * ## File Paths
 * 
 * The following paths are useful for accessing the game's resources, especially textures.
 * These paths are based on the current working directory and are relative to the executable.
 */

const std::filesystem::path EXECUTABLE_PATH = std::filesystem::current_path(),  ///< The path to the executable file.
                            RESOURCES_PATH  = EXECUTABLE_PATH / "resources",    ///< The path to the resources directory.
                            TEXTURES_PATH   = RESOURCES_PATH  / "textures",     ///< The path to the textures directory.
                            SHADERS_PATH    = RESOURCES_PATH  / "shaders";      ///< The path to the shaders directory.


/**
 * @brief Auxiliary function. It safely closes the program when it asks for a Scene or UIElement that is not present in their respective container.
 * @param id The string identifier of the item that has not been found. This @p id is shown on screen to facilitate debugging.
 */
[[noreturn]] void ThrowNotFoundException(const std::string &id);

/**
 * @brief Default button callback. Prints a message on the console when a button without a defined callback is clicked.
 */
void DefaultCallback();


const int MIN_DRAW_ORDER = -100; ///< The minimum value for drawing order (used for objects in the background).
const int MAX_DRAW_ORDER =  100; ///< The maximum value for drawing order (used for objects in the foreground).

/**
 * ## The Transform2D Struct
 * 
 * The `Transform2D` struct stores the position, rotation, and scale of an object in 2D space. 
 * 
 * - `position`: A `Vector2` representing the position of the object in 2D space.
 * - `rotation`: A float value representing the rotation of the object in radians.
 * - `scale`: A float value representing the scaling factor of the object, where `1.0f` is the default (no scaling).
 */

 struct Transform2D {
    /**
     * @brief The position of the object in 2D space.
     */
    Vector2 position = {0, 0};

    /**
     * @brief The rotation of the object in radians.
     */
    float rotation = 0.0f;

    /**
     * @brief The scaling factor of the object.
     */
    float scale = 1.0f;
};

extern Camera2D camera; ///< Main camera to be used for rendering.

/**
 * @brief This shader is used internally by the `Button` class
 * @details
 * - If the button is @b idle, then it's texture will be drawn with nothing else.
 * - If the button is @b being @b hovered, it's texture will appear with a slight white tint and a white outline.
 * - If the button is @b being @b pressed, it's texture will appear with a dark tint and a white outline.
 */
extern Shader button_shader;
/**
 * @brief Default thickness value for the button outline.
 */
const float BUTTON_SHADER_OUTLINE_THICKNESS_DEFAULT = 2.0f;

/**
 * @brief Auxiliary function that initializes the button outline shader.
 * @warning This function @b must be called after the window has been initialized.
 */
void InitButtonShader();
/**
 * @brief Auxiliary function used internally by the `Button` class.
 * @param outline Whether to show the white outline or not.
 * @param thickness Size of the outline.
 */
void ConfigButtonShader(bool outline, float thickness = BUTTON_SHADER_OUTLINE_THICKNESS_DEFAULT);

#endif // GLOBALS_H