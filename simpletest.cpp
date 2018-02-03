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


    std::pair<int,int> mytuple(10, 20);

    std::cout << std::get<0>(mytuple) << std::endl;

    exit(0);
}