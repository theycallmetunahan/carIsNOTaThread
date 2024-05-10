#include "path.hpp"

Path::Path() {
    
}   

Path::Path(char type, int id, int fromDirection, int toDirection) {
    this->type = type;
    this->id = id;
    this->fromDirection = fromDirection;
    this->toDirection = toDirection;
}

Path::Path(const Path& rhs) {
    this->type = rhs.type;
    this->id = rhs.id;
    this->fromDirection = rhs.fromDirection;
    this->toDirection = rhs.toDirection;
}

Path::~Path() {
    
}


int Path::GetID() const {
    return this->id;
}

char Path::GetType() const {
    return this->type;
}

int Path::GetFromDirection() const {
    return this->fromDirection;
}

int Path::GetToDirection() const {
    return this->toDirection;
}

void Path::PrintPath() const { // PathSegment 0: type=N, id=0, fromDirection=0, toDirection=1
    std::cout << "  PathSegment " << this->id << ": type=" << this->type << ", id=" << this->id << ", fromDirection=" << this->fromDirection << ", toDirection=" << this->toDirection << std::endl;
}

// Path: path.hpp
