#ifndef PATH_HPP
#define PATH_HPP

#include <iostream>

class Path {
private:

    
public:
    char type;
    int id;
    int fromDirection;
    int toDirection;
    Path();
    Path(char type, int id, int fromDirection, int toDirection);
    Path(const Path& rhs);
    ~Path();

    int GetID() const;
    char GetType() const;
    int GetFromDirection() const;
    int GetToDirection() const;

    void PrintPath() const;
    

    
};

#endif