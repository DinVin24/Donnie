#pragma once

#include <memory>

#include "HealthDisplay.h"
#include "Nivele.h"
#include "Menu.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "VictoryScreen.h"
#include "Instructiuni.h"
#include "GameOverScreen.h"

inline std::unique_ptr<Nivele> createNextLevel(int currentLevelNumber) {
    switch (currentLevelNumber) {
        case 0: return std::make_unique<GameOverScreen>();
        case -1: return std::make_unique<LevelOne>();
        case 1:  return std::make_unique<LevelTwo>();
        case 2:  return std::make_unique<VictoryScreen>();
        case 100: return std::make_unique<Instructiuni>();
        default: return std::make_unique<Menu>();
    }
}