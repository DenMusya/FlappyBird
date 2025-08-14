#include "FeatherSpawner.h"

#include "../utils/Config.h"
#include "../utils/Utils.h"
#include "Feather.h"
#include "GameObject.h"

void FeatherSpawner::SpawnFeathers(Vector2 pos) {
  Vector2 birdSize = g_config.bird.size * g_config.bird.scale;

  for (uint32_t i = 0; i < g_config.featherSpawner.countFeathers; ++i) {
    FeatherConfig newFeathConf = g_config.feather;

    newFeathConf.pos.x = RandomFloat(pos.x, pos.x + birdSize.x);
    newFeathConf.pos.y = RandomFloat(pos.y, pos.y + birdSize.y);

    newFeathConf.velocity.x = RandomFloat(g_config.featherSpawner.velXBounds.x,
                                          g_config.featherSpawner.velXBounds.y);
    newFeathConf.velocity.y = RandomFloat(g_config.featherSpawner.velYBounds.x,
                                          g_config.featherSpawner.velYBounds.y);

    newFeathConf.rotation = RandomFloat(g_config.featherSpawner.rotBounds.x,
                                        g_config.featherSpawner.rotBounds.y);

    newFeathConf.rotationSpeed =
        RandomFloat(g_config.featherSpawner.rotSpeedBounds.x,
                    g_config.featherSpawner.rotSpeedBounds.y);

    newFeathConf.lifeDuration =
        RandomFloat(g_config.featherSpawner.lifeBounds.x,
                    g_config.featherSpawner.lifeBounds.y);

    newFeathConf.spritePath +=
        std::to_string(i % g_config.featherSpawner.countSprites + 1) + ".png";

    _feathers.push_back(GameObject::Create<Feather>(newFeathConf));
  }
}

void FeatherSpawner::ClearFeathers() { _feathers.clear(); }

std::span<std::shared_ptr<Feather>> FeatherSpawner::GetFeathers() {
  return _feathers;
}