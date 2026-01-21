#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

#define CLEAR_COMMAND "cls"

// ANSI color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;

// Declaration of classes and functions used in the program
class QuoteGenerator {
private:
    vector<string> forstorequotes;

public:
    QuoteGenerator() {
        // Initialize quotes
        forstorequotes = {
            "I'm king of the world! - Titanic",
            "There's no place like home. - The Wizard of Oz",
            "You're gonna need a bigger boat. - Jaws",
            "Here's Johnny! - The Shining",
            "Frankly, my dear, I don't give a damn. - Gone with the Wind",
            "You shall not pass! - The Lord of the Rings: The Fellowship of the Ring",
            "Hasta la vista, baby. - Terminator 2: Judgment Day",
            "Why so serious? - The Dark Knight",
            "Just keep swimming. - Finding Nemo",
            "I am Groot. - Guardians of the Galaxy",
            "May the Force be with you. - Star Wars",
            "Here's looking at you, kid. - Casablanca",
            "You can't handle the truth! - A Few Good Men",
            "I'll be back. - The Terminator",
            "My precious. - The Lord of the Rings: The Two Towers",
            "Life is like a box of chocolates; you never know what you're gonna get. - Forrest Gump",
            "To infinity and beyond! - Toy Story",
            "You talking to me? - Taxi Driver",
            "Bond. James Bond. - Various James Bond films",
            "Houston, we have a problem. - Apollo 13",
        };
    }

    string forRandomQuote() {
        // Generate a random index
        int x = rand() % forstorequotes.size();

        // Return the random quote
        return forstorequotes[x];
    }
};


struct Task {
    string name;
    time_t time;
};

class ToDo {
private:
    vector<Task> tasks;
    const string filename = "tasks.txt";

public:
    void foraddt(const string& name, const tm& time) {
        tm time_copy = time;
        time_t Time1 = mktime(&time_copy);
        tasks.push_back({name, Time1});
        saveTasks(); // Auto-save after adding
        cout << GREEN << "Task added and saved successfully!" << RESET << endl;
    }

    void displayt() {
        system(CLEAR_COMMAND); // Clear screen
        cout << CYAN << "=============== TASKS ===============" << RESET << endl;
        if (tasks.empty()) {
            cout << YELLOW << "No tasks found. Add some tasks to get started!" << RESET << endl;
        } else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << "  " << GREEN << i + 1 << "." << RESET << " " << tasks[i].name << endl;
                cout << "     Due: " << BLUE << formatTime(tasks[i].time) << RESET << endl;
            }
        }
        cout << CYAN << "====================================" << RESET << endl;
    }

    void removet(int remove_task) {
        if (remove_task >= 0 && remove_task < tasks.size()) {
            tasks.erase(tasks.begin() + remove_task);
            saveTasks(); // Auto-save after removing
            cout << GREEN << "Task removed and saved successfully!" << RESET << endl;
        } else {
            cout << RED << "Invalid task number!" << RESET << endl;
        }
    }

    void saveTasks() {
        ofstream file(filename);
        if (!file) {
            cout << RED << "Error: Unable to save tasks!" << RESET << endl;
            return;
        }
        
        for (const auto& task : tasks) {
            // Save task name and time_t value
            file << task.name << endl;
            file << task.time << endl;
        }
        
        file.close();
    }

    void loadTasks() {
        ifstream file(filename);
        if (!file) {
            // File doesn't exist yet, no tasks to load
            return;
        }
        
        tasks.clear();
        string name;
        time_t taskTime;
        
        while (getline(file, name)) {
            if (file >> taskTime) {
                file.ignore(); // Ignore newline after reading time_t
                tasks.push_back({name, taskTime});
            }
        }
        
        file.close();
        if (!tasks.empty()) {
            cout << GREEN << "Loaded " << tasks.size() << " task(s) from file." << RESET << endl;
        }
    }

    string formatTime(time_t t) {
        tm* timeinfo = localtime(&t);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", timeinfo);
        return string(buffer);
    }

    bool hasTasks() const {
        return !tasks.empty();
    }
};

tm current_time() {
    time_t current_time = time(nullptr);
    return *localtime(&current_time);
}

tm get_task() {
    int choice;
    tm Time;
    cout << "\nEnter task due date and time:\n";
    cout << "  1. Enter specific date and time\n";
    cout << "  2. Use current date and time\n";
    cout << "\nEnter your choice : ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEnter task due date and time (YYYY-MM-DD HH:MM): ";
        cin >> get_time(&Time, "%Y-%m-%d %H:%M");

    } else if (choice == 2) {
        Time = current_time();
    } else {
        cout << "\nInvalid choice. Using current Date and Time by default.\n";
        Time = current_time();
    }

    return Time;
}

int main() {

    QuoteGenerator obj1;
    ToDo obj2;
    int choice;

    // Seed the random number generator
    srand(time(nullptr));

    // Load saved tasks from file
    cout << CYAN << "Loading tasks..." << RESET << endl;
    obj2.loadTasks();
    cout << endl;

    do {
        system(CLEAR_COMMAND); // Clear screen

        cout << CYAN << " __________________________________ "<< RESET << endl;
        cout << CYAN << "|                                  |"<< RESET << endl;
        cout << CYAN << "|              Menu                |"<< RESET << endl;
        cout << CYAN << "|__________________________________|"<< RESET << endl;
        cout << CYAN << "|                                  |"<< RESET << endl;
        cout << CYAN << "| 1. To-Do List                    |"<< RESET << endl;
        cout << CYAN << "| 2. Random Quote Generator        |"<< RESET << endl;
        cout << CYAN << "| 3. Exit                          |"<< RESET << endl;
        cout << CYAN << "|__________________________________|"<< RESET << endl;

        cout << "\nEnter your choice : ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int select;
                do {
                    system(CLEAR_COMMAND); // Clear screen

                    cout << BLUE << " __________________________________ "<< RESET << endl;
                    cout << BLUE << "|                                  |"<< RESET << endl;
                    cout << BLUE << "|          To-Do List Menu         |"<< RESET << endl;
                    cout << BLUE << "|__________________________________|"<< RESET << endl;
                    cout << BLUE << "|                                  |"<< RESET << endl;
                    cout << BLUE << "| 1. Add Task                      |"<< RESET << endl;
                    cout << BLUE << "| 2. Display Tasks                 |"<< RESET << endl;
                    cout << BLUE << "| 3. Remove Task                   |"<< RESET << endl;
                    cout << BLUE << "| 4. Back to Main Menu             |"<< RESET << endl;
                    cout << BLUE << "|__________________________________|"<< RESET << endl;

                    cout << "\nEnter your choice : ";
                    cin >> select;

                    switch (select) {
                        case 1: {
                            string task_name;
                            tm task_time = get_task();
                            cout << "\nEnter Task : ";
                            cin.ignore();
                            getline(cin, task_name);
                            obj2.foraddt(task_name, task_time);
                            obj2.displayt();
                            break;
                        }
                        case 2:
                            obj2.displayt();
                            break;
                        case 3: {
                            if (!obj2.hasTasks()) {
                                cout << YELLOW << "\nNo tasks to remove!" << RESET << endl;
                                break;
                            }
                            obj2.displayt();
                            int remove_task;
                            cout << "\nEnter index of task to remove : ";
                            cin >> remove_task;
                            obj2.removet(remove_task - 1); // Adjust index to match vector indexing
                            obj2.displayt();         // Clear and display tasks after removing
                            break;
                        }
                        case 4:
                            break; // Exit to main menu
                        default:
                            cout << "\nInvalid choice. Please try again.\n";
                    }

                    if (select != 4) {
                        cout << "\nPress Enter to continue...";
                        cin.ignore(); // Wait for Enter key
                        cin.get();
                    }
                } while (select != 4);
                break;
            }
            case 2: {
                system(CLEAR_COMMAND); // Clear screen

                cout << "\nRandom Quote :  " << endl;
                cout << obj1.forRandomQuote() << endl;

                cout << "\nPress Enter to continue...";
                cin.ignore(); // Wait for Enter key
                cin.get();
                break;
            }

            case 3:
                cout << GREEN << "\nAll tasks saved. Exiting...\n" << RESET;
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

