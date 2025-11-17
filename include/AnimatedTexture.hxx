#ifndef ANIMATED_TEXTURE_H
#define ANIMATED_TEXTURE_H

#include "globals.hxx"
#include "transform.hxx"
#include <chrono>

/** 
 * @brief ## Animated texture class.
 * @brief Manage a texture with an animation. 
 */
class AnimatedTexture{
private:
    std::vector<Texture2D> frames;                           // A vector storing the texture data of each frame.
    std::chrono::milliseconds ms_per_frame;                  // Time between frames. Inversely proportional to `fps`.
    std::chrono::steady_clock::time_point last_frame_change; // Time since `current_frame` was last increased.
    int current_frame;                                       // Index of the currently active frame.
    bool loop;                                               // Whether to reset the index to 0 after reaching `frames.size()`.
    bool play;                                               // Whether the animation is playing.

    std::string texture_names; // Auxiliary variable for texture initialization.
    bool initialized;          // Whether the texture is correctly initialized.
    
    void LoadFrames(std::string texture_name, int frame_count);
public:
    /** 
     * @brief Default constructor, creates the AnimatedTextue as
     * one singular frame with the default texture and no loop.
     */
    AnimatedTexture();
    /**
     * @brief Create an AnimatedTexture given some parameters:
     * @param texture_name The name of the textures.
     * @param frame_count Number of frames.
     * @param fps Target fps of the animation.
     * @param _loop Whether to return to frame 0 instead of stopping at frame `frame_count`.
     * @note This constructor uses a naming convention that looks for files named "texture_name_0.png" up to "texture_name_`frame_count`.png".
     */
    AnimatedTexture(std::string texture_name, int frame_count, int fps = 60, bool _loop = true);
    /**
     * @brief Correctly cleans all memory reserved by the object.
     */
    ~AnimatedTexture();

    /**
     * @brief Initialize the texture's frames.
     * @note Function must be called after window initialization.
     */
    void Initialize();
    /**
     * @brief Check the initialization state.
     * @return @b True if the texture is ready to be drawn. @b False otherwise.
     * @note If @b false, the texture will not be rendered.
     */
    bool IsInitialized() const;

    /**
     * @brief Begin playing the animation.
     * @note If previously paused, the animation will restart at frame 0.
     */
    void Play();
    /**
     * @brief Pause playing the animation.
     */
    void Pause();
    /**
     * @brief Resume paused animation.
     * @note Textures begin paused, so this can be used instead of `Play()` under certain conditions.
     */
    void Resume();
    /**
     * @brief Pauses and resets the animation to frame 0.
     */
    void Stop();
    /**
     * @brief Resets the animation to frame 0
     * @note If the @b AnimatedTexture was previously unpaused, this function will not pause it.
     */
    void Reset();

    /**
     * @brief Draw the @b AnimatedTexture.
     * @param transform The location, orientation and scaling of the texture.
     */
    void Draw(Transform2D transform) const;
    /**
     * @brief Update the @b AnimatedTexture. Carries out all the logic for frame changing and time calculation.
     */
    void Update();
};

#endif