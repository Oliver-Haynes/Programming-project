#include <iostream>
#include <vector>
// git test
enum piece_colour { white, black };
enum piece_type { empty, pawn, knight, bishop, rook, queen, king };
struct piece {
  piece_type type;
  piece_colour colour;
  std::string icon;
  std::vector<int> direction;
};

piece createPawn(piece_colour colour) {
  piece init;
  init.type = pawn;
  init.colour = colour;
  init.icon = (colour == white) ? "♙" : "♟";
  init.direction = {1, -1};

  return init;
}

std::vector<piece> board(64, createPawn(white));

int main() { std::cout << board[40].type; }