#include<iostream>
#include<vector>
using namespace std;
#define SIZE 8
#define pb push_back
struct Position{
	int x, y;
	Position(){}
	Position(int _x, int _y){
		x = _x; y = _y;
	}
};
struct Move{
	Position src, dst;
	Move(Position _src, Position _dst){
		src = _src;
		dst = _dst;
	}
};
class ChessPiece{
public:
	char name;
	Position position;
	bool doesExist;
	ChessPiece(Position _position = Position(0,0)){position=_position;}
	// bool validMove(Move move);
};
class Pawn : public ChessPiece{
public:
	Pawn(Position _position){
		name = 'P';
		doesExist=true;
		position = _position;
	}
};
class Bishop : public ChessPiece{
public:
	Bishop(Position _position){
		name = 'B';
		doesExist = true;
		position = _position;
	}
};
class Knight : public ChessPiece{
public:
	Knight(Position _position){
		name = 'T';
		doesExist = true;
		position = _position;
	}
};
class Rook : public ChessPiece{
public:
	Rook(Position _position){
		name = 'R';
		doesExist = true;
		position = _position;
	}
};
class Queen : public ChessPiece{
public:
	Queen(Position _position){
		name = 'Q';
		doesExist = true;
		position = _position;
	}
};
class King : public ChessPiece{
public:
	King(Position _position=Position(0,0)){
		name = 'K';
		doesExist = true;
		position = _position;
	}
};

class User{
private:
	int id;
	int score;
	int numGames;
public:
	User(){
		id=score=numGames=0;
	}
	void setID(int _id){
		id=_id;
	}
	int getID(){
		return id;
	}
	void setScore(int result){
		score += result;
		numGames++;
	}
	double getAvgScore(){
		if(numGames==0) return 0;
		return (double)score/(double)numGames;
	}
};

class Ensemble{
public:
	vector<ChessPiece> pieces;
	bool isChecked;
	// black or white player
	Ensemble(bool color = true){
		isChecked = false;
		pieces = vector<ChessPiece>();
		int posX = color? 1 : SIZE-1-1;
		for(int i=0;i<SIZE;i++){
			pieces.pb(Pawn(Position(posX, i)));
		}
		posX = color? 0: SIZE-1;
		pieces.pb(Rook(Position(posX, 0)));
		pieces.pb(Rook(Position(posX, SIZE-1)));
		pieces.pb(Knight(Position(posX, 1)));
		pieces.pb(Knight(Position(posX, SIZE-1-1)));
		pieces.pb(Bishop(Position(posX, 2)));
		pieces.pb(Bishop(Position(posX, SIZE-1-2)));
		pieces.pb(color? Queen(Position(0,4)): Queen(Position(SIZE-1,3)));
		pieces.pb(color? King(Position(0,3)):King(Position(SIZE-1,4)));
	}
};
class Chess{
private:	
	vector< vector< char > > board;
	Ensemble white, black;
	int uid1, uid2;
	double clockUser1, clockUser2;
	int result; // -1, 0, 1, 2;
	vector<Move> moves;
public:
	Chess(){
		board = vector<vector<char> > (SIZE, vector<char>(SIZE, '_'));
		white = initEnsemble(true);
		black = initEnsemble(false);
		moves = vector<Move>();
		result = -1;
		clockUser1 = 100;
		clockUser2 = 100;
		printBoard();
	}
	Ensemble initEnsemble(bool color = true){
		Ensemble e(color);
		for(auto piece : e.pieces){
			board[piece.position.x][piece.position.y] = piece.name;
		}
		return e;
	}
	void printBoard(){
		cout << "CHESS BOARD: " << endl;
		cout << "  ";
		for(int i=0;i<SIZE;i++){
			cout << i << " ";
		}
		cout << endl;
		for(int i=0;i<SIZE;i++){
			cout << i << " ";
			for(auto c: board[i]){
				cout << c << " ";
			}
			cout << endl;
		}
	}
	int playMove(int uid, Move move){
		return result;
	}

};
int main(){
	Chess game;
	User u1,u2;

}