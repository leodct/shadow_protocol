#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "transform.hxx"

class GameObject{
protected:
    Transform2D transform;
public:
    GameObject(Transform2D _transform = {});
    GameObject(Vector2 position);
    GameObject(Vector2 position, float scale);
    virtual ~GameObject() = default;

    const Transform2D &GetTransform() const;
    Transform2D       &GetTransform();

    virtual void Draw() const = 0;
    virtual void Update()     = 0;
};
#endif