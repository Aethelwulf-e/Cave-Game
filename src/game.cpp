#include "game.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::ifstream;
using std::ofstream;
using std::vector;

game::game() {
    this->cave_   = nullptr;
    this->player_ = nullptr;
}

game::~game() {
    delete this->player_;
    delete this->cave_;
}

void game::clearScreen() {
    cout << "Enter to continuer..." << endl;
    getchar();
    getchar();
    system("clear");
}

int game::showGameScreen() {
    int option = 0;
    cout << "1 - Start new game" << endl;
    cout << "2 - Your record"    << endl;
    cout << "0 - Exit"           << endl;
    cout << ">>>  ";
    cin  >> option;
    return option;
}

void game::init() {
    string playerName;
    bool playerWantsToLeave = false;

    cout << "Enter your name: ";
    cin >> playerName;

    this->player_ = this->findPlayerFromFile(playerName);
    this->cave_ = new cave(15, 15, 10);

    this->writePlayerStatsToFile();

    while(!playerWantsToLeave) {
        switch(this->showGameScreen())
        {
        case 1:
        {
            system("clear");
            while(!this->player_->isDead()) {
                if(player_->getPosX() == 0 && player_->getPosY() == 0) {
                  this->cave_->at(0, 0)->visit();
                }

                this->cave_->show();

                char direction;

                cout << "Choose a direction (a, w, s, d): ";
                cout << ">>>  ";
                cin >> direction;

                system("clear");

                int lastPosX = this->player_->getPosX();
                int lastPosY = this->player_->getPosY();

                this->player_->makeAMove(direction);

                int actualPosX = this->player_->getPosX();
                int actualPosY = this->player_->getPosY();

                if(!this->cave_->canGoTo(actualPosX, actualPosY)) {
                    //system("clear");
                    cout << "Invalid direction!" << endl << endl;
                    this->player_->undoLastAction();
                    continue;
                }

                this->cave_->at(lastPosX, lastPosY)->leave();
                this->cave_->at(actualPosX, actualPosY)->visit();

                if(this->cave_->at(actualPosX, actualPosY)->isAHole()) {
                    system("clear");
                    cout << "You died..." << endl;
                    this->player_->kill();
                    this->writePlayerStatsToFile();
                }
                else if(this->cave_->at(actualPosX, actualPosY)->isExit()) {
                    system("clear");
                    this->cave_->show();
                    cout << "You have found the exit!" << endl;
                    cout << "Here is another challenge:" << endl;
                    this->clearScreen();
                    this->player_->increaseScore();
                    this->cave_ = new cave(15, 15, 10);
                    this->player_ = new player(this->player_->getName(), this->player_->getScore(),
                                               0, 0, true);
                }
            }

            cout << "Final Configuration:" << endl;
            this->cave_->show();
            this->cave_ = new cave(15, 15, 60);
            this->player_ = new player(this->player_->getName(), this->player_->getScore(),
                                       0, 0, true);
            this->clearScreen();
            break;
        }
        case 2:
        {
            system("clear");
            cout << "Record: " << this->player_->getScore() << endl;
            this->clearScreen();
            break;
        }
        case 0:
        {
            system("clear");
            cout << "Goodbye!" << endl;
            playerWantsToLeave = true;
            //this->clearScreen();
            break;
        }
        default:
        {
            system("clear");
            cout << "Invalid option." << endl;
            this->clearScreen();
            break;
        }
        }
    }
}

player* game::findPlayerFromFile(string name) {
    ifstream reader = ifstream("playersStats.txt");

    if(!reader) {
        cout << "Error while loading user. Contact suport." << endl;
    } else {
        string currentName;
        int currentScore;
        while(reader >> currentName >> currentScore) {
            if(currentName == name) {
                reader.close();
                return new player(currentName, currentScore, 0, 0, true);
            }
        }
        reader.close();
    }
    return new player(name);
}

void game::writePlayerStatsToFile() {
    if(this->player_ == nullptr)
        return;

    ifstream reader = ifstream("playersStats.txt");

    vector<string> names = vector<string>();
    vector<int> scores   = vector<int>();

    if(!reader) {
        cout << "Error while opening files. Contact suport." << endl;
        return;
    } else {
        string currentName;
        int currentScore;

        while(reader >> currentName >> currentScore) {
            names.push_back(currentName);
            scores.push_back(currentScore);
        }

        reader.close();
    }

    ofstream writer = ofstream("playersStats.txt", ios::trunc);
    bool found = false;

    if(!writer) {
        cout << "Error while writing on files. Contact suport." << endl;
        return;
    } else {
        for(unsigned int i = 0; i < names.size(); i++) {
            if(names[i] == this->player_->getName()) {
                if(scores[i] < this->player_->getScore())
                    writer << names[i] << " " << this->player_->getScore() << "\n";
                else
                    writer << names[i] << " " << scores[i] << "\n";

                found = true;
            } else {
                writer << names[i] << " " << scores[i] << "\n";
            }
        }

        if(!found) {
            writer << this->player_->getName() << " " << this->player_->getScore() << "\n";
        }

        writer.close();
    }
}
