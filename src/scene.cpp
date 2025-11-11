#include "scene.hpp"
#include <iostream>

[[noreturn]] void ThrowNotFoundException(std::string &id){
    throw std::out_of_range("Error. Object with id " + id + " not found in scene. Terminating abnormally...");
}

Scene::Scene()
{
}

Scene::~Scene()
{
    for (auto &ui : interfaces)
    {
        delete ui.second;
    }
    for (auto &obj : objects)
    {
        delete obj.second;
    }
}

void Scene::AddUi(std::string id, UIContainer *_ui)
{
    interfaces.emplace(id, _ui);
}

void Scene::RemoveUI(std::string id)
{
    delete interfaces[id];
    interfaces.erase(id);
}

void Scene::AddObject(std::string id, GameObject *_object)
{
    objects.emplace(id, _object);
}

void Scene::RemoveObject(std::string id)
{
    delete objects[id];
    objects.erase(id);
}

void Scene::AddObjectList(std::map<std::string, GameObject *> _objects)
{
    objects.merge(_objects);
}

GameObject &Scene::GetObject(std::string &id)
{
    auto it = objects.find(id);
    if (it != objects.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

const GameObject &Scene::GetObject(std::string &id) const
{
    auto it = objects.find(id);
    if (it != objects.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

UIContainer &Scene::GetUI(std::string &id)
{
    auto it = interfaces.find(id);
    if (it != interfaces.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

const UIContainer &Scene::GetUI(std::string &id) const
{
    auto it = interfaces.find(id);
    if (it != interfaces.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

void Scene::Draw() const
{
    BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);
            for (auto &obj : objects)
            {
                obj.second->Draw();
            }
        EndMode2D();
        for (int i = MIN_DRAW_ORDER; i <= MAX_DRAW_ORDER; i++)
        {
            for (auto &ui : interfaces)
            {
                if (ui.second->GetDrawOrder() == i)
                {
                    ui.second->Draw();
                }
            }
        }
    EndDrawing();
}

void Scene::Update()
{
    for (auto &obj : objects)
    {
        obj.second->Update();
    }
    for (auto &ui : interfaces)
    {
        ui.second->Update();
    }
}


// =================================
// === SCENE MANAGER SHENANIGANS ===
// =================================
Scene SceneManager::emptyScene = Scene();

SceneManager::SceneManager() : activeScene(&emptyScene)
{
}

SceneManager::~SceneManager()
{
    for (auto &scene : scenes){
        delete scene.second;
    }
}

void SceneManager::AddScene(std::string scene_id, Scene *_scene)
{
    scenes.emplace(scene_id, _scene);
}

void SceneManager::LoadScene(std::string scene_id)
{
    auto it = scenes.find(scene_id);
    if (it == scenes.end())
    {
        activeScene = &emptyScene;
        std::cerr << "Error! Empty scene loaded!" << std::endl;
    }
    else
    {
        activeScene = it->second;
    }
}

Scene &SceneManager::GetActiveScene()
{
    return *activeScene;
}

void SceneManager::Draw() const
{
    activeScene->Draw();
}

void SceneManager::Update()
{
    activeScene->Update();
}
