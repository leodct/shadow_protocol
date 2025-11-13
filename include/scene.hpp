#ifndef SCENE_H
#define SCENE_H

#include "globals.hxx"
#include "UI.hpp"
#include "gameObject.hxx"

class Scene {
private:
    std::map<std::string, UIContainer*> interfaces;
    std::map<std::string, GameObject*>  objects;
public:
    Scene();
    ~Scene();
    
    void AddUi(const        std::string &id, UIContainer *_ui);
    void RemoveUI(const     std::string &id);
    void AddObject(const    std::string &id, GameObject *_object);
    void RemoveObject(const std::string &id);
    void AddObjectList(std::map<std::string, GameObject*> _objects);

    GameObject        &GetObject(const std::string &id);
    const GameObject  &GetObject(const std::string &id) const;
    UIContainer       &GetUI(const     std::string &id);
    const UIContainer &GetUI(const     std::string &id) const;

    void Draw() const;
    void Update();
};

class SceneManager {
private:
    std::map<std::string, Scene*> scenes;
    static Scene emptyScene;
    Scene       *activeScene;
public:
    SceneManager();
    ~SceneManager();

    void   AddScene(const  std::string &scene_id, Scene *_scene);
    void   LoadScene(const std::string &scene_id);
    Scene& GetActiveScene();

    void Draw() const;
    void Update();
};
#endif