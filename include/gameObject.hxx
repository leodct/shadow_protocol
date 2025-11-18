#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "globals.hxx"

/**
 * @file GameObject.hxx
 * @brief This file contains the declaration of the GameObject class.
 * @details
 * This file defines the `GameObject` class, which serves as a base class for all game objects in the system. 
 * It provides a common interface for all objects that will exist in the game world by defining core properties and methods that can be shared or overridden by derived classes.
 * 
 * The `GameObject` class includes a `Transform2D` data member, which holds the position, scale, and rotation data for the object. 
 * It also defines pure virtual methods (`Draw()` and `Update()`) that must be implemented by subclasses, allowing each derived object to have its own drawing and update logic.
 * 
 * Key features of the `GameObject` class include:
 * - A common transform system to manage the position, rotation, and scale of objects in 2D space.
 * - Pure virtual methods for drawing and updating, enforcing that all game objects must define how they are rendered and how they behave in the game world.
 * 
 * The `GameObject` class is meant to be subclassed by specific game entities (e.g., player characters, enemies, items) to add specific behaviors and attributes.
 */


/**
 * @brief ## Game Object parent class
 * @brief Pure virtual class to provide generic methods to its child classes.
 */
class GameObject{
protected:
    Transform2D transform; // Position, scale and rotation data.
public:
    /**
     * @brief Create a new `GameObject` object with default parameters.
     * @param _transform New object's `transform` data. Defines position, rotation and scale.
     */
    GameObject(Transform2D _transform = {});
    /**
     * @brief Default virtual destructor.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Get a @b constant reference to the object's `transform` data.
     * @return A @b constant reference to the object's `transform` data.
     */
    const Transform2D &GetTransform() const;
    /**
     * @brief Get a reference to the object's `transform` data.
     * @return A @b non-constant reference to the object's `transform` data.
     */
    Transform2D       &GetTransform();

    /**
     * @brief Pure virtual function to be overriden in child classes.
     */
    virtual void Draw() const = 0;
    /**
     * @brief Pure virtual function to be overriden in child classes.
     */
    virtual void Update()     = 0;
};
#endif