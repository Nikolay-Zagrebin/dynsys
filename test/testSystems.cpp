#include "gtest/gtest.h"
#include "Model/Model.hpp"
#include "DynamicSystems/DynamicSystem.hpp"

int countConvergesSystems(const Model::Point &startPoint, int requiredCount, long double tau) {
    int convergesCount = 0;

    int count = 0;
    auto counter = [&count](const Model::Point &) {
        ++count;
    };

    auto vectorSystems = DynamicSystems::getDefaultSystems<decltype(counter)>();

    for (auto &system : vectorSystems) {
        auto constantValues = system.getInterestingConstants();
        for (auto&[name, params] : constantValues) {
            count = 0;
            system.compute(counter, startPoint, requiredCount, tau, params);
            if (count == requiredCount) convergesCount++;
        }
    }
    return convergesCount;
}

TEST(model, allConstantRK4_1) {
    Model::Point startPoint = {0.1, 0.1, 0.1};
    int requiredCount = 100'000;
    long double tau = 0.01;

    EXPECT_GE(countConvergesSystems(startPoint, requiredCount, tau), 32);
}


TEST(model, allConstantRK4_2) {
    Model::Point startPoint = {0.01, 0.01, 0.01};
    int requiredCount = 500'000;
    long double tau = 0.01;

    EXPECT_GE(countConvergesSystems(startPoint, requiredCount, tau), 27);
}

TEST(model, allConstantRK4_3) {
    Model::Point startPoint = {0.01, 0.01, 0.01};
    int requiredCount = 200'000;
    long double tau = 0.0001;

    EXPECT_GE(countConvergesSystems(startPoint, requiredCount, tau), 37);
}

TEST(model, allConstantRK4_4) {
    Model::Point startPoint = {0.01, 0.01, 0.01};
    int requiredCount = 100'000;
    long double tau = 0.1;

    EXPECT_GE(countConvergesSystems(startPoint, requiredCount, tau), 19);
}