// simpel game to have some knowledge of the procedures programming with C++, im sure a lot of these things are not correctly design
// for example.. defining the methods outside of the class and because of that accessing into the class parameters my the name of the class
// it looks like we are accesing to thouse parameteres because they are static and public, search if the correct option its to access with ->



#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>
using namespace std;


class MyGame {
	vector<string> level_allowed{ "low","medium","high" };
	vector<string> possible_words;
	vector<string> low_level_words { "fly", "try", "car", "son", "cat", "pet", "fur" };
	vector<string> medium_level_words { "jazz", "frog", "fort", "tier", "scar", "part", "eyes" };
	vector<string> high_level_words{ "merge", "style", "motor", "plane", "tango", "wisky", "games" };
	string word_selected, level_selected;
	int words_lenght, maximum_words_count, word_idx, maximum_tries, current_try;

public:
	MyGame();
	void run();
	vector<char> compare_common_characters(string, string);
	bool update_level_info(string);
	void print_message(string);
	bool exist_level(string);
	bool is_correct_response(string);
	string get_user_response();
	string transforms_to_lower_case(string);
	string get_idx_word(int, vector<string>);
	string get_string_from_vectorChar(vector<char>);
};

MyGame::MyGame()
{

	// initiaize list with words and select one randomly 

	if (low_level_words.size() == medium_level_words.size() == high_level_words.size())
		maximum_words_count = low_level_words.size();
	else
		invalid_argument("Wrong Lenght defined in the constructor");

	MyGame::maximum_words_count = 6;
	MyGame::word_idx = rand() % MyGame::maximum_words_count;

};
void MyGame::run()
{
	// print welcome message
	print_message("Welcome to this fantastic game made by: Miguel Molledo");
	// set difficulty 
	print_message("Please set one of the difficulties allowed for this game:[low,medium,high]");
	string level_response = "default";
	// get level game by request
	while (level_response == "default") {
		// ask for a response
		level_response = MyGame::get_user_response();
		// get lower case
		level_response = transforms_to_lower_case(level_response);
		if (MyGame::exist_level(level_response) == false){
			// if its found
			MyGame::print_message("What you have insert do not match with any level detected:\n");
			MyGame::print_message("Please set one of the difficulties allowed for this game:[low,medium,high]");

			level_response = "default";
		}
		else 
			// now that eveything its updated. execute a "while" loop to get the response till the user wants to stop it or it reachs the maximum tries 
			if (MyGame::update_level_info(level_response) == true)
				break;
	}
	string word_response = " ";
	this->current_try = 0;
	while (word_response == " ") {
		// ask for a response
		MyGame::print_message("Guess a word with: "+to_string(this->words_lenght));
		word_response = MyGame::get_user_response();
		word_response = MyGame::transforms_to_lower_case(word_response);
		if (MyGame::is_correct_response(word_response) == true) {
			MyGame::print_message("Congratulations you have won the game!");
			MyGame::print_message("You had: " + to_string(MyGame::maximum_tries - MyGame::current_try) + " tries more to use!");
			MyGame::get_user_response();
			break;
		}
		else {
			// analize common characters with the word selected randomly 
			vector<char> comparation = MyGame::compare_common_characters(MyGame::word_selected, word_response);
			// print the common characters and discount one try for each loop step 
			string comparation_string = MyGame::get_string_from_vectorChar(comparation);
			string message = "You have this current matches: " + comparation_string;
			MyGame::print_message(message);
			this->print_message("You have this quantity of tries: "+ to_string(this->maximum_tries - this->current_try));
			word_response = " ";
		}
		if (this->current_try >= this->maximum_tries) {
			this->print_message("YOU HAVE LOST THIS GAME");
			MyGame::get_user_response();
		}
		// update our class with the new values , (maximum lenght == Game deficulty) so select one words or another depending on their lenght 
		this->current_try++;

	}
	

}
string MyGame::transforms_to_lower_case(string value) {
	transform(value.begin(), value.end(), value.begin(), tolower);
	return value;
}

bool MyGame::exist_level(string level) {
	if (find(begin(MyGame::level_allowed), end(MyGame::level_allowed), level) == end(MyGame::level_allowed))
		return false;
	else
		return true;

}


bool MyGame::update_level_info(string level){
	if (MyGame::exist_level(level) == false)
		return false;
	MyGame::level_selected = level;
	if (level == "low") {
		MyGame::word_selected = MyGame::get_idx_word(MyGame::word_idx, MyGame::low_level_words);
		MyGame::words_lenght = MyGame::word_selected.size();
		MyGame::maximum_tries = 5;
		return true;
	}
	if (level == "medium") {
		MyGame::word_selected = MyGame::get_idx_word(MyGame::word_idx, MyGame::medium_level_words);
		MyGame::words_lenght = MyGame::word_selected.size();
		MyGame::maximum_tries = 10;
		return true;
	}
	if (level == "high") {
		MyGame::word_selected = MyGame::get_idx_word(MyGame::word_idx, MyGame::high_level_words);
		MyGame::words_lenght = MyGame::word_selected.size();
		MyGame::maximum_tries = 15;
		return true;
	}
	return false;
}

string MyGame::get_idx_word(int word_idx, vector<string> words) {
	if (word_idx <= words.size())
		return words.at(word_idx);
}

vector<char> MyGame::compare_common_characters(string word, string possible_word)
{
	vector<char> result;
	char aux_char = '_';
	if (word.size() == possible_word.size()) {
		for (int i = 0; i < word.size(); i++) {
			if (word.at(i) == possible_word.at(i))
				result.push_back(word.at(i));
			else
				result.push_back(aux_char);
		}
		return result;
	}

}


string MyGame::get_string_from_vectorChar(vector<char> word) {
	string result;
	for (vector<char>::iterator it = word.begin(); it != word.end(); ++it) {

		result += *it;
	}
	return result;

}

void MyGame::print_message(string message) {
	cout << message + "\n";
}
string MyGame::get_user_response()
{
	string response;
	getline(cin, response);
	// check that the lenght corresponds with the difficulty selected before
	return response;
}

bool MyGame::is_correct_response(string response) {
	if (MyGame::word_selected == response)
		return true;
	else
		return false;

}



void main() {

	MyGame my_game;
	my_game.run();

}
