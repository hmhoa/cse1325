#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "cart.h"

int main() {
    Cart cart{"Rice"};

    //read in new items from std::cin using item's operator>> until end of 
    std::cout << "Enter product names and price (e.g., \"English peas 0.79\"), press return again when done: " << std::endl;
    
    Item item{"", 0};
    
    while(std::cin >> item)
    {
        try{
            cart.add_item(item);
        }catch(std::exception& e){
            std::cerr << e.what() << std::endl;
        }
    }
    
    //output
    std::cout << "\nRegister Receipt\n" << std::endl; 
    //using iteration capability
    for(iterator i = cart.begin(); i!=cart.end(); ++i)
    {
        std::cout << **i << std::endl;
    }
    std::cout << std::string(20, '-') << std::endl;
    std::cout << std::setprecision(2) << std::fixed << "$\t" << cart.cost() << " Total Cost" << std::endl;
    
    return 0;
}
