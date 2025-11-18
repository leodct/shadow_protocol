#ifndef SCENE_H
#define SCENE_H

#include "globals.hxx"
#include "UI.hpp"
#include "gameObject.hxx"

/**
 * @file scene.hxx
 * @brief This file contains the `Scene` and `SceneManager` classes.
 * @details
 * This file defines the `Scene` class, which acts as a container for `GameObject` and `UIContainer` objects that should be displayed in the same location.
 * It also defines the `SceneManager` class, which is responsible for managing and switching between scenes.
 */

 
/**
 * @brief ## Scene class
 * @brief A container for all `GameObject` and `UIContainer` objects that should be displayed in the same place.
 * @note Once given a pointer to a `GameObject` or `UIContainer`, this class becomes owner of said object and will liberate their memory on it's own.
 */
class Scene {
private:
    /**
     * @brief Map containing all the `UIContainer` objects stored in the scene.
     */
    std::map<std::string, UIContainer*> interfaces;
    /**
     * @brief Map containing all `GameObject` objects stored in the scene.
     */
    std::map<std::string, GameObject*>  objects;
public:
    /**
     * @brief Default constructor. Creates a completely empty scene.
     */
    Scene();
    /**
     * @brief Destructor. Correctly cleans up all memory related to the `Scene` object's elements.
     * @warning The `Scene` object is owner of all pointers given to it to facilitate centralized memory cleanups. This means the user is not
     * required to call the @b delete function on all of the `Scene` object's elements as the parent object will take care of it upon it's
     * destruction.
     */
    ~Scene();
    
    /**
     * @brief Add a new `UIContainer` to the scene.
     * @param id Text associated with the inserted `_ui`. This std::string will be the identifier of `_ui`.
     * @param _ui The UIContainer to add to the `Scene`.
     * @note Ownership of `_ui` will be given to the `Scene` object for more centralized memory management.
     */
    void AddUi(const        std::string &id, UIContainer *_ui);
    /**
     * @brief Remove a `UIContainer` element given it's identifier.
     * @param id Identifier of the element to remove.
     * @warning This will also free the memory occupied by the object with identifier `id`! Plan accordingly!
     */
    void RemoveUI(const     std::string &id);
    /**
     * @brief Add a new `GameObject` to the scene.
     * @param id Text associated with the inserted `_object`. This std::string will be the identifier of `_object`.
     * @param _ui The GameObject to add to the `Scene`.
     * @note Ownership of `_object` will be given to the `Scene` object for more centralized memory management.
     */
    void AddObject(const    std::string &id, GameObject *_object);
    /**
     * @brief Remove a `GameObject` element given it's identifier.
     * @param id Identifier of the element to remove.
     * @warning This will also free the memory occupied by the object with identifier `id`! Plan accordingly!
     */
    void RemoveObject(const std::string &id);

    /**
     * @brief Get a reference to the `GameObject` with identifier `id`.
     * @param id Desired object's identifier.
     * @return A @b non-constant reference to the `GameObject` stored with the identifier `id`.
     */
    GameObject        &GetObject(const std::string &id);
    /**
     * @brief Get a @b constant reference to the `GameObject` with identifier `id`.
     * @param id Desired object's identifier.
     * @return A @b constant reference to the `GameObject` stored with the identifier `id`.
     */
    const GameObject  &GetObject(const std::string &id) const;
    /**
     * @brief Get a reference to the `UIContainer` with identifier `id`.
     * @param id Desired object's identifier.
     * @return A @b non-constant reference to the `UIContainer` stored with the identifier `id`.
     */
    UIContainer       &GetUI(const     std::string &id);
    /**
     * @brief Get a @b constant reference to the `UIContainer` with identifier `id`.
     * @param id Desired object's identifier.
     * @return A @b constant reference to the `UIContainer` stored with the identifier `id`.
     */
    const UIContainer &GetUI(const     std::string &id) const;

    /**
     * @brief Draw all of the `Scene` object's elements following their `draw_order`.
     * @note All objects of type `UIContainer` are @b always drawn after all `GameObject` objects.
     */
    void Draw() const;
    /**
     * @brief Updates all of the `Scene` object's elements.
     */
    void Update();
};

/**
 * @brief ## SceneManager class
 * @brief A container for all `Scene` objects. Allows for the display of @b only @b one `Scene` object at a time.
 * @note Once given a pointer to a `Scene` object, this class becomes owner of said object and will liberate their memory on it's own.
 */
class SceneManager {
private:
    /**
     * @brief All `Scene` objects are stored here.
     */
    std::map<std::string, Scene*> scenes;
    /**
     * @brief A pointer to the currently active `Scene` object.
     */
    Scene       *activeScene;
public:
    /**
     * @brief Default constructor. Creates an empty `Scene` object and stores it with the identifier @b "scene_default". It then sets
     * said empty scene as `activeScene`.
     */
    SceneManager();
    /**
     * @brief Destructor. Automatically deletes all `Scene` objects stored in the container.
     * @warning The `SceneManager` becomes the owner of all the `Scene` objects stored in it, and will therefore clean the memory by itself.
     */
    ~SceneManager();

    /**
     * @brief Add a `Scene` object with an identifier `scene_id`.
     * @param scene_id Text associated with the inserted `Scene`. This std::string will be the identifier of `Scene`.
     * @param _scene The `Scene` object to insert.
     * @note Once inserted, ownership of the `Scene` object passes onto the `SceneManager` class. This means the user does
     * not need to manually delete every inserted object.
     */
    void   AddScene(const    std::string &scene_id, Scene *_scene);
    /**
     * @brief Remove a `Scene` object given it's `scene_id`.
     * @param scene_id Identifier of the `Scene` object to remove.
     * @warning Once removed from the `SceneManager` the object is also deleted! Plan accordingly!
     */
    void   RemoveScene(const std::string &scene_id);
    /**
     * @brief Set a `Scene` object given by `scene_id` to be loaded and drawn/updated.
     * @param scene_id Desired `Scene` object's identifier.
     */
    void   LoadScene(const   std::string &scene_id);
    /**
     * @brief Get a reference to the currently active `Scene` object.
     * @return a @b non-constant reference to the currently active `Scene` object.
     */
    Scene& GetActiveScene();
    /**
     * @brief Get a @b constant reference to the currently active `Scene` object.
     * @return a @b constant @b reference to the currently active `Scene` object.
     */
    const Scene& GetActiveScene() const;

    /**
     * @brief Calls the `Draw()` method of the currently active `Scene` object.
     */
    void Draw() const;
    /**
     * @brief Calls the `Update()` method of the currently active `Scene` object.
     */
    void Update();
};
#endif