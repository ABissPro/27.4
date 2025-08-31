#include <iostream>
#include <vector>
#include <string>

class SimpleRandom {
private:
    unsigned int seed;

public:
    SimpleRandom(unsigned int s = 1) : seed(s) {}

    void setSeed(unsigned int s) {
        seed = s;
    }

    unsigned int generate(unsigned int max) {
        seed = (seed * 1103515245 + 12345) % 2147483648;
        return seed % max;
    }
};

class Worker {
private:
    std::string name;
    bool isBusy;
    char currentTask;

public:
    Worker(const std::string& n) : name(n), isBusy(false), currentTask('\0') {}

    void assignTask(char task) {
        currentTask = task;
        isBusy = true;
        std::cout << name << " is working on task " << task << std::endl;
    }

    bool getIsBusy() const {
        return isBusy;
    }

    std::string getName() const {
        return name;
    }
};

class MiddleManager {
private:
    std::string name;
    int managerId;
    std::vector<Worker> workers;
    SimpleRandom randomGenerator;

public:
    MiddleManager(const std::string& n, int id) : name(n), managerId(id), randomGenerator(id) {}

    void addWorker(const Worker& worker) {
        workers.push_back(worker);
    }

    void processCommand(int command) {
        std::cout << name << " received command: " << command << std::endl;
    
        unsigned int seed = command + managerId;
        randomGenerator.setSeed(seed);

        unsigned int tasksCount = randomGenerator.generate(workers.size()) + 1;
        std::cout << name << " generated " << tasksCount << " tasks for the team" << std::endl;

        std::vector<Worker*> availableWorkers;
        for (unsigned int i = 0; i < workers.size(); ++i) {
            if (!workers[i].getIsBusy()) {
                availableWorkers.push_back(&workers[i]);
            }
        }

        if (tasksCount > availableWorkers.size()) {
            tasksCount = availableWorkers.size();
        }

        for (unsigned int i = 0; i < tasksCount; ++i) {
            char taskType = 'A' + randomGenerator.generate(3);
            availableWorkers[i]->assignTask(taskType);
        }
    }

    bool isTeamBusy() const {
        for (unsigned int i = 0; i < workers.size(); ++i) {
            if (!workers[i].getIsBusy()) {
                return false;
            }
        }
        return true;
    }
};

class HeadOfCompany {
private:
    std::string name;
    std::vector<MiddleManager> managers;

public:
    HeadOfCompany(const std::string& n) : name(n) {}

    void addManager(const MiddleManager& manager) {
        managers.push_back(manager);
    }

    void processCommand(int command) {
        std::cout << name << " received strategic command: " << command << std::endl;

        for (unsigned int i = 0; i < managers.size(); ++i) {
            managers[i].processCommand(command);
        }
    }

    bool isCompanyBusy() const {
        for (unsigned int i = 0; i < managers.size(); ++i) {
            if (!managers[i].isTeamBusy()) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    int numTeams, workersPerTeam;

    std::cout << "Enter number of teams: ";
    std::cin >> numTeams;

    std::cout << "Enter number of workers per team: ";
    std::cin >> workersPerTeam;

    HeadOfCompany head("Company Head");

    for (int i = 0; i < numTeams; ++i) {
        std::string managerName = "Manager_" + std::to_string(i + 1);
        MiddleManager manager(managerName, i + 1);

        for (int j = 0; j < workersPerTeam; ++j) {
            std::string workerName = "Worker_" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
            manager.addWorker(Worker(workerName));
        }

        head.addManager(manager);
    }

    int command;
    while (!head.isCompanyBusy()) {
        std::cout << "\nEnter command (integer) or -1 to exit: ";
        std::cin >> command;

        if (command == -1) {
            break;
        }

        head.processCommand(command);
    }

    std::cout << "All workers are busy. Simulation completed." << std::endl;

    return 0;
}