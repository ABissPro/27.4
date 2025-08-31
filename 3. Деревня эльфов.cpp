#include <iostream>
#include <vector>
#include <string>

class Branch {
private:
    Branch* parent;
    std::vector<Branch*> children;
    std::string elfName;

public:
    Branch(Branch* p = nullptr) : parent(p) {}

    void addChild() {
        children.push_back(new Branch(this));
    }

    int getChildCount() const {
        return children.size();
    }

    Branch* getChild(int index) {
        if (index >= 0 && index < static_cast<int>(children.size())) {
            return children[index];
        }
        return nullptr;
    }

    void setElfName(const std::string& name) {
        elfName = name;
    }

    std::string getElfName() const {
        return elfName;
    }

    Branch* getParent() const {
        return parent;
    }

    Branch* findElf(const std::string& name) {
        if (elfName == name) {
            return this;
        }

        for (Branch* child : children) {
            Branch* result = child->findElf(name);
            if (result != nullptr) {
                return result;
            }
        }

        return nullptr;
    }

    Branch* getTopBranch() {
        if (parent == nullptr) return nullptr; // Это дерево
        if (parent->parent == nullptr) return this; // Это большая ветвь
        return parent->getTopBranch(); // Это средняя ветвь
    }

    int countElvesOnBranch() {
        int count = 0;
        if (!elfName.empty() && elfName != "None") {
            count++;
        }

        for (Branch* child : children) {
            count += child->countElvesOnBranch();
        }

        return count;
    }
};

int randomInt(int min, int max) {
    static unsigned int seed = 1;
    seed = (seed * 1103515245 + 12345) % 2147483648;
    return min + (seed % (max - min + 1));
}

int main() {
    std::vector<Branch*> trees;

    for (int i = 0; i < 5; i++) {
        trees.push_back(new Branch());

        int largeBranches = randomInt(3, 5);
        for (int j = 0; j < largeBranches; j++) {
            trees[i]->addChild();

            int mediumBranches = randomInt(2, 3);
            for (int k = 0; k < mediumBranches; k++) {
                trees[i]->getChild(j)->addChild();
            }
        }
    }

    std::cout << "Add elf in village:" << std::endl;
    for (Branch* tree : trees) {
        for (int i = 0; i < tree->getChildCount(); i++) {
            Branch* largeBranch = tree->getChild(i);

            std::cout << "Enter name of elf for great branch (or 'None'): ";
            std::string name;
            std::cin >> name;
            largeBranch->setElfName(name);

            for (int j = 0; j < largeBranch->getChildCount(); j++) {
                std::cout << "Enter name of elf for middle branch (or 'None'): ";
                std::cin >> name;
                largeBranch->getChild(j)->setElfName(name);
            }
        }
    }

    std::string elfName;
    std::cout << "Enter name of elf for search: ";
    std::cin >> elfName;

    Branch* foundElf = nullptr;
    for (Branch* tree : trees) {
        foundElf = tree->findElf(elfName);
        if (foundElf != nullptr) {
            break;
        }
    }

    if (foundElf == nullptr) {
        std::cout << "Elf '" << elfName << "' not found." << std::endl;
    }
    else {
        Branch* topBranch = foundElf->getTopBranch();
        if (topBranch == nullptr) {
            std::cout << "Error: cannot find great brench." << std::endl;
        }
        else {
            int totalElves = topBranch->countElvesOnBranch();
            int neighbors = totalElves - 1;

            std::cout << "Elf '" << elfName << "' have " << neighbors << " neighbours." << std::endl;
        }
    }

    for (Branch* tree : trees) {
        delete tree;
    }

    return 0;
}