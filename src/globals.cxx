#include "globals.hxx"
#include "scene.hpp"

Camera2D  camera                          = {};
Settings gameSettings                     = { false, 90, 0.15f };
bool closeGame                            = false;
SceneManager scene_manager;


// --- SHADER SHENANIGANS ---

Shader outline_shader = {};
void InitShaders()
{
    outline_shader = LoadShader(TextFormat("%s/outline.vs", SHADERS_PATH.string().c_str()), TextFormat("%s/outline.fs", SHADERS_PATH.string().c_str()));

    Vector2 texSize = { 64.0f, 64.0f }; // Default (will be updated per texture)
    int texSizeLoc = GetShaderLocation(outline_shader, "texSize");
    SetShaderValue(outline_shader, texSizeLoc, &texSize, SHADER_UNIFORM_VEC2);

    float outlineSize = 2.0f;
    int outlineSizeLoc = GetShaderLocation(outline_shader, "outlineSize");
    SetShaderValue(outline_shader, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);

    Vector4 outlineColor = {1.0f, 1.0f, 1.0f, 1.0f}; // white
    int outlineColorLoc = GetShaderLocation(outline_shader, "outlineColor");
    SetShaderValue(outline_shader, outlineColorLoc, &outlineColor, SHADER_UNIFORM_VEC4);

    Vector4 colorMod = {1, 1, 1, 0}; // Set shader tint alpha to 0% (aka no tint)

    int colorModLoc = GetShaderLocation(outline_shader, "tintCol");
    SetShaderValue(outline_shader, colorModLoc, &colorMod, SHADER_UNIFORM_VEC4);
}

void ConfigOutlineShader(bool outline, float thickness)
{
    int hover = outline;
    int hoverLoc = GetShaderLocation(outline_shader, "hover");
    SetShaderValue(outline_shader, hoverLoc, &hover, SHADER_UNIFORM_INT);

    int outlineSizeLoc = GetShaderLocation(outline_shader, "outlineSize");
    SetShaderValue(outline_shader, outlineSizeLoc, &thickness, SHADER_UNIFORM_FLOAT);
}

void ThrowNotFoundException(const std::string &id)
{
    throw std::out_of_range("Error. Object with id " + id + " not found. Terminating abnormally...");
}