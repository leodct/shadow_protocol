#include "scene.hpp"
#include <iostream>

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

void Scene::AddUi(const std::string &id, UIContainer *_ui)
{
    interfaces.emplace(id, _ui);
}

void Scene::RemoveUI(const std::string &id)
{
    delete interfaces[id];
    interfaces.erase(id);
}

void Scene::AddObject(const std::string &id, GameObject *_object)
{
    objects.emplace(id, _object);
}

void Scene::RemoveObject(const std::string &id)
{
    delete objects[id];
    objects.erase(id);
}

GameObject &Scene::GetObject(const std::string &id)
{
    auto it = objects.find(id);
    if (it != objects.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

const GameObject &Scene::GetObject(const std::string &id) const
{
    auto it = objects.find(id);
    if (it != objects.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

UIContainer &Scene::GetUI(const std::string &id)
{
    auto it = interfaces.find(id);
    if (it != interfaces.end())
        return *it->second;
    else
        ThrowNotFoundException(id);
}

const UIContainer &Scene::GetUI(const std::string &id) const
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

SceneManager::SceneManager()
{
    scenes.emplace("scene_default", new Scene());
    activeScene = scenes["scene_default"];
}

SceneManager::~SceneManager()
{
    for (auto &scene : scenes){
        delete scene.second;
    }
}

void SceneManager::AddScene(const std::string &scene_id, Scene *_scene)
{
    scenes.emplace(scene_id, _scene);
}

void SceneManager::RemoveScene(const std::string &scene_id)
{
    auto it = scenes.find(scene_id);
    if (it != scenes.end())
    {
        delete it->second;
        scenes.erase(it);
    }

}

void SceneManager::LoadScene(const std::string &scene_id)
{
    auto it = scenes.find(scene_id);
    if (it == scenes.end())
    {
        ThrowNotFoundException(scene_id);
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

const Scene &SceneManager::GetActiveScene() const
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
