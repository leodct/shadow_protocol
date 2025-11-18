#ifndef UI_H
#define UI_H

#include <vector>
#include "globals.hxx"
#include <map>
#include <functional>
#include "gameObject.hxx"


/**
 * @file ui.hxx
 * @brief User Interface (UI) Element classes for managing and rendering UI components in a game engine.
 * 
 * This file provides a set of classes and structures for creating, managing, and rendering various UI components such as buttons, labels,
 * panels, and images. These components are derived from the `UIElement` class and are managed within containers for efficient rendering and interaction.
 * The UI elements can be displayed, updated, and manipulated through a flexible system that supports drawing order, enabling/disabling, and visibility toggling.
 * 
 * ## Classes:
 * - `UIElement`: A base class for all UI elements. Handles the common properties and functionality for UI components such as draw order, visibility, and enabling/disabling update logic.
 * - `UIContainer`: A container for managing and rendering multiple `UIElement` objects. It is responsible for the centralized management of UI elements, including updating and drawing all contained elements.
 * 
 * ## UI Components in the `UI` Namespace:
 * - `Button`: A clickable button that can be pressed and released.
 * - `Panel`: A rectangular UI element, useful for creating backgrounds or containers for other UI elements.
 * - `Label`: Displays text, supporting alignment and font size customization.
 * - `ImageDisplay`: Displays an image/texture at a specified position.
 * - `VariableDisplay`: A template class that displays the value of a variable, updating automatically when the variable changes.
 * 
 * ## Functionality:
 * - **UIElement Class**: Provides methods for enabling, disabling, and controlling the display and update logic of UI components. It also manages the drawing order for rendering.
 * - **UIContainer Class**: Manages multiple `UIElement` instances. It allows adding/removing elements, updating their states, and rendering them in a specific order.
 * - **Interaction**: Each `UIElement` has mechanisms for handling user interaction such as hovering, pressing, and releasing buttons, and for drawing different types of UI elements like text and images.
 * 
 * The system is designed to be flexible and extendable, allowing new UI elements to be added easily by inheriting from the `UIElement` class.
 */


/**
 * @brief ## UI Element class
 * @brief Virtual parent class for all UI Elements. Contains generic methods to Enable/Disable, Show/Hide and modify the draw order.
 */
class UIElement : public GameObject{
protected:
    int  draw_order; // Defines the drawing priority, if 2 elements have different draw orders the one with the higher order will be drawn above the other one.
    bool active;     // Determines whether the `UIElement` should be drawn.
    bool enabled;    // Determines whether the `UIElement` should update.
public:
    /**
     * @brief Create a new, empty UIElement.
     */
    UIElement();
    /**
     * @brief Virtual destructor.
     */
    virtual ~UIElement() = default;

    /**
     * @brief Check the `UIElement`'s draw order.
     * @return An int `draw_order` that determines the drawing priority for the `UIElement`.
     * @note If 2 `UIElement` objects have different draw orders, the one with the highest order will be drawn above.
     */
    int  GetDrawOrder() const;
    /**
     * @brief Set the `UIElement`'s draw order.
     * @param _order An integer determining the new order.
     * @return The `UIElement` object's `draw_order`.
     * @note If 2 `UIElement` objects have different draw orders, the one with the highest order will be drawn above.
     * @note ` @p _order ` Must be in the [-100, 100] range. If it is outside it will be clamped.
     */
    void SetDrawOrder(int _order);

    /**
     * @brief Switch the display state (whether to draw the `UIElement` or not). If @b true then @b false and vice-versa.
     */
    void ToggleDisplayState();
    /**
     * @brief Set the display state,
     * @param _active A boolean value telling the `UIElement` whether it sould be drawn or not.
     */
    void SetDisplayState(bool _active);
    /**
     * @brief Check the display state.
     * @return @b True if the `UIElement` will be drawn on next `Draw()` call. @b False otherwise.
     */
    bool GetDisplayState();

    /**
     * @brief Enables the update logic of the object.
     */
    void Enable();
    /**
     * @brief Disables the update logic of the object.
     */
    void Disable();
    /**
     * @brief Toggles the update logic of the object, if @b true then @b false and vice-versa.
     */
    void ToggleEnabled();
    /**
     * @brief Check if the object is enabled, i.e. calling the `Update` function causes it to run the update logic.
     * @return @b True if the next `Update()` call will run the update logic. @b False otherwise.
     */
    bool IsEnabled() const;
    
    /**
     * @brief Draw the `UIElement`.
     */
    virtual void Draw() const = 0;
    /**
     * @brief Update the `UIElement`.
     */
    virtual void Update() = 0;
};

/**
 * @brief ## UIContainer class
 * @brief Stores and manages multiple `UIElement` objects and their memory.
 * @note The `UIContainer` class automatically manages the reserved memory of all it's `UIElement` objects. When given a
 * pointer to an object, said object's ownership will be passed to the respective `UIContainer` for centralized memory management.
 */
class UIContainer {
private:
    /**
     * @brief Container storing all `UIElement` objects and their `std::string` identifiers.
     */
    std::map<std::string, UIElement*> elements;
    /**
     * @brief Order in which the `UIContainer` will be drawn.
     */
    int draw_order;
public:
    /**
     * @brief Default constructor. Creates an empty `UIContainer` object with no elements and a `draw_order` of zero.
     */
    UIContainer();
    /**
     * @brief Automatically cleans up the memory of all the stored `UIElement` objects.
     */
    ~UIContainer();

    /**
     * @brief Store a new `UIElement` with an identifier ` @p id `.
     * @param id String identifier of the @p _element.
     * @param _element Pointer to the `UIElement` that will be stored.
     * @note Ownership of @p _element will be passed to the `UIContainer` object.
     */
    void AddElement(std::string id, UIElement* _element);
    /**
     * @brief Remove an element given by it's unique identifier.
     * @param id String identifier of the desired `UIElement`.
     * @warning The removed element's memory will also be liberated! Plan accordingly!
     */
    void RemoveElement(std::string id);
    /**
     * @brief Get a reference to a stored `UIElement`.
     * @param id String identifer of the desired `UIElement`.
     * @return A @b non-constant reference to the `UIElement` identified by @p id.
     */
    UIElement              &GetElement(std::string id);
    /**
     * @brief Get a @b constant reference to a stored `UIElement`.
     * @param id String identifier of the desired `UIElement`.
     * @return A @b constant reference to the `UIElement` identified by @p id.
     */
    const UIElement        &GetElement(std::string id) const;

    /**
     * @brief Get this `UIContainer` object's `draw_order`.
     * @note If 2 `UIElement` objects have different draw orders, the one with the highest order will be drawn above.
     */
    int  GetDrawOrder() const;
    /**
     * @brief Change this `UIContaier` object's `draw_order` to @p _order.
     * @param _order An integer determining the new order.
     * @note If 2 `UIElement` objects have different draw orders, the one with the highest order will be drawn above.
     * @note ` @p _order ` Must be in the [-100, 100] range. If it is outside it will be clamped.
     */
    void SetDrawOrder(int _order);

    /**
     * @brief Calls the `Update()` method on all stored `UIElement` objects.
     */
    void Update();
    /**
     * @brief Calls the `Draw()` method on all stored `UIElement` objects.
     */
    void Draw() const;

    /**
     * @brief Calls the `Enable()` method on all stored `UIElement` objects.
     */
    void EnableAll();
    /**
     * @brief Calls the `Disable()` method on all stored `UIElement` objects.
     */
    void DisableAll();
    /**
     * @brief Calls the `SetDisplayState( @p value )` method on all stored `UIElement` objects.
     * @param value Value to set as `display_state` on all stored `UIElement` objects.
     */
    void SetAllVisibilityTo(bool value);
};

/**
 * @brief Namespace containing all child classes of `UIElement`.
 */
namespace UI
{

    // --------------------
    // --- BUTTON CLASS ---
    // --------------------
    /**
     * @brief ## Basic button class.
     */
    class Button : public UIElement {
    private:
        Texture2D texture;                      /** @brief Base `Button` texture.                                                 */
        static Color TINT_PRESS;                /** @brief Tint to apply to the texture when `Button` is pressed.                 */
        bool hover;                             /** @brief Whether the mouse is hovering over the `Button`.                       */
        bool press;                             /** @brief Whether `MOUSE_BUTTON_LEFT` is being pressed while `hover` is @b true. */
        Rectangle hitbox;                       /** @brief Rectangle that defines the bounds of the `Button`                      */
        std::function<void()> callbackFunction; /** @brief Function to be called when the `Button` is released.                   */
        /**
         * @brief Auxiliary function for initializing `Button` parameters.
         */
        void InitButton();   
        /**
         * @brief Auxiliary function for initializing the `Button` texture.
         */    
        void TextureSetup();


    public:
        /**
         * @brief Create a new `Button` object with a texture given by ` @p _texture `, with a transform given by ` @p _transform ` and with a default callback.
         * @param _texture Texture that defines how the `Button` object should be drawn.
         * @param _transform Transform that defines the `Button` object.
         */
        Button(Texture2D _texture, Transform2D _transform);

        /**
         * @brief Check whether the `Button` is being pressed.
         * @return @b True if `MOUSE_BUTTON_LEFT` is being pressed while @b `IsHover()` is @b true. @b False otherwise.
         */
        bool IsPressed() const;
        /**
         * @brief Check whether the `Button` object is no longer being pressed.
         * @return @b True if the `Button` object is not being pressed in the
         * current update cycle but was in the previous one. @b False otherwise.
         */
        bool IsReleased() const;
        /**
         * @brief Check whether the mouse cursor is hovering over the `Button` object.
         * @return @b True If the position of the mouse cursor lies within the bounds of
         * the `Button` object defined by `hitbox`. @b False otherwise.
         */
        bool IsHover() const;

        /**
         * @brief Define the function to be called when the button is released.
         * @param callback Function to be called.
         */
        void DefineOnPressCallback(std::function<void()> callback);

        /**
         * @brief Run the updating logic on the `Button` object. Calculates `hover` 
         * and `press`, and determine if the `callbackFunction` should be called.
         */
        void Update() override;
        /**
         * @brief Draw the `Button` object.
         */
        void Draw() const override;
    };

    // -------------------
    // --- PANEL CLASS ---
    // -------------------
    /**
     * @brief ## Panel class.
     */
    class Panel : public UIElement{
    private:
        Color   col;                 // Main panel colour.
        Color   edge_col;            // Panel edge colour.
        Vector2 dimensions;          // Panel dimensions.
        unsigned int edge_thickness; // Panel edge thickness.
    public:
        /**
         * @brief Create a new `Panel` with default parameters. 
         */
        Panel(Transform2D _transform = {}, Vector2 _dimensions = {0,0}, Color _col = {255, 255, 255, 255}, Color _edge_col = {255, 255, 255, 255}, unsigned int _edge_thickness = 0);

        /**
         * @brief Draw the panel.
         */
        void Draw() const override;
        /**
         * @brief Update the panel.
         */
        void Update() override;
    };

    // -------------------
    // --- LABEL CLASS ---
    // -------------------
    /**
     * @brief ## Label class.
     * @brief Allows for drawing text as a `UIElement`.
     */
    class Label : public UIElement{
    public:
        /**
         * @brief Determine whether the position given by the object's `transform` parameter is the `LEFT`, `MIDDLE` or `RIGHT`.
         */
        enum class ALIGNMENT { LEFT, MIDDLE, RIGHT };
    protected:
        Color text_col;         // Label text colour.
        std::string text;       // Label content.
        unsigned int text_size; // Label font size.
        ALIGNMENT alignment;    // Label text alignment.
    public:
        /**
         * @brief Creates a new, empty `Label` object with default parameters.
         */
        Label(Transform2D _transform = {}, std::string _text = "text", unsigned int _text_size = 1, Color _text_col = BLACK, ALIGNMENT _alignment = ALIGNMENT::LEFT);

        /**
         * @brief Get a reference to the text stored in the `Label`.
         * @return A @b non-constant reference to the stored text.
         */
        std::string       &GetText();
        /**
         * @brief Get a @b constant reference to the text stored in the `Label`.
         * @return A @b constant reference to the stored text.
         */
        const std::string &GetText() const;
        /**
         * @brief Change the stored text to a new string.
         * @param _text New text to display in the `Label`.
         */
        void               SetText(std::string _text);

        /**
         * @brief Get the `Label` object's `font_size`.
         * @return An unsigned integer value that determines the font size.
         */
        unsigned int       GetFontSize() const;
        /**
         * @brief Change the `Label` object's `font_size`.
         * @param _size New size.
         */
        void               SetFontSize(unsigned int _size);

        /**
         * @brief Check the `Label` object's text alignmnent.
         * @return The `Label` object's `alignment` value.
         */
        ALIGNMENT         GetAlignment() const;
        /**
         * @brief Change the `Label` object's alignment value.
         * @param _alignment The `Label` object's new alignment value.
         */
        void               SetAlignment(ALIGNMENT _alignment);

        /**
         * @brief Get the text colour.
         * @return An 8 bit RGBA value with the colour of the `Label` object's text.
         */
        Color              GetTextColor() const;
        /**
         * @brief Change the text colour.
         * @param color The new colour to display.
         */
        void               SetTextColor(Color color);

        /**
         * @brief Overriden update method. Does nothing.
         */
        void Update() override = 0;
        /**
         * @brief Draw the `Label` object.
         */
        void Draw() const override;

    };

    // ---------------------------
    // --- IMAGE DISPLAY CLASS ---
    // ---------------------------
    /**
     * @brief ## Image Display class
     * @brief Allows for displaying an Image/Texture2D as a `UIElement`.
     */
    class ImageDisplay : public UIElement {
    private:
        Texture2D image;  // Image to display.
        Vector2   origin; // Point of origin. Set to {`image`.width / 2.0f, `image`.height / 2.0f} to have the image centered around `transform.position`.
        Rectangle sr, dr; // Auxiliary rectangles for the `Draw()` method.
    public:
        /**
         * @brief Create an `ImageDisplay` object with default parameters.
         * @param texture Image to be displayed.
         * @param _transform New object's transform. Determines position, scale and rotation.
         * @param _origin Point of reference from which to draw the ` @p texture `.
         * @note Set ` @p _origin ` to {`image`.width / 2.0f, `image`.height / 2.0f} to have the image centered around ` @p _transform.position `.
         */
        ImageDisplay(Texture2D texture, Transform2D _transform = {}, Vector2 _origin = {});
        /**
         * @brief Safely clean up texture data.
         */
        ~ImageDisplay();

        /**
         * @brief Automatically calculate the center of the `image` and set the `origin` to that point.
         */
        void CenterImage();

        /**
         * @brief Update logic. Calculates where to draw the image using the object's `transform` data.
         */
        void Update() override;
        /**
         * @brief Draw the object.
         */
        void Draw() const override;
    };

    // ------------------------------
    // --- VARIABLE DISPLAY CLASS ---
    // ------------------------------
    /**
     * @brief ## Variable Display class
     * @brief Allows for having a label with a variable value in it. The value will automatically update when the `Update()` method is called.
     * @note This class stores a constant pointer to the variable it displays. Ownership of the object is not passed to this class.
     * @warning This template class is compatible with all data types compatible with the `std::to_string()` method of the STL.
     */
    template <typename T>
    class VariableDisplay : public Label{
    private:
        const T *variable; // Pointer to the variable to be displayed.
    public:
        /**
         * @brief Create a new `VariableDisplay` object with default parameters.
         * @param _variable Constant pointer to the variable to be displayed.
         * @param _transform New object's `transform` value. Determines position, rotation and scale.
         * @param _text_size Font size.
         * @param _text_col Colour with which to draw the object.
         * @param _alignment Whether ` @p transform.position ` is in the @b middle of the text, the @b left or the @b right
         * @warning ` @p _variable ` must @b always have a defined value. Passing an undefined or null pointer @b will cause issues.
         */
        VariableDisplay(const T *_variable, Transform2D _transform = {}, unsigned int _text_size = 1, Color _text_col = BLACK, ALIGNMENT _alignment = ALIGNMENT::LEFT);
        /**
         * @brief Get a reference to the stored `variable`.
         * @return A @b constant reference to the stored `variable`.
         */
        const T &GetVariable() const;

        /**
         * @brief Update the display to have the most recent value stored in `variable`.
         */
        void Update() override;
    };

    template <typename T>
    UI::VariableDisplay<T>::VariableDisplay(const T *_variable, Transform2D _transform, unsigned int _text_size, Color _text_col, ALIGNMENT _alignment) : variable(_variable)
    {
        transform = _transform;
        text_size = _text_size;
        text_col  = _text_col;
        alignment = _alignment;
    }

    template <typename T>
    inline const T &VariableDisplay<T>::GetVariable() const
    {
        return variable;
    }

    template <typename T>
    inline void VariableDisplay<T>::Update()
    {
        text = std::to_string(*variable);
    }
}
#endif // UI_H
