#include <iostream>

void GivenTwoPoints() {
    double P1[2], P2[2]; //points
    double m, A, B, C; //values
    std::cout << "\nInput points" << std::endl;
    std::cout << "Enter first point, separated by space (x₁, y₁): ";
    std::cin >> P1[0] >> P1[1];
    std::cout << "Enter second point, separated by space (x₂, y₂): ";
    std::cin >> P2[0] >> P2[1];
    m = (P2[1] - P1[1]) / (P2[0] - P1[0]);
    A = m
}

void LineEquation() {
    int choice;
    std::cout << "\nEquation of a Line\nWhich specifically though?\n";
    std::cout << "1. Given two points";
    std::cout << "\nChoice: ";
    std::cin >> choice;
    if(choice == 1) {
        GivenTwoPoints();
    }
}

void menu() {
    int choice;
    std::cout << "Analytical Geometry Calculator!" << std::endl;
    std::cout << "1. Equation of a Line";
    std::cout << "\nChoice: ";
    std::cin >> choice;
    if(choice == 1) {
        LineEquation();
    }
}

int main() {
    menu();
}
