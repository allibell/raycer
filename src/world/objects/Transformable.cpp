#include "world/objects/Transformable.h"
#include "world/objects/Material.h"
#include "raycer/primitives/Instance.h"
#include "raycer/primitives/Composite.h"

Transformable::Transformable(Element* parent)
  : Element(parent),
    m_scale(Vector3d::one())
{
}

Matrix4d Transformable::localTransform() const {
  return Matrix4d::translate(position()) *
         Matrix3d::rotate(rotation()) *
         Matrix3d::scale(scale());
}

Matrix4d Transformable::globalTransform() const {
  Matrix4d parentTransform;
  if (Transformable* p = dynamic_cast<Transformable*>(parent())) {
    parentTransform = p->globalTransform();
  }
  return parentTransform * localTransform();
}

void Transformable::setMatrix(const Matrix4d& matrix) {
  setPosition(matrix.translationVector());
  setRotation(Matrix3d(matrix).rotationVector());
  setScale(Matrix3d(matrix).scaleVector());
}

bool Transformable::canHaveChild(Element* child) const {
  return dynamic_cast<Transformable*>(child) != nullptr;
}

void Transformable::leaveParent() {
  if (isGenerated())
    return;
  
  setMatrix(globalTransform());
}

void Transformable::joinParent() {
  if (isGenerated())
    return;
  
  Matrix4d matrix;
  if (Transformable* p = dynamic_cast<Transformable*>(parent())) {
    matrix = p->globalTransform().inverted();
  }
  
  setMatrix(matrix * localTransform());
}

void Transformable::moveBy(const Vector3d& vector, bool global) {
  Vector3d offset;
  if (global) {
    offset = Matrix3d(globalTransform().inverted() * localTransform()) * vector;
  } else {
    offset = Matrix3d(localTransform()) * vector;
  }
  setPosition(position() + offset);
}

#include "Transformable.moc"
