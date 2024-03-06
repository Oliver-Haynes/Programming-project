#include <iostream>
#include <vector>

enum piece_colour { white, black };
enum piece_type { empty, pawn, knight, bishop, rook, queen, king };
struct move {
  int startSquare;
  int targetSquare;
};
struct piece { // provides a template for the pieces
  piece_type type;
  piece_colour colour;
  std::string icon;
  std::vector<int> direction;
};
// defines pieces,the board and game properties
piece createEmpty() {
  piece init;
  init.type = empty;
  init.icon = "•";
  return init;
}
piece createPawn(piece_colour colour) {
  piece init;
  init.type = pawn;
  init.colour = colour;
  init.icon = (colour == white) ? "♙" : "♟";
  init.direction = {8, -8};
  return init;
}
piece createKnight(piece_colour colour) {
  piece init;
  init.type = knight;
  init.colour = colour;
  init.icon = (colour == white) ? "♘" : "♞";
  init.direction = {10, -10, 15, -15, 6, -6, 17, -17};
  return init;
}
piece createBishop(piece_colour colour) {
  piece init;
  init.type = bishop;
  init.colour = colour;
  init.icon = (colour == white) ? "♗" : "♝";
  init.direction = {9, -9, 7, -7};

  return init;
}
piece createRook(piece_colour colour) {
  piece init;
  init.type = rook;
  init.colour = colour;
  init.icon = (colour == white) ? "♖" : "♜";
  init.direction = {8, -8, 1, -1};

  return init;
}
piece createQueen(piece_colour colour) {
  piece init;
  init.type = queen;
  init.colour = colour;
  init.icon = (colour == white) ? "♕" : "♛";
  init.direction = {9, -9, 7, -7, 8, -8, 1, -1};

  return init;
}
piece createKing(piece_colour colour) {
  piece init;
  init.type = king;
  init.colour = colour;
  init.icon = (colour == white) ? "♔" : "♚";
  init.direction = {9, -9, 7, -7, 8, -8, 1, -1};

  return init;
}
std::vector<piece> board(64, createEmpty());
piece_colour turn = white;

void parseFen(std::string fen) {
  int j = 0;
  for (int i = 0; i < fen.length(); i++) {
    if (isdigit(fen[i])) {
      j = j + stoi(std::string(1, fen[i]));
      continue;
    }
    if (fen[i] == '/') {
      continue;
    }
    switch (tolower(fen[i])) {
    case 'p':
      board[j] = createPawn(isupper(fen[i]) ? white : black);
      break;
    case 'n':
      board[j] = createKnight(isupper(fen[i]) ? white : black);
      break;
    case 'b':
      board[j] = createBishop(isupper(fen[i]) ? white : black);
      break;
    case 'r':
      board[j] = createRook(isupper(fen[i]) ? white : black);
      break;
    case 'q':
      board[j] = createQueen(isupper(fen[i]) ? white : black);
      break;
    case 'k':
      board[j] = createKing(isupper(fen[i]) ? white : black);
      break;
    }
    j++;
  }
}
void printBoard() {
  int j = 0;
  for (piece i : board) {
    std::cout << i.icon << " ";
    j++;
    if (j == 8) {
      std::cout << "\n";
      j = 0;
    }
  }
}
void pieceMove(int start, int end) {
  int diff = abs(start - end);
  bool pseudolegal = false;
  for (int i : board[start].direction) {
    if (diff % i == 0) {
      pseudolegal = true;
    }
  }
  if (pseudolegal && board[start].colour == turn) {
    turn = (turn == white) ? black : white;
    board[end] = board[start];
    board[start] = createEmpty();
  } else {
    std::cout << "Illegal move" << std::endl;
  }
}
int toCoord(std::string ord) {
  int coord;
  int num = stoi(ord.substr(1, 1));
  char let = ord[0];
  switch (let) {
  case 'A':
    coord = 1 + (8 - num) * 8;
    break;
  case 'B':
    coord = 2 + (8 - num) * 8;
    break;
  case 'C':
    coord = 3 + (8 - num) * 8;
    break;
  case 'D':
    coord = 4 + (8 - num) * 8;
    break;
  case 'E':
    coord = 5 + (8 - num) * 8;
    break;
  case 'F':
    coord = 6 + (8 - num) * 8;
    break;
  case 'G':
    coord = 7 + (8 - num) * 8;
    break;
  case 'H':
    coord = 8 + (8 - num) * 8;
    break;
  }
  return coord - 1;
}

int main() {
  parseFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
  std::string x, y;
  while (true) {
    printBoard();
    std::cout << "enter start coordinate" << std::endl;
    std::cin >> x;
    std::cout << "enter target coordinate" << std::endl;
    std::cin >> y;
    pieceMove(toCoord(x), toCoord(y));
  }
}