#pragma once

#include "core/Factory.h"
#include "core/Singleton.h"
#include "raycer/primitives/Scene.h"

typedef Singleton<Factory<raycer::Scene>> SceneFactory;
