// chessboard.cpp

#include "chessboard.h"

// define containers for color mappings (2 colors) and piece mappings (6 pieces)

string charColorGrabber (Color color) {
  switch(color)
    {
      case Color::Black:
        return "b";
      case Color::White:
        return "w";
      case Color::NONE:
        return " ";
    }
  return "error";
}

string charPieceGrabber (Piece piece) {
  switch(piece)
    {
      case Piece::Pawn:
        return "P ";
      case Piece::Rook:
        return "R ";
      case Piece::Queen:
        return "Q ";
      case Piece::King:
        return "K ";
      case Piece::Knight:
        return "N ";
      case Piece::Bishop:
        return "B ";
      case Piece::Empty:
        return ". ";
    }
  return "error";
}
 
ChessboardIterator Chessboard::begin() {
  return ChessboardIterator(*this, 0); // Start at position 0 (top-left corner)
}

ChessboardIterator Chessboard::end() {
  return ChessboardIterator(*this, 64); // End at position 64 (one past the last square)
}

// print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
  int count = 0;
  for (ChessboardIterator it = begin(); it != end(); ++it) {
    Square square = *it; // Get the value of the current square
    // Print the square value or perform any other desired action
    cout << charColorGrabber(square.getColor()) <<
      charPieceGrabber(square.getPiece());
    count++;
    if ((count % 8) == 0) {
      cout << endl;
    }
    
  }
}


