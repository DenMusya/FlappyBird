#pragma once
#include <numbers>
#include <string>

#include "../graphics/Color.h"
#include "Utils.h"

struct BirdConfig {
  Vector2 size = Vector2{64.0f, 64.0f};
  Vector2 beginPosition = Vector2{SCREEN_WIDTH, SCREEN_HEIGHT} * 0.5f;

  float gravity = 750.0f;
  float jumpForce = 350.0f;
  float terminalVelocity = 500.0f;

  float rotateSpeed = 0.02f;
  float terminalTopAngle = ToRadians(45);
  float terminalDownAngle = -ToRadians(15);

  float colliderRadiusX = 21.0f;
  float colliderRadiusY = 13.5f;

  float scale = 1.5f;

  float deadRotationSpeed = 8.0f;

  std::string baseSpritePath = "Resources/Bird.png";
  std::string deadSpritePath = "Resources/DeadBird.png";
};

struct PipeConfig {
  Vector2 size = Vector2{100.0f, 600.0f};
  float speed = 300.0f;

  float distanceBetweenPipes = 200.0f;

  std::string spritePath = "Resources/Pipe.png";
};

struct PipeSpawnerConfig {
  float timeToNewPipe = 2.0f;
  float randomLowerBound = -300.0f;
  float randomUpperBound = 300.0f;
};

struct TextConfig {
  Vector2 pos;
  float scale = 3.0f;
  Color color = Color::Black;

  Vector2u symbolSize = Vector2u{5, 7};
};

struct BackgroundConfig {
  float speed = 80.0f;
  uint32_t spriteDuplicates = 4u;
  std::string spritePath = "Resources/bg2.png";
};

struct FeatherConfig {
  Vector2 size = Vector2{7, 7};
  float gravity = 50.0f;
  std::string spritePath = "Resources/feather";
  Vector2 pos;
  float scale = 2;
  Vector2 velocity;
  float rotation;
  float rotationSpeed;
  float lifeDuration;
};

struct FeatherSpawnerConfig {
  uint32_t countFeathers = 30;
  uint32_t countSprites = 4;

  Vector2 velXBounds = Vector2{-150, 150};
  Vector2 velYBounds = Vector2{-150, -50};

  Vector2 rotBounds = Vector2{0, 2 * std::numbers::pi};
  Vector2 rotSpeedBounds = Vector2{-2, 2};
  Vector2 lifeBounds = Vector2{0.5, 1.5};
};

struct Config {
  // TextConfig scoreConfig;
  // TextConfig fpsConfig;
  BirdConfig bird;
  PipeConfig pipe;
  PipeSpawnerConfig pipeSpawner;
  BackgroundConfig background;
  FeatherConfig feather;
  FeatherSpawnerConfig featherSpawner;
  TextConfig text;
};

extern Config g_config;