#pragma once

#include "ElevatorControllerBase.h"
#include "ElevatorMotor.h"
#include <unordered_set>

class ElevatorController : public ElevatorControllerBase
{

public:
    explicit ElevatorController(ElevatorMotor* InMotor);

    void SummonElevator(int InFloor) override;
    void SelectDestination(int InFloor) override;
    void StepSimulation() override;

private:
    enum ControllerState
    {
        Idle,
        Moving,
        Stopped
    };

    ElevatorMotor* Motor;
    ControllerState State;
    int WaitTimer;
    ElevatorDirection LastDirection;

    std::unordered_set<int> SummonRequests;
    std::unordered_set<int> DestinationRequests;

    bool AnyRequestedAbove(int InFloor) const;
    bool AnyRequestedBelow(int InFloor) const;

    void ProcessIdleState();
    void ProcessMovingState();
    void ProcessStoppedState();
};
