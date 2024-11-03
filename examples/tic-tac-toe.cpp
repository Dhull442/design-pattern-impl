#include<iostream>
#include<vector>
// #include<assert>
using namespace std;
class User{
private:
	int id;
	int score;
	int numGames;
	int rating;
public:
	User(){
		id = 0;
		score = 0;
		numGames = 0;
	}
	void setID(int _id){
		id = _id;
	}
	int getID(){
		return id;
	}
	void setScore(int value){
		// win = 2, draw = 1, lose = 0;
		score += value;
		numGames++;
	}
	double getAvgScore(){
		if(numGames==0) return 0;
		return (double)score/(double)numGames;
	}
};
struct Move{
	int x,y;
};
class Game{
private:
	int id;
	int uid1, uid2;
	vector< vector<int> > board;
	int boardSize;
	vector< Move > moves;
	int result; // -1, 0, 1, 2;
public:
	Game(int _uid1, int _uid2, int _boardSize){
		id = 0;
		uid1 = _uid1;
		uid2 = _uid2;
		boardSize = _boardSize;
		board = vector< vector<int> > (boardSize, vector<int>(boardSize,-1));
		moves = vector<Move>();
		result = -1;
		printBoard();
	}
	int playMove(int uid, Move move){
		cout << "Player "<<uid <<" places at " << move.x << " " << move.y << endl;
		int play = uid == uid1? 0:1;
		if(move.x < boardSize && move.x >= 0 && move.y >= 0 && move.y < boardSize){
			board[move.x][move.y] = play;
			moves.push_back(move);
			checkResult();
		}
		printBoard();
		return result;

	}
	void printBoard(){
		cout << "Board:" << endl;
		for(auto row: board){
			for(auto val: row){
				cout << val <<"|\t";
			}
			cout << endl;
		}
	}
	void checkResult(){
		Move m = moves.back();
		int play = board[m.x][m.y];
		bool winDiagonal, winRdiagonal, winVertical, winHorizontal;
		winDiagonal = winRdiagonal = winVertical = winHorizontal = true;
		for(int i=0;i<boardSize;i++){
			if(winDiagonal && board[i][i]!=play){
					winDiagonal = false;
			}
			if(winRdiagonal && board[i][boardSize-i-1] != play){
					winRdiagonal=false;
			}
			if(winVertical && board[i][m.y] != play){
				winVertical = false;
			}
			if(winHorizontal && board[m.x][i] != play){
				winHorizontal = false;
			}
		}
		if(winDiagonal || winRdiagonal || winVertical || winHorizontal){
			// Set Result
			result = play;
			return;
		}
		if(moves.size() == boardSize*boardSize){
			result = 2;
		}
	}
	vector< Move > getGame(){
		if(result!=-1)
			return moves;
		return vector< Move > ();
	}
};

int main(){
	User u1, u2;
	u1.setID(0);
	u2.setID(1);
	Game game(u1.getID(),u2.getID(),3);
	int i=0;
	while(true){
		Move m;
		int uid = i%2==0? u1.getID(): u2.getID();
		i++;
		cin >> m.x >> m.y;
		int result = game.playMove(uid, m);
		switch(result){
			case 0:
				{cout << "Player " << u1.getID() <<" won!" << endl;
								u1.setScore(2);
								u2.setScore(0);
								break;}
			case 1:
				{cout << "Player " << u2.getID() <<" won!" << endl;
								u1.setScore(0);
								u2.setScore(2);
								break;}
			case 2:
				{cout << "Draw / No result!" << endl;
								u1.setScore(1);
								u2.setScore(1);
								break;}
			default:
				break;
		}
		if(result!=-1) break;
	}
}