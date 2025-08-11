#pragma once
#include "../graphics/Color.h"
#include "Utils.h"

struct BirdConfig {
  Vector2 size;
  Vector2 beginPosition;

  float gravity;
  float jumpForce;
  float terminalVelocity;

  float rotateSpeed;
  float terminalTopAngle;
  float terminalDownAngle;

  float colliderRadiusX;
  float colliderRadiusY;

  float scale;
};

struct PipeConfig {
  Vector2 size;
  float speed;

  float distanceBetweenPipes;
};

struct PipeSpawnerConfig {
  float timeToNewPipe;
  float randomLowerBound;
  float randomUpperBound;
};

struct TextConfig {
  Vector2 pos;
  float scale;
  Color color;

  Vector2u symbolSize;
};

struct Config {
  BirdConfig bird;
  PipeConfig pipe;
  PipeSpawnerConfig pipeSpawner;
  TextConfig scoreConfig;
};

extern Config g_config;