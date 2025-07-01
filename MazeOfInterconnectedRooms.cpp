#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>

class Room
{
public:
    std::string name;
    Room* north;
    Room* south;
    Room* east;
    Room* west;

    Room(std::string name)
        : name(std::move(name)), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}
};

void ConnectRooms(Room* ExistingRoom, Room* NewRoom, const std::string& Direction)
{
    if (Direction == "north")
    {
        ExistingRoom->north = NewRoom;
    }
    else if (Direction == "south")
    {
        ExistingRoom->south = NewRoom;
    }
    else if (Direction == "east")
    {
        ExistingRoom->east = NewRoom;
    }
    else if (Direction == "west")
    {
        ExistingRoom->west = NewRoom;
    }
}

bool PathExistsTo(Room* StartingRoom, const std::string& EndingRoomName)
{
    if (!StartingRoom) return false;

    std::queue<Room*> ToVisit;
    std::unordered_set<Room*> Visited;

    ToVisit.push(StartingRoom);
    Visited.insert(StartingRoom);

    while (!ToVisit.empty()) {
        Room* Current = ToVisit.front();
        ToVisit.pop();

        if (Current->name == EndingRoomName) {
            return true;
        }

        auto CheckAndEnqueue = [&](Room* Next) {
            if (Next && Visited.find(Next) == Visited.end()) {
                Visited.insert(Next);
                ToVisit.push(Next);
            }
        };

        CheckAndEnqueue(Current->north);
        CheckAndEnqueue(Current->south);
        CheckAndEnqueue(Current->east);
        CheckAndEnqueue(Current->west);
    }
    return false;
}

int main()
{
    Room* RoomA = new Room("A");
    Room* RoomB = new Room("B");
    Room* RoomC = new Room("C");
    Room* RoomD = new Room("D");
    Room* RoomE = new Room("E");

    ConnectRooms(RoomA, RoomB, "north");
    ConnectRooms(RoomB, RoomC, "east");
    ConnectRooms(RoomC, RoomD, "south");
    ConnectRooms(RoomD, RoomA, "west"); // Looping back
    ConnectRooms(RoomE, RoomE, "north"); // Self-connected room

    std::cout << "Testing PathExistsTo():\n";

    bool TestAD = PathExistsTo(RoomA, "D");
    std::cout << "Path from A to D: " << (TestAD ? "Exists" : "Does not exist") << " (Expected: Exists)\n";

    bool TestAE = PathExistsTo(RoomA, "E");
    std::cout << "Path from A to E: " << (TestAE ? "Exists" : "Does not exist") << " (Expected: Does not exist)\n";

    bool TestEE = PathExistsTo(RoomE, "E");
    std::cout << "Path from E to E: " << (TestEE ? "Exists" : "Does not exist") << " (Expected: Exists)\n";

    bool TestBA = PathExistsTo(RoomB, "A");
    std::cout << "Path from B to A: " << (TestBA ? "Exists" : "Does not exist") << " (Expected: Exists - because of cycle)\n";

    bool TestNonExistent = PathExistsTo(RoomA, "X");
    std::cout << "Path from A to X: " << (TestNonExistent ? "Exists" : "Does not exist") << " (Expected: Does not exist)\n";

    delete RoomA;
    delete RoomB;
    delete RoomC;
    delete RoomD;
    delete RoomE;

    std::cout << "\nPress any key to exit...";
    std::cin.get();

    return 0;
}
