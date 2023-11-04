// see for background
//  https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html

#include <iostream>
#include <iterator>
using namespace std;

// define separate containers for Color, Piece (enums recommended)

enum Color { White, Black, NONE};
enum Piece { King, Queen, Rook, Bishop, Knight, Pawn, Empty};

// a chessboard contains squares
class Square {
private:
  Color color;
  Piece piece;
  bool occupied;

public:
  Square() { // default, square unoccupied
    // fill out
    color = NONE;
    piece = Empty;
    occupied = false;
  }
  Square(Color c, Piece p) { // an occupied square
    // fill out
    color = c;
    piece = p;
    occupied = true;
  }
  int get(bool &o, Color &c, Piece &p) {
    // fill out
    c = color;
    p = piece;
    o = occupied;
    return 1;
  }

  //setters
  void setColor(Color c) {color = c;}
  void setOccupied(bool o) {occupied = o;}
  void setPiece(Piece p) {piece = p;}

  //getters
  Color getColor() {return color;}
  bool getOccupied() {return occupied;}
  Piece getPiece() {return piece;}

  //piece dies/ removed from board
  void Clear() {
    color = NONE;
    piece = Empty;
    occupied = false;
  }


  void print();
};

class ChessboardIterator;

class Chessboard {
  // make the container iterator friendly
  typedef ChessboardIterator iterator;

private:
  Square chessboard[8][8];

public:
  friend class ChessboardIterator;

  Chessboard() {} // Square does all the initialization

  // return an x,y square from chessboard
  Square square(int x, int y) {
    // fill out
    return chessboard[x][y];
  }

  ChessboardIterator begin();
  ChessboardIterator end();

  // place a piece on a x,y square in the chessboard
  int place(int x, int y, Color c, Piece p) {
    // fill out
    if (x < 0 || x > 7) {
      return -1;
    } else if (y < 0 || y > 7) {
      return -2;
    } else if (chessboard[x][y].getOccupied() == true) {
      return -3;
    } else if (c != Black && c != White) {
      return -4;
    } else if (p != Pawn && p != Rook && p != Queen && 
               p != King && p != Bishop && p != Knight) {
      return -5;
    }

    chessboard[x][y].setColor(c);
    chessboard[x][y].setPiece(p);
    chessboard[x][y].setOccupied(true);
    return 1;
  }

  int get(int x, int y, Color &c, Piece &p) {
    // fill out
    if (x < 0 || x > 7) {
      return -1;
    } else if (y < 0 || y > 7) {
      return -2;
    } else if (chessboard[x][y].getOccupied() == false) {
      return -3;
    }
    p = chessboard[x][y].getPiece();
    c = chessboard[x][y].getColor();
    return 1;
  }

  int movePawn(int fromX, int fromY, int toX, int toY, Color color) {
    // Check if the move is valid based on the pawn's color
    if (color == White) {
        // Move forward
        if (toY - fromY == 1 && fromX == toX) {
            return 1;  // Success
        }
        // Move two squares forward from the starting position
        else if (fromY == 1 && toY - fromY == 2 && fromX == toX) {
            return 1;  // Success
        }
        // Capture diagonally
        else if (toY - fromY == 1 && abs(fromX - toX) == 1) {
            return 1;  // Success
        }
    } else if (color == Black) {
        // Move forward
        if (fromY - toY == 1 && fromX == toX) {
            return 1;  // Success
        }
        // Move two squares forward from the starting position
        else if (fromY == 1 && fromY - toY == 2 && fromX == toX) {
            return 1;  // Success
        }
        // Capture diagonally
        else if (fromY - toY == 1 && abs(fromX - toX) == 1 && 
                  chessboard[toX][toY].getOccupied()) {
            return 1;  // Success
        }
    }

    return -7;  // Invalid move
}

  int moveRook(int fromX, int fromY, int toX, int toY) {
    // Attempt to move to the same cell
    if (fromX == toX && fromY == toY) {
        return -7;
    }
    // Collision detection
    if (fromX == toX) {
        // Horizontal move
        int dx = (fromY < toY) ? 1 : -1;

        for (int i = fromY + dx; i != toY; i += dx) {
            if (chessboard[fromX][i].getOccupied() == true) {
                return -7;
            }
        }
    } else if (fromY == toY) {
        // Vertical move
        int dy = (fromX < toX) ? 1 : -1;

        for (int i = fromX + dy; i != toX; i += dy) {
            if (chessboard[i][fromY].getOccupied() == true) {
                return -7;
            }
        }
    } else {
        // Not a valid rook move (neither horizontal nor vertical)
        return -7;
    }
    chessboard[toX][toY] = chessboard[fromX][fromY];
    chessboard[fromX][fromY].Clear();
    return 1;
  }

  int moveBishop (int fromX, int fromY, int toX, int toY) {
    // Check if bishop is moving diagonally
    if (abs(fromX - toX) != abs(fromY - toY)) {
        return -7;
    }

    // Determine direction of movement
    int xDirection = (toX - fromX) > 0 ? 1 : -1;
    int yDirection = (toY - fromY) > 0 ? 1 : -1;

    // Check if spaces between fromX/toX and fromY/toY are empty
    for (int i = 1; i < abs(fromX - toX); i++) {
        int x = fromX + i * xDirection;
        int y = fromY + i * yDirection;

        // Check if space is empty
        if (chessboard[x][y].getOccupied() == true) {
            return -7;
        }
    }
    chessboard[toX][toY] = chessboard[fromX][fromY];
    chessboard[fromX][fromY].Clear();
    return 1;
  }

  int moveQueen(int fromX, int fromY, int toX, int toY) {
    // Check if the move is valid for a queen
    if (fromX == toX || fromY == toY || abs(fromX - toX) == abs(fromY - toY)) {
        // Check if there are any pieces in the way
        int deltaX = (toX > fromX) ? 1 : ((toX < fromX) ? -1 : 0);
        int deltaY = (toY > fromY) ? 1 : ((toY < fromY) ? -1 : 0);
        int currentX = fromX + deltaX;
        int currentY = fromY + deltaY;

        while (currentX != toX || currentY != toY) {
            if (chessboard[currentX][currentY].getOccupied() == true) {
                // There is a piece in the way, so the move is not valid
                return -7;
            }

            currentX += deltaX;
            currentY += deltaY;
        }

        // Move the queen piece
        chessboard[toX][toY] = chessboard[fromX][fromY];
        chessboard[fromX][fromY].Clear();
        return 1;
    }
    else {
        // The move is not valid for a queen
        return -7;
    }
  }

  int moveKing(int fromX, int fromY, int toX, int toY) {
    // Check if the move is valid for a king
    if (abs(fromX - toX) <= 1 && abs(fromY - toY) <= 1) {
      // Move the king piece
      chessboard[toX][toY] = chessboard[fromX][fromY];
      chessboard[fromX][fromY].Clear();
      return 1;
    }

    // The move is not valid for a king
    return -7;
  }

  //used to move knight pieces to their designated positions
  int moveKnight(int fromX, int fromY, int toX, int toY) {
    // Check if the move is valid for a knight
    if ((abs(fromX - toX) == 2 && abs(fromY - toY) == 1) || 
      (abs(fromX - toX) == 1 && abs(fromY - toY) == 2)) {
        // Move the knight piece
        chessboard[toX][toY] = chessboard[fromX][fromY];
        chessboard[fromX][fromY].Clear();
        return 1;   
    }
    // The move is not valid for a knight
    return -7;
  }

  //function that controls all movement errors and movements
  int move(int fromX, int fromY, int toX, int toY) {
    //checks for invalid coordinates and checks to see if the specified piece to
    //be moved has a piece there to begin with also checks to see if the pieces 
    //are moving to the same colored position which is also illegal otherwise 
    //moves the piece accordingly
    if (fromX > 7 || fromX < 0) {return -1;}
    if (fromY > 7 || fromY < 0) {return -2;}
    if (toX > 7 || toX < 0) {return -3;}
    if (toY > 7 || toY < 0) {return -4;}
    if (chessboard[fromX][fromY].getOccupied() == false) {return -5;}
    if (chessboard[fromX][fromY].getColor() == chessboard[toX][toY].getColor()) {
      return -6;
    }
    if (chessboard[fromX][fromY].getPiece() == Pawn) {
      return movePawn(fromX, fromY, toX, toY, chessboard[fromX][fromY].getColor());
    } else if (chessboard[fromX][fromY].getPiece() == Rook) {
      return moveRook(fromX, fromY, toX, toY);
    } else if (chessboard[fromX][fromY].getPiece() == Bishop) {
      return moveBishop(fromX, fromY, toX, toY);
    } else if (chessboard[fromX][fromY].getPiece() == Queen) {
      return moveQueen(fromX, fromY, toX, toY);
    } else if (chessboard[fromX][fromY].getPiece() == King) {
      return moveKing(fromX, fromY, toX, toY);
    } else if (chessboard[fromX][fromY].getPiece() == Knight) {
      return moveKnight(fromX, fromY, toX, toY);
    }
    return -7;
  }

  void print();
};

class ChessboardIterator {
private:
  int position; // a number in [0..64]
  Chessboard chessboard;
//class to define iterator to print the chessboard
public:
  ChessboardIterator(Chessboard &board,
                     int pos) { // start out with an empty board
    //public variables
    position = pos;
    chessboard = board;
  }

  //gives x and y values given a position in the board
  void xy(int &x, int &y) { // break position down into x and y
    // fill out
    x = position % 8;
    y = 7 - position / 8;
  }

  // finds the square even an x and y value
  Square operator*() {
    // fill out
    int x,y;
    xy(x,y);
    return this->chessboard.chessboard[x][y];
  }

  // pre-increment
  ChessboardIterator &operator++() {
    position++;
    return *this;
  }

  //overloaded operator for != to use in for each loop to print board
  bool operator!=(const ChessboardIterator &a) {
    // fill out
    return this->position != a.position;
  }
};
