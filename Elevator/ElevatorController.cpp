#include "ElevatorController.h"

ElevatorController::ElevatorController(ElevatorMotor* InMotor)
    : State(Idle), WaitTimer(0), LastDirection(ElevatorDirection::Idle)
{
    Motor = InMotor;
}

void ElevatorController::SummonElevator(const int InFloor)
{
    SummonRequests.insert(InFloor);
}

void ElevatorController::SelectDestination(const int InFloor)
{
    DestinationRequests.insert(InFloor);
}

bool ElevatorController::AnyRequestedAbove(const int InFloor) const
{
    for (int i = InFloor + 1; i <= 9; i++)
    {
        if (SummonRequests.find(i) != SummonRequests.end() ||
            DestinationRequests.find(i) != DestinationRequests.end())
        {
            return true;
        }
    }

    return false;
}

bool ElevatorController::AnyRequestedBelow(const int InFloor) const
{
    for (int i = InFloor - 1; i >= 0; i--)
    {
        if (SummonRequests.find(i) != SummonRequests.end() ||
            DestinationRequests.find(i) != DestinationRequests.end())
        {
            return true;
        }
    }

    return false;
}

void ElevatorController::ProcessIdleState()
{
    const int CurrentFloor = Motor->GetCurrentFloor();

    if (SummonRequests.count(CurrentFloor) || DestinationRequests.count(CurrentFloor))
    {
        Motor->SetDirection(ElevatorDirection::Idle);
        State = Stopped;
        WaitTimer = 5;
        return;
    }

    if (AnyRequestedAbove(CurrentFloor))
    {
        Motor->SetDirection(ElevatorDirection::Up);
        State = Moving;
        LastDirection = ElevatorDirection::Up;
    }
    else if (AnyRequestedBelow(CurrentFloor))
    {
        Motor->SetDirection(ElevatorDirection::Down);
        State = Moving;
        LastDirection = ElevatorDirection::Down;
    }
}

void ElevatorController::ProcessMovingState()
{
    Motor->Step();
    const int NewFloor = Motor->GetCurrentFloor();

    if (SummonRequests.count(NewFloor) || DestinationRequests.count(NewFloor))
    {
        Motor->SetDirection(ElevatorDirection::Idle);
        State = Stopped;
        WaitTimer = 5;
    }
}

void ElevatorController::ProcessStoppedState()
{
    const int CurrentFloor = Motor->GetCurrentFloor();

    if (WaitTimer > 0)
    {
        WaitTimer--;
        return;
    }

    SummonRequests.erase(CurrentFloor);
    DestinationRequests.erase(CurrentFloor);

    if (LastDirection == ElevatorDirection::Up)
    {
        if (AnyRequestedAbove(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Up);
            State = Moving;
        }
        else if (AnyRequestedBelow(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Down);
            State = Moving;
            LastDirection = ElevatorDirection::Down;
        }
        else
        {
            Motor->SetDirection(ElevatorDirection::Idle);
            State = Idle;
        }
    }
    else if (LastDirection == ElevatorDirection::Down)
    {
        if (AnyRequestedBelow(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Down);
            State = Moving;
        }
        else if (AnyRequestedAbove(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Up);
            State = Moving;
            LastDirection = ElevatorDirection::Up;
        }
        else
        {
            Motor->SetDirection(ElevatorDirection::Idle);
            State = Idle;
        }
    }
    else
    {
        if (AnyRequestedAbove(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Up);
            State = Moving;
            LastDirection = ElevatorDirection::Up;
        }
        else if (AnyRequestedBelow(CurrentFloor))
        {
            Motor->SetDirection(ElevatorDirection::Down);
            State = Moving;
            LastDirection = ElevatorDirection::Down;
        }
        else
        {
            Motor->SetDirection(ElevatorDirection::Idle);
            State = Idle;
        }
    }
}

void ElevatorController::StepSimulation()
{
    switch (State)
    {
        case Idle:
            ProcessIdleState();
            break;
        case Moving:
            ProcessMovingState();
            break;
        case Stopped:
            ProcessStoppedState();
            break;
    }
}
