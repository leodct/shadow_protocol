#include "gameObject.hxx"

GameObject::GameObject(Transform2D _transform) : transform(_transform)
{
}

GameObject::GameObject(Vector2 position)
{
    transform.position = position;
}

GameObject::GameObject(Vector2 position, float scale)
{
    transform.position = position;
    transform.scale    = scale;
}

Transform2D &GameObject::GetTransform()
{
    return transform;
}

const Transform2D &GameObject::GetTransform() const
{
    return transform;
}
