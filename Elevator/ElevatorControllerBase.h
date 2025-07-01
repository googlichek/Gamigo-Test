#pragma once

#include <string>

class ElevatorControllerBase
{

public:
    virtual ~ElevatorControllerBase() = default;

    // Pure virtual methods
    virtual void SummonElevator(int InFloor) = 0;
    virtual void SelectDestination(int InFloor) = 0;
    virtual void StepSimulation() = 0;
};
