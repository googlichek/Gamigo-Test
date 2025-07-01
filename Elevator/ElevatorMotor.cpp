#include "ElevatorMotor.h"

ElevatorMotor::ElevatorMotor()
    : CurrentFloor(0), Direction(ElevatorDirection::Idle)
{
}

void ElevatorMotor::SetDirection(const ElevatorDirection InDirection)
{
    Direction = InDirection;
}

void ElevatorMotor::Step()
{
    if (Direction == ElevatorDirection::Up && CurrentFloor < 9)
    {
        CurrentFloor++;
    }
    else if (Direction == ElevatorDirection::Down && CurrentFloor > 0)
    {
        CurrentFloor--;
    }
}
