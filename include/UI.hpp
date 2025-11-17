#ifndef UI_H
#define UI_H

#include <vector>
#include "globals.hxx"
#include <map>
#include "transform.hxx"
#include <functional>
#include "gameObject.hxx"

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
     * @param _order New `draw_order` to be set.
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
     * @brief Basic button class.
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
    class Panel : public UIElement{
    private:
        Color   col;
        Color   edge_col;
        Vector2 dimensions;
        unsigned int edge_thickness;
    public:
        Panel(Transform2D _transform = {}, Vector2 _dimensions = {0,0}, Color _col = {255, 255, 255, 255}, Color _edge_col = {255, 255, 255, 255}, unsigned int _edge_thickness = 0);

        void Draw() const override;
        void Update() override;
    };

    // -------------------
    // --- LABEL CLASS ---
    // -------------------
    class Label : public UIElement{
    public:
        enum class ALIGNMENT { LEFT, MIDDLE, RIGHT };
    protected:
        Color text_col;
        std::string text;
        unsigned int text_size;
        ALIGNMENT alignment;
    public:
        Label(Transform2D _transform = {}, std::string _text = "text", unsigned int _text_size = 1, Color _text_col = BLACK, ALIGNMENT _alignment = ALIGNMENT::LEFT);

        std::string       &GetText();
        const std::string &GetText() const;
        void               SetText(std::string _text);

        unsigned int       GetFontSize() const;
        void               SetFontSize(unsigned int _size);

        ALIGNMENT         GetAlignment() const;
        void               SetAlignment(ALIGNMENT _alignment);

        Color              GetTextColor() const;
        void               SetTextColor(Color color);

        void Update() override;
        void Draw() const override;

    };

    // ---------------------------
    // --- IMAGE DISPLAY CLASS ---
    // ---------------------------
    class ImageDisplay : public UIElement {
    private:
        Texture2D image;
        Vector2   origin;
    public:
        ImageDisplay(Texture2D texture, Transform2D _transform, Vector2 _origin);
        ~ImageDisplay();

        void Draw() const override;
        void Update() override;
    };

    // ------------------------------
    // --- VARIABLE DISPLAY CLASS ---
    // ------------------------------
    template <typename T>
    class VariableDisplay : public Label{
    private:
        const T *variable;
    public:
        VariableDisplay(T *_variable, Transform2D _transform = {}, unsigned int _text_size = 1, Color _text_col = BLACK, ALIGNMENT _alignment = ALIGNMENT::LEFT);
        T   &GetVariable() const;

        void Update() override;
    };

    template <typename T>
    UI::VariableDisplay<T>::VariableDisplay(T *_variable, Transform2D _transform, unsigned int _text_size, Color _text_col, ALIGNMENT _alignment) : variable(_variable)
    {
        transform = _transform;
        text_size = _text_size;
        text_col  = _text_col;
        alignment = _alignment;
    }

    template <typename T>
    inline T &VariableDisplay<T>::GetVariable() const
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
