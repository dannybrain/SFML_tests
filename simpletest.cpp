#include <iostream>

class MaClass {
public:
    MaClass() { std::cout << "constructeur" << std::endl; 
                number = 10;
    }
    ~MaClass() { std::cout << "destructeur" << std::endl; }
    int getNumber() { return number; }

private:
    int number = 0;

};

int main(int argc, char** argv) {
    MaClass cool;
    std::cout << "hehe = " << cool.getNumber() << std::endl;

    exit(0);
}