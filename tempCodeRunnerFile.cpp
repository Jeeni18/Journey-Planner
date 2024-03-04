#include <iostream>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

class Journey {
private:
    const int numBusStops = 9;
    const double fareThreshold1 = 2.0;
    const double fareThreshold2 = 4.0;
    const double fare1 = 20.0;
    const double fare2 = 25.0;
    const double fare3 = 30.0;

    string busStops[9] = {"Baneshwor", "Koteshwor", "Jadibuti", "Gwarko", "Ekantakuna", "Balku", "Tripureshwor", "Thapathali", "Pulchowk"};
    double distances[9][9];
    bool seatAvailability[40];

public:
    Journey() {
        initializeGraph();
        initializeSeats();
    }

    int Choice() {
        int x;
        cout << "Please enter the number of your choice" << endl;
        cout << "1. List the bus stops" << endl;
        cout << "2. Find the shortest route between two places" << endl;
        cout << "3. Find the fare between two places" << endl;
        cout << "4. Book seats in the bus" << endl;
        cin >> x;
        return x;
    }

    void initializeSeats() {
        for (int i = 0; i < 40; ++i) {
            seatAvailability[i] = true;
        }
    }

    void listBusStops() {
        cout << "The bus stops are:" << endl;
        for (int i = 0; i < numBusStops; ++i) {
            cout << i + 1 << ". " << busStops[i] << endl;
        }
    }

    void initializeGraph() {
        // Initializing distances to -1 indicating no direct connection
        for (int i = 0; i < numBusStops; ++i) {
            for (int j = 0; j < numBusStops; ++j) {
                distances[i][j] = -1;
            }
        }

        // Setting distances for direct connections
        setDistance(0, 1, 2.0);
        setDistance(1, 2, 1.6);
        setDistance(1, 3, 2.1);
        setDistance(2, 3, 3.4);
        setDistance(3, 4, 3.3);
        setDistance(4, 5, 2.5);
        setDistance(5, 6, 2.5);
        setDistance(6, 7, 0.9);
        setDistance(7, 0, 2.0);
        setDistance(0, 8, 3.3);
        setDistance(1, 8, 4.1);
        setDistance(3, 8, 2.0);
        setDistance(4, 8, 1.6);
        setDistance(5, 8, 2.4);
        setDistance(7, 8, 2.0);
    }

    void setDistance(int source, int destination, double distance) {
        distances[source][destination] = distance;
        distances[destination][source] = distance; // Bidirectional edge
    }

    void findingPath() {
        listBusStops();
        cout << "Enter the source bus stop (1-9): ";
        int source, destination;
        cin >> source;
        cout << "Enter the destination bus stop (1-9): ";
        cin >> destination;

        if (source >= 1 && source <= numBusStops && destination >= 1 && destination <= numBusStops) {
            dijkstra(source - 1, destination - 1);
        } else {
            cout << "Invalid choice. Please choose a valid option." << endl;
        }
    }

    void dijkstra(int source, int destination) const {
        double distance[numBusStops];
        bool visited[numBusStops];
        int predecessor[numBusStops];

        for (int i = 0; i < numBusStops; ++i) {
            distance[i] = numeric_limits<double>::infinity();
            visited[i] = false;
            predecessor[i] = -1;
        }

        distance[source] = 0.0;

        for (int count = 0; count < numBusStops - 1; ++count) {
            int u = minDistance(distance, visited);
            visited[u] = true;

            for (int v = 0; v < numBusStops; ++v) {
                if (!visited[v] && distances[u][v] != -1 && distance[u] + distances[u][v] < distance[v]) {
                    distance[v] = distance[u] + distances[u][v];
                    predecessor[v] = u;
                }
            }
        }

        printShortestPath(source, destination, distance, predecessor);
    }

    int minDistance(const double distance[], const bool visited[]) const {
        double minDist = numeric_limits<double>::infinity();
        int minIndex = -1;

        for (int i = 0; i < numBusStops; ++i) {
            if (!visited[i] && distance[i] < minDist) {
                minDist = distance[i];
                minIndex = i;
            }
        }

        return minIndex;
    }

    void printShortestPath(int source, int destination, const double distance[], const int predecessor[]) const {
        cout << "Shortest path from " << busStops[source] << " to " << busStops[destination] << ":" << endl;
        cout << "Total Distance: " << fixed << setprecision(2) << distance[destination] << " km" << endl;

        // Print the actual path
        cout << "The shortest path it follows is: " << busStops[source];
        printPath(destination, source, predecessor);
        cout << endl;
    }

    void printPath(int current, int source, const int predecessor[]) const {
        if (current == source) {
            return;
        }

        printPath(predecessor[current], source, predecessor);
        cout << " -> " << busStops[current];
    }


void fare() {
    listBusStops();
    cout << "Enter the source bus stop (1-9): ";
    int source, destination;
    cin >> source;
    cout << "Enter the destination bus stop (1-9): ";
    cin >> destination;

    if (source >= 1 && source <= numBusStops && destination >= 1 && destination <= numBusStops) {
        double distance = distances[source - 1][destination - 1];
        calculateAndPrintFare(source - 1, destination - 1);
    } else {
        cout << "Invalid choice. Please choose a valid option." << endl;
    }
}

void calculateAndPrintFare(int source, int destination) const {
    double distance[numBusStops];
    bool visited[numBusStops];
    int predecessor[numBusStops];

    for (int i = 0; i < numBusStops; ++i) {
        distance[i] = numeric_limits<double>::infinity();
        visited[i] = false;
        predecessor[i] = -1;
    }

    distance[source] = 0.0;

    for (int count = 0; count < numBusStops - 1; ++count) {
        int u = minDistance(distance, visited);
        visited[u] = true;

        for (int v = 0; v < numBusStops; ++v) {
            if (!visited[v] && distances[u][v] != -1 && distance[u] + distances[u][v] < distance[v]) {
                distance[v] = distance[u] + distances[u][v];
                predecessor[v] = u;
            }
        }
    }

    cout << "Total Distance: " << fixed << setprecision(2) << distance[destination] << " km" << endl;

    double minDistance = distance[destination];

    if (minDistance <= fareThreshold1)
        cout << "Fare: Rs. " << fare1 << endl;
    else if (minDistance <= fareThreshold2)
        cout << "Fare: Rs. " << fare2 << endl;
    else
        cout << "Fare: Rs. " << fare3 << endl;
}



    void Book() {
        char moreSeatsChoice;
        do {
            cout << "\nEnter your Name: ";
            string name;
            cin >> name;

            cout << "Enter your Age: ";
            int age;
            cin >> age;

            cout << "Enter your Gender (M/F): ";
            char gender;
            cin >> gender;

            cout << "Enter your Phone Number: ";
            long long phoneNumber;
            cin >> phoneNumber;

            cout << "Enter the seat number you want to reserve (1-40): ";
            int seatNumber;
            cin >> seatNumber;

            int bookedSeat = reserveSeat(age, gender, seatNumber);
            if (bookedSeat != -1) {
                cout << "\nSeat booked successfully!\n";
                cout << "Name: " << name << ", Seat Number: " << bookedSeat << endl;
            }
            else
            {
                cout << "\nSorry, the specified seat is not available or doesn't match your criteria.\n";
            }

            cout << "Remaining available seats: " << countAvailableSeats() << endl;

            cout << "\nDo you want to book more seats?Type 'y' if yes: ";

            cin >> moreSeatsChoice;

            if (moreSeatsChoice == 'N' || moreSeatsChoice == 'n') {
                break;
            }

        } while (moreSeatsChoice == 'Y' || moreSeatsChoice == 'y');
    }



   int reserveSeat(int age, char gender, int seatNumber) {
    if (seatNumber < 1 || seatNumber > 40 || !seatAvailability[seatNumber - 1]) {
       // cout << "Please choose another seat." << endl;
        return -1;
    }

    int startSeat, endSeat;

    if (seatNumber == 1 || seatNumber == 2) {
        // Seats 1 and 2 are reserved for 60+ people
        if (age < 60) {
            cout << "\n~Seats 1 and 2 are reserved for people aged 60 and above~" ;
            return -1;
        }
        startSeat = 1;
        endSeat = 2;
    } else if (seatNumber == 3 || seatNumber == 4) {
        // Seats 3 and 4 are reserved for females
        if (!(gender == 'F' || gender == 'f')) {
            cout << "\n~Seats 3 and 4 are reserved for females~" ;
            return -1;
        }
        startSeat = 3;
        endSeat = 4;
    } else {
        // Other seats can be booked by anyone
        startSeat = 5;
        endSeat = 40;
    }

    if (seatNumber < startSeat || seatNumber > endSeat) {
       // cout << "Seat number " << startSeat << " to " << endSeat << " has specific criteria. Please choose another seat." << endl;
         //  cout<<"Please choose another seat"<<endl;
        return -1;
    }

    seatAvailability[seatNumber - 1] = false;
    return seatNumber; // Seat booked successfully
}


    int countAvailableSeats() const {
        int count = 0;
        for (int i = 0; i < 40; ++i) {
            if (seatAvailability[i]) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    Journey j;
    int x;
    char a;
    cout << "**WELCOME TO THE JOURNEY PLANNER**\n";
    do {
        x = j.Choice();
        switch (x) {
        case 1:
            j.listBusStops();
            cout << "\n------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 2:
            j.findingPath();
            cout << "\n------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 3:
            j.fare();
            cout << "\n------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 4:
            j.Book();
            cout << "\n------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        default:
            cout<<"\t\t\tINVALID INPUT"<<endl;
        }
        cout << "DO YOU WANT TO PERFORM MORE OPERATIONS?TYPE 'y' IF YES:";
        cin >> a;


    } while (a == 'Y' || a == 'y');
    cout << "\n**THANK YOU FOR USING OUR SERVICE**\n";
    return 0;
}
