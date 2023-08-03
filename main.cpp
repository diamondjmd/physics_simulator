#include <iostream>
#include "World.h"
#include "black_box/Application.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Please, call with one argument "
                  << "( example: " << argv[0] << " <path to file smile.txt> )";
        return 1;
    }
    try {   
        World w(argv[1]);
        /**
         *  The code below starts the application execution. For
         *  To complete the job, there is no need to examine 
         *  or change the contents of the Application. 
         *  Better to focus on Ball.hpp, Ball.cpp and World.cpp first
         */
        Application app("physics");
        app.run(w);
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 2;
    }
    return 0;
}