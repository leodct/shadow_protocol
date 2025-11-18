#include "globals.hxx"
#include "scene.hpp"

Camera2D camera = {};

void ThrowNotFoundException(const std::string &id)
{
    throw std::out_of_range("Error. Object with id " + id + " not found. Terminating abnormally...");
}

void DefaultCallback()
{
    std::cout << "Default button callback!" << std::endl;
}

Shader button_shader = {};
void InitButtonShader()
{
    button_shader = LoadShader(TextFormat("%s/outline.vs", SHADERS_PATH.string().c_str()), TextFormat("%s/outline.fs", SHADERS_PATH.string().c_str()));

    Vector2 texSize = { 64.0f, 64.0f }; // Default (will be updated per texture)
    int texSizeLoc = GetShaderLocation(button_shader, "texSize");
    SetShaderValue(button_shader, texSizeLoc, &texSize, SHADER_UNIFORM_VEC2);

    float outlineSize = 2.0f;
    int outlineSizeLoc = GetShaderLocation(button_shader, "outlineSize");
    SetShaderValue(button_shader, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);

    Vector4 outlineColor = {1.0f, 1.0f, 1.0f, 1.0f}; // white
    int outlineColorLoc = GetShaderLocation(button_shader, "outlineColor");
    SetShaderValue(button_shader, outlineColorLoc, &outlineColor, SHADER_UNIFORM_VEC4);

    Vector4 colorMod = {1, 1, 1, 0}; // Set shader tint alpha to 0% (aka no tint)

    int colorModLoc = GetShaderLocation(button_shader, "tintCol");
    SetShaderValue(button_shader, colorModLoc, &colorMod, SHADER_UNIFORM_VEC4);
}

void ConfigButtonShader(bool outline, float thickness)
{
    int hover = outline;
    int hoverLoc = GetShaderLocation(button_shader, "hover");
    SetShaderValue(button_shader, hoverLoc, &hover, SHADER_UNIFORM_INT);

    int outlineSizeLoc = GetShaderLocation(button_shader, "outlineSize");
    SetShaderValue(button_shader, outlineSizeLoc, &thickness, SHADER_UNIFORM_FLOAT);
}