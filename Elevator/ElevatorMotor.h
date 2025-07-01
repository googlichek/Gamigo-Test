#pragma once

enum class ElevatorDirection
{
    Idle,
    Up,
    Down
};

class ElevatorMotor
{

public:
    ElevatorMotor();

    int GetCurrentFloor() const { return CurrentFloor; }
    ElevatorDirection GetCurrentDirection() const {return Direction; }

    void SetDirection(ElevatorDirection InDirection);
    void Step();

private:
    int CurrentFloor;
    ElevatorDirection Direction;
};
