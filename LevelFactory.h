#pragma once

#include <memory>
#include "Nivele.h"
#include "Menu.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "VictoryScreen.h"

inline std::unique_ptr<Nivele> createNextLevel(int currentLevelNumber) {
    switch (currentLevelNumber) {
        case -1: return std::make_unique<LevelOne>();
        case 1:  return std::make_unique<LevelTwo>();
        case 2:  return std::make_unique<VictoryScreen>();
        default: return std::make_unique<Menu>();
    }
}