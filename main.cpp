#include <iostream>
#include <cstdlib>

//#include <string>
#include <vector>
#include <string>
#include <fstream>


#include "User.h"
#include "Root.h"


using namespace std;

string encrypt(string a){

	for(unsigned int i = 0; i < a.length(); i++){
		a[i] = (a[i] + 127);
	}

	return a;

}

string decrypt(string a){
	for(unsigned int i = 0; i < a.length(); i++){
		a[i] = a[i] - 127;
	}

	return a;
}

bool verify(string a, vector<User> &  b){
	for(unsigned int i = 0; i < b.size(); i++){
		//	cout << b[i].getUsername();
		if(a == b[i].getUsername()){
			return false;
		}

	}
	return true;
}

bool verify(string a, vector<User> &  b, int & index){
	for(unsigned int i = 0; i < b.size(); i++){
		//	cout << b[i].getUsername();
		if(a == b[i].getUsername()){
			index = i;
			return false;
		}

	}
	return true;
}


bool passwordCheck(string password, string username, vector<User> & b){
	int userIndex = -1;	
	for(unsigned int i = 0; i < b.size(); i++){
		if(username == b[i].getUsername()){

			userIndex = i;
			break;

		}

	}

	if(userIndex != -1){
		if(password == b[userIndex].getPassword()){
			return true;
		}
	}

	return false;
}

void sendMessage(string user, string messageTo, vector<User> & b, User * currUser){
	int index;
	if(!verify(user, b, index)){

		b[index].message =  messageTo + "\t-" + currUser->getUsername(); 
	}
}

int getUserIndex(string user, vector<User> & b){
	for(unsigned int i = 0; i < b.size(); i++){
		if(user == b[i].getUsername()){
			return i;
		}
	}
	return -1;
}

void printAllUsersInfo(vector <User> & b){
	cout << endl << endl;
	for(unsigned int i = 0; i < b.size(); i++){
		cout << "Username: " << b[i].getUsername() << endl << "Password: " << b[i].getPassword() << endl;
		if(b[i].message == ""){
			cout << "No Messages.\n\n";
		}else{
			cout << b[i].message << endl << endl;
		}
	}

}

int main(){


	int option;

	vector<User> users;

	Root rootUser("root", "root");

	users.push_back(rootUser);

	ifstream fileInput("users.txt");
	if(fileInput.is_open()){

		string username = "";
		string password = "";
		string message = "";

		while(fileInput >> username){
			fileInput >> password;
			getline(fileInput, message);
			User freshUser(decrypt(username), decrypt(password), decrypt(message));
			users.push_back(freshUser);
		}

	}



	do{
		cout << endl << endl;
		cout << "Enter the numeric value of the option you wish to choose" << endl;
		cout << "1. Create Account" << endl;
		cout << "2. Login" << endl;
		cout << "3. Exit" << endl;

		cin >> option;
		string username = "";


		switch(option){

			case 1:{
				       int exists = 1;
				       int alertUser = 0;



				       do{
					       if(alertUser){
						       cout << "That Username is Already in Use" << endl;

					       }
					       else{ alertUser = 1;}


					       cout << "Username: ";

					       cin >> username;


					       if(verify(username, users)){
						       exists = 0;
					       }

				       }while(exists == 1);

				       string password = "";

				       cout << "Password: ";

				       cin >> password;


				       User newUser(username, password);

				       users.push_back(newUser);

				       cout << endl << endl << "Your Account Details" << endl;
				       cout << "Username: " << username << endl;
				       cout << "Password: " << password << endl;



				       break;	
			       }


			case 2:{
				       string login_Password;
				       string login_Username; 


				       do{
					       cout << "Enter Username: ";

					       cin >> login_Username;
				       }while(verify(login_Username,users));

				       do{


					       cout << "Enter Password: ";
					       cin >> login_Password;
				       }while(!passwordCheck(login_Password, login_Username, users));

				       User * currentUser = (login_Username == "root") ? new Root(login_Username, login_Password, users[getUserIndex(login_Username, users)].message) : new User(login_Username, login_Password, users[getUserIndex(login_Username, users)].message);
				       int op;

				       if(login_Username != "root"){

					       do{	
						       cout << endl << endl << "Action Menu" << endl;
						       cout << "1. Send Message" << endl;
						       cout << "2. Get Messages" << endl;
						       cout << "3. Log Out" << endl;
						       cout << "4. Delete Account" << endl;

						       cin >> op;

						       switch(op){


							       case 1:{
									      string message;
									      string messageUser;
									      do{
										      cout << "Message To: ";
										      cin >> messageUser;
									      }while(verify(messageUser, users));

									      cout << "Message: ";
									      cin.ignore();
									      getline(cin, message);

									      if(messageUser == currentUser->getUsername()){
										      currentUser->message = message + "\t-"+messageUser;
									      }else{

										      sendMessage(messageUser, message, users, currentUser);
									      }
									      cout << endl << "Message Sent." << endl;


									      break;
								      }
							       case 2:{
									      if(currentUser->message == ""){
										      cout<< endl << endl << "No messages\n";
									      }else{
										      cout << endl<< endl<< currentUser->message << endl;
									      }


									      break;
								      }
							       case 3:{
									      break;
								      }
							       case 4:{
									      users.erase(users.begin() + getUserIndex(login_Username, users));
									      break;
								      }


							       default:
								      cout << "Please choose another option" << endl;
								      break;

						       }



					       }while(op != 3 && op !=4);
				       }
				       else if(login_Username == "root"){

					       do{

						       cout << endl << endl << "Root Action Menu" << endl;
						       cout << "1. Send Message" << endl;
						       cout << "2. Get Messages" << endl;
						       cout << "3. Get All Users Info" << endl;
						       cout << "4. Delete User" << endl;
						       cout << "5. Log Out" << endl;

						       cin >> op;

						       switch(op){

							       case 1:{
									      string message;
									      string messageUser;
									      do{
										      cout << "Message To: ";
										      cin >> messageUser;
									      }while(verify(messageUser, users));

									      cout << "Message: ";
									      cin.ignore();
									      getline(cin, message);

									      if(messageUser == currentUser->getUsername()){
										      currentUser->message = message + "    -"+messageUser;
									      }else{

										      sendMessage(messageUser, message, users, currentUser);
									      }
									      cout << endl << "Message Sent." << endl;


									      break;
								      }
							       case 2:{
									      if(currentUser->message == ""){
										      cout<< endl << endl << "No messages\n";
									      }else{
										      cout << endl<< endl<< currentUser->message << endl;
									      }


									      break;
								      }


							       case 3:{
									      printAllUsersInfo(users);
									      break;
								      }
							       case 4:{
									      string userToDelete = "";
									      do{
										      cout << "User to Delete: ";
										      cin.ignore();
										      getline(cin, userToDelete);
									      }while(verify(userToDelete,users) ||  userToDelete == "root");


									      users.erase(users.begin() + getUserIndex(userToDelete, users));
									      cout << endl << endl << userToDelete <<"'s Account was Deleted."<< endl << endl;

								      }

						       }


					       }while(op != 5);


				       }

				       delete currentUser;


				       break;
			       }

			case 3:{

				       ofstream outputFile("users.txt");
				       if(outputFile.is_open()){

					       for(unsigned int i  = 0; i < users.size(); i++){
						       if(users[i].getUsername() != "root"){

						       outputFile << encrypt(users[i].getUsername()) << " " << encrypt(users[i].getPassword()) << " " << encrypt(users[i].message) << endl;
						       }

					       }
				       }


				       exit(0);
				       break;
			       }
			       //			case 4:

			default:
			       cout << "Please Select an Available Option." << endl << endl;

		}

	}while(option != 3);







	return 0;
}
