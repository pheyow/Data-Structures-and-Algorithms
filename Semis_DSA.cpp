#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <set>
#include <limits>

using namespace std;

class Person {
public:
    string name;
    string ticketNumber;

    Person(string n, string t) : name(n), ticketNumber(t) {}
};

class Queue {
private:
    vector<Person> queueList;
    int ticketCounter;
    set<string> receivedTickets;

public:
    Queue() : ticketCounter(1) {}

    void enqueue(const string& name) {
        string ticketNum = formatTicketNumber(ticketCounter++);
        queueList.emplace_back(name, ticketNum);
        cout << name << " added to the queue with Ticket #" << ticketNum << endl;
    }

    void autoDequeue() {
        if (!queueList.empty()) {
            Person front = queueList.front();
            queueList.erase(queueList.begin());
            cout << "\nAfter 1 minute...\n";
            cout << "Dequeue: " << front.name << " received a ticket (Ticket #" << front.ticketNumber << ")" << endl;
            receivedTickets.insert(front.ticketNumber);
        } else {
            cout << "Queue is empty." << endl;
        }
    }

    bool isEmpty() {
        return queueList.empty();
    }

    int size() {
        return queueList.size();
    }

    string peek() {
        if (!queueList.empty()) {
            return queueList.front().name + " (Ticket #" + queueList.front().ticketNumber + ")";
        }
        return "No one in line.";
    }

    int position(const string& nameOrTicket) {
        for (int i = 0; i < queueList.size(); ++i) {
            if (queueList[i].name == nameOrTicket || queueList[i].ticketNumber == nameOrTicket) {
                return i + 1;
            }
        }
        return -1;
    }

    bool hasReceivedTicket(const string& nameOrTicket) {
        return receivedTickets.find(nameOrTicket) != receivedTickets.end();
    }

private:
    string formatTicketNumber(int num) {
        return (num < 10 ? "00" : (num < 100 ? "0" : "")) + to_string(num);
    }
};

int main() {
    Queue ticketQueue;
    int choice;
    bool menuDisplayed = false;

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!" << endl;

    auto lastDequeueTime = chrono::steady_clock::now();

    while (true) {
        auto currentTime = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::minutes>(currentTime - lastDequeueTime).count() >= 1) {
            ticketQueue.autoDequeue();
            lastDequeueTime = currentTime;
            cout << "Queue size: " << ticketQueue.size() << endl;
            cout << "Next in line: " << ticketQueue.peek() << endl;
        }

        if (!menuDisplayed) {
            cout << "\n\t1. Enqueue a person\n\t2. Check your position in the Queue\n\t3. Exit\n";
            menuDisplayed = true;
        }

        cout << "\nChoose an option: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                string name;
                cout << "Enter the name: ";
                getline(cin, name);
                ticketQueue.enqueue(name);
                cout << "Queue size: " << ticketQueue.size() << endl;
                break;
            }
            case 2: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string nameOrTicket;
                cout << "Enter your name or ticket number: ";
                getline(cin, nameOrTicket);

                if (ticketQueue.hasReceivedTicket(nameOrTicket)) {
                    cout << nameOrTicket << " has already received a ticket." << endl;
                } else {
                    int pos = ticketQueue.position(nameOrTicket);
                    if (pos != -1) {
                        cout << nameOrTicket << " is currently at position " << pos << " in the queue." << endl;
                    } else {
                        cout << nameOrTicket << " is not in the queue.\n" << endl;
                    }
                }
                break;
            }
            case 3: {
                cout << "Exiting the system. Thank you!" << endl;
                return 0;
            }
            default: {
                cout << "Invalid option. Please try again." << endl;
                break;
            }
        }

        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
