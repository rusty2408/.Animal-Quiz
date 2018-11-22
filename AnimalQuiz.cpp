#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

vector<string> nonWhitespace(string animals)
//removes whitespace from elements entered into string
{
    vector<string> animalVect;      //vector of animals
    animals += " ";                 //string to store animals
    string ANI = "";                //storing animals wiithout a space
    for(int i=0; i<animals.size(); i++)
    {
        if(animals[i] != ' ')
        {
            ANI += animals[i];
        }
        else if(animals[i] == ' ' && !ANI.empty())
        {
            animalVect.push_back(ANI);
            ANI.clear();
        }
    }
    return animalVect;          //return of a vector string
}


vector<string> initialStart()
        {
            string animals;
            string ANI;
            cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;
                do{//must be done at least once
                    getline(cin, animals);
                    ANI += (animals + ' ');
                }while(!animals.empty());

                vector<string> animalVect = nonWhitespace(ANI);
            for (int i = 0; i < animalVect.size(); i++)
            {
                cout << i + 1 << ": " << animalVect[i] << endl;     //list elem of vector from 1-5
            }
            return animalVect;
        }

vector<string> questGenerator(vector<string> animalVect, size_t count)
{
    string quest;

    srand(time(0));
    int randQ = rand()%3+1; //rand num btw 1-3

    //use rand shuffle to unorder animals in vector(user familiar with order)
    random_shuffle(animalVect.begin(), animalVect.end());

    //for loop used to range through vector and reduce to 1-3 sized list
    for(int i=0, j=animalVect.size() - randQ; i<j; i++)
    {
        animalVect.pop_back();
    }

    for(int i = 0; i < animalVect.size(); i++)
    {
        quest += animalVect[i];
    }

    //another rand shuffle to jumble new string of animals
    random_shuffle(quest.begin(), quest.end());

    //loop is set to take the lowest lettered ani and add underscores according to
    for(int i=0; i<fmin(count, quest.length()); i++)
    {
        quest[i] = '_';
    }
    random_shuffle(quest.begin(), quest.end());

    cout<<"What are "<<animalVect.size()<<" animals in "<<quest<<" ?";

    return animalVect;
}


vector<string> questAttempt()
{
    string questResponse;
    getline(cin, questResponse);
    vector<string> response = nonWhitespace(questResponse);

    return response;
}
bool rightwrongAnswer(vector<string> response, vector<string> questGenerator)
{
    //right=true right=false=wrong
    bool right;

    //double for loop will compare entry and outputed question
    for(int i=0; i<response.size(); i++)
    {
        right = false;
        for(int j=0; j< questGenerator.size(); j++)
        {
            if(response[i] == questGenerator[j])
            {
                right = true;
            }
        }
        if(right == false)
            ;

    }
    return right;
}

int main() {
    vector<string> animalVect; //Vect String of all the animals
    animalVect = initialStart();

    vector<string> response; //users response to questions

    //string animals = ""; // empty to be populated in game
    //string ANI = "";

    size_t count = 0; //representing difficulty btw questions
    int correctAni = 0; // number of times question is right


    /*While user enters animals add to string w/ space to account
        for new lines do at least once no matter what's entered*/
    while (true) {
        vector<string> questAnswer;
        questAnswer = questGenerator(animalVect, count);
        response = questAttempt();

        //to end game
        if (response[0] == "quit" || response[0] == "q" || response[0] == "QUIT" || response[0] == "Q") {
            cout << "Bye..";
            break;
        }
        //hint for user -- show contents in vector
        if (response[0] == "?")
        {
            do{

                for (int i = 0; i < animalVect.size(); i++) {
                    cout << i + 1 << ": " << animalVect[i] << endl;
                }
                cout << "Enter again: " << endl;
                response = questAttempt();
            }while(response[0] == "?");
        }

        //Compare response to question with the true answer
        if (rightwrongAnswer(questAnswer, response)) {
            cout << "Yes!" << endl;
            if (++correctAni == 2) {
                correctAni = 0;
                count++;
                cout << "Succeeded two consecutive times, challenge goes up!"<<endl;
            } else {
                correctAni = 1;
                cout << endl;
            }
        } else {
            cout << "Nope!" << endl;
            if (--correctAni == 2) {
                correctAni = 0;
                if (count > 0) {
                    count--;
                    cout << "Missed two consecutive times, challenge goes down!" << endl;
                } else {
                    correctAni = -1;
                    cout << endl;
                }
            }
        }
    }
        return 0;
}




