#include <iostream>
#include <string>
#include <cctype>

struct node {
    node *prev, *next;
    double value;
    int weight;
};

double vinput() {
    std::string buffer;
    int counter;
    double value;
    while(true) {
        counter = 0;
        std::cout << "Input value: ";
        std::getline(std::cin, buffer);
        if(buffer.length() == 0) {
            std::cout << "There isn't anything there lol\n";
            continue;
        }
        else {
            for(int i = 0;i < buffer.length();i++) {
                if(isalpha(buffer[i])) counter++;
                else if(ispunct(buffer[i]) && buffer[i] != '-') counter++;
            }
            if(counter > 0) {
                std::cout << counter << " invalid tokens found, try again\n";
                continue;
            }
            else {
                value = std::stod(buffer);
                return value;
            }
        }
    }
}

int winput() {
    std::string buffer;
    int counter, weight;
    while(true) {
        counter = 0;
        std::cout << "Input weight: ";
        std::getline(std::cin, buffer);
        if(buffer.length() == 0) {
            std::cout << "There isn't anything there lol\n";
            continue;
        }
        else {
            for(int i = 0;i < buffer.length();i++) {
                if(isalpha(buffer[i])) counter++;
                else if(ispunct(buffer[i])) counter++;
            }
            if(counter > 0) {
                std::cout << counter << " invalid tokens found, try again\n";
                continue;
            }
            else {
                weight = std::stoi(buffer);
                return weight;
            }
        }
    }
}

int main() {
    std::cout << "Weighted Stats calc\n\n";
    node *head, *current, *temp;
    head = new node;
    head->prev = nullptr;
    current = head;
    while(true) {
        current->value = vinput();
        current->weight = winput();
        temp = new node;
        temp->prev = current;
        current->next = temp;
        current = temp;
    }
}
