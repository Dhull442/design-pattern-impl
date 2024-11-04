/*
Requirements:
- get,post,mod,del,vote,tags - Ques
- get,post,mod,del,vote - Answer
- get,post,mod,del,vote - Comment
- getRecentQuestions;
- getMostUpvotedQuestions;
- searchQues by User
- searchQues by tag


User:
id, name, rep, list<questionsID>, list<answersID>, list<commentsID>, lastActive, createdOn

Questions:
Id, userid, text, list<AnswersID>, list<CommentsID>, votes, CreatedOn, tags
postAnswer()


Answers:
Id, userid, text, list<commentsID>, votes, CreatedOn

Comments:
Id, userid, text, votes, CreatedOn

TextMatter -> Comments, Questions, Answers

StackOverflow:
List<users>, list<textMatter>
User getUserbyID()
User addUser()
User getUserbyRep()
updateRep()
delUser()
timeBanUser()

postTextMatter(Ques/Answ/Comment)
modTextMatter()
deltextMatter()
votetextMatter()

searchQuestionbyTag()
searchQuestionbyUser()
searchUser()

*/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#define US unordered_set
#define UM unordered_map
class TextMatter{
public:
	string id;
	string text;
	string userID;
	int votes;
	int createdOn;
	US<string> textIDs;
	TextMatter(){}
	TextMatter(string _userID, string _text){
		id = "T0000"; // sys genearted
		text = _text;
		userID = _userID;
		votes = 0;
		createdOn=0;
		textIDs=US<string>();
	}
	void addTextMatter(string _id){
		textIDs.insert(_id);
	}
	void delTextMatter(string _id){
		textIDs.erase(_id);
	}
	void addVote(int vote){
		// 1 or -1;
		votes += vote;
	}
	void print(){
		cout << id << " " << userID <<" "<<votes << " " << text<<" ";
		for(auto id: textIDs){
			cout << id <<",";
		}
		cout << endl;
	}
};
class Comment: public TextMatter{};
class Answer: public TextMatter{};
class Question: public TextMatter{
public:
	US<string> tags;
};
class User{
private:
	US< string > textIDs;
	int rep,lastActive,createdOn;
public:
	string id,name;
	User(){
		id=name="UNULL";
		rep=lastActive=createdOn=0;
		textIDs	= US<string>();
	}
	void addTextMatter(string oid){
		textIDs.insert(oid);
	}
	void delTextMatter(string oid){
		textIDs.erase(oid);
	}
	void addVote(int vote){
		rep+=vote;
	}
	void print(){
		cout << id << " " << rep <<" ids: ";
		for(auto id: textIDs){
			cout << id <<",";
		}
		cout << endl;
	}
};
// assume all correctness
class StackOverflow{
public:
	UM< string, User > userDB;
	UM< string, TextMatter > textDB;
	StackOverflow(){
		userDB = UM<string,User>();
		textDB = UM<string,TextMatter>();
	}
	void addUsers(int numUsers){
		for(int i=0;i<numUsers;i++){
			User u;
			u.id = u.name = "U"+to_string(i);
			userDB[u.id]=u;
		}
	}
	void addUser(User user){
		userDB[user.id] = user;
	}
	void delUser(string uid){
		userDB.erase(uid);
	}
	void addTextMatter(string uid, string pid, TextMatter tm){
		userDB[uid].addTextMatter(tm.id);
		textDB[tm.id] = tm;
		if(pid!="TNULL"){
			// A or C, add id to parent!
			textDB[pid].addTextMatter(tm.id);
		}
	}
	void modTextMatter(string uid, TextMatter newtm){
		// newTm id is already present.
		if(textDB[newtm.id].userID == uid){
			textDB[newtm.id] = newtm;
		}
	}
	void delTree(string id){
		for(auto id: textDB[id].textIDs){
			delTree(id);
		}
		userDB[textDB[id].userID].delTextMatter(id);
		textDB.erase(id);
	}
	void delTextMatter(string uid, string oid){
		if(textDB[oid].userID == uid){
			// Del Obj -> del inner obj -> remove from DB
			delTree(oid);
			userDB[uid].delTextMatter(oid);
		}
	}
	void addVote(string uid, string oid, int vote){
		// vote = -1 \ 1;
		if(textDB[oid].userID!=uid){
			textDB[oid].addVote(vote);
			userDB[textDB[oid].userID].addVote(vote);
		}
	}
	void print(){
		cout << "userDB: " << endl;
		for(auto user: userDB){
			user.second.print();
		}
		cout << endl << endl;
		cout << "textDB: " << endl;
		for(auto text: textDB){
			text.second.print();
		}
	}
};
int main(){
	StackOverflow server;
	server.addUsers(5);
	server.print();
	while(true){
		int action,vote;
		string uid, pid, oid, text;
		cin >> action;
		switch(action){
		case 0:
			{	// Add Text
				cin >> uid >> oid >> text;
				TextMatter txt(uid, text);
				txt.id = oid;
				server.addTextMatter(uid,"TNULL",txt);
				break;
			}
		case 1:
			{
				// Add Text sub
				cin >> uid >> pid >> oid >> text;
				TextMatter txt(uid, text);
				txt.id = oid;
				server.addTextMatter(uid,pid,txt);
				break;
			}
		case 2:
			{
				// Del
				cin >> uid >> oid;
				server.delTextMatter(uid,oid);
				break;
			}
		case 3:
			{
				// vote
				cin >> uid >> oid >> vote;
				server.addVote(uid,oid,vote);
				break;
			}

		}
		server.print();
	}

}