#include <cmath>

class Piece {
public:
    Cell posit;

    Piece(const Cell &position_): position(position_) {}

    virtual bool available(const Cell &target) const = 0;
protected:
    void cooord(const Cell &target, int &x, int &y) const {
        x = target.h - posit.h;
        y = target.v - posit.v;
    }
};

class King: public Piece {
public:
    King(const Cell &position): Piece(position) {}

    bool available(const Cell &target) const {
        int x, y;
        cooord(target, x, y);
        return std::abs(x) <= 1 && std::abs(y) <= 1 && std::abs(x) + std::abs(y);
    }
};

bool rookCanMove(int x, int y) {
    return (x && !y) || (!x && y);
}

class Rook: public Piece {
public:
    Rook(const Cell &position): Piece(position) {}

    bool available(const Cell &target) const {
        int x, y;
        cooord(target, x, y);
        return rookCanMove(x, y);
    }
};

bool bishopCanMove(int x, int y) {
    return std::abs(x) == std::abs(y) && x;
}

class Bishop: public Piece {
public:
    Bishop(const Cell &position): Piece(position) {}

    bool available(const Cell &target) const {
        int x, y;
        cooord(target, x, y);
        return bishopCanMove(x, y);
    }
};

class Queen: public Piece {
public:
    Queen(const Cell &position): Piece(position) {}

    bool available(const Cell &target) const {
        int x, y;
        cooord(target, x, y);
        return rookCanMove(x, y) || bishopCanMove(x, y);
    }
};
