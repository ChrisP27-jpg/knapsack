#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Card{
	public:
	string name = "";
	int price = 0;
	int market = 0;
	int include = 0;
};

int main(int argc, char *argv[]){
	high_resolution_clock::time_point start = high_resolution_clock::now();
	ifstream cost;
	ifstream profit;
	ofstream output;
	
	//I removed my old vectors and created arrays down below that accomplish this task in a better way
	
	//vector<Card> cards;
	vector<Card> database;
	//vector<Card> subset;
	//vector<Card> answer;
	Card c;
	
	
	string line;
	string prof;
	int numCards;
	int totalMoney;
	int maxProfit = 0;
	int sumOfWeights=0;
	int sumSubset=0;
	int numSubset=0;
	int numAns=0;
	int profitSubset=0;
	int numDat=0;
	int x;
	int y=0;
	int crash=0;
	
	output.open("output.txt");
	line = argv[1];
	
	if (line=="-m"){
		prof=argv[2];
		profit.open(prof);
	}
	else if(line=="-p"){
		cost.open(argv[2]);
	}
	else{cout << "incorrect entry";return 0;}
	
	line = argv[3];
	
	if (line=="-m"){
		prof=argv[4];
		profit.open(prof);
	}
	else if(line=="-p"){
		cost.open(argv[4]);
	}
	else{cout << "incorrect entry";return 0;}
	
	profit >> x;
	for (int i=0;i<x;i++){
		profit >> c.name;
		profit >> c.market;
		database.push_back(c);
		numDat++;
	}
	
	cost >> numCards;
	
	//These arrays are holding the position of the cards in the database that are being used
	int cards[numDat];
	for(int i=0; i<numDat; i++){cards[i]=0;}
	int subset[numDat];
	for(int i=0; i<numDat; i++){subset[i]=0;}
	int answer[numDat];
	for(int i=0; i<numDat; i++){answer[i]=0;}
	int cardsCounter =0;
	
	
	while(cost){
		
		cost >> totalMoney;
		//for (int i=0; i<10; i++){cout << cards[i]<< " ";}cout << endl;
		
		//This for loop stores the positions of the cards being used for this particular problem in the cards array
		for (int i = 0; i<numCards; i++){
			cost >> line;
			cost >> x;
			c.name=line;
			c.price = x;
			crash=0;
			
			for (int j=0; j<numDat;j++){
				if(database[j].name==c.name){database[j].price=c.price; cards[cardsCounter]=j; cardsCounter++;j=numDat;crash=1;}
			}
			
			if (crash==0){
				cout << "the card \"" << c.name << "\" was not in the market price file. Exiting program." << endl;
				return 0; 
			}
			//else{
				
				//cards.push_back(c);
			//}
		}
		//for (int i=0; i<10; i++){cout << cards[i]<< " ";}cout << endl;
		
		
		//Earlier my code was just calculating the market prices, not the net profit of the transaction
		int temp;
		for (int i=0; i<numCards; i++){
			
			sumOfWeights+=database[cards[i]].price;	
			temp = (database[cards[i]].market-database[cards[i]].price);
			maxProfit += temp;	
			
		}
		
		//Set the contents of the cards array to the answer array
		if (sumOfWeights <=totalMoney){
			//answer = cards;	
			for (int i=0; i<numCards; i++){answer[i]=cards[i];}	
			numAns = numCards;
			
		}
		else{
		maxProfit =0;
		int count = pow(2,numCards);
		
		//This sets the positions of the cards for a single subset in the subset array and then determines if it is the best subset so far
		for (int i=0; i<count ; i++){
			for (int j=0; j<numCards; j++){
				if ((i & (1 << j)) != 0){
					//subset.push_back(cards[j]);	
					subset[numSubset]=cards[j];
					//cout << cards[j];
					numSubset++;	
				}		
			}	
			//cout << endl;
			for (int i=0; i<numSubset; i++){
				sumSubset+=database[subset[i]].price;	
				temp = (database[subset[i]].market-database[subset[i]].price);
				profitSubset+=temp;	
			}
			if (sumSubset <= totalMoney){
				if (profitSubset>=maxProfit){
						maxProfit = profitSubset;
						//answer=subset;	
						for (int i=0; i<numSubset; i++){answer[i]=subset[i];}	
						numAns=numSubset;
				}	
			}
			sumSubset=0;
			
			profitSubset=0;
			//subset.clear();
			for(int i=0; i<numCards;i++){subset[i]=0;}
			numSubset=0;
		}
		}
		
		//My earlier time value was rounding down so it would say the calculation was done in 0 seconds. Now it shows a more accurate number.
		high_resolution_clock::time_point stop = high_resolution_clock::now();
		duration<double> t = duration_cast<duration<double>>(stop - start);
		
		output << numCards << " " << maxProfit << " " << numAns << " " << t.count() << endl;
		//y=sizeof(answer)/sizeof(answer[0]);
		for (int i=0; i<numAns;i++){
			output << database[answer[i]].name << " " << database[answer[i]].price << " " << database[answer[i]].market-database[answer[i]].price << endl;		
		}
		//output << endl;
		
		
		//reset everything for next problem
		maxProfit = 0;
		sumOfWeights=0;
		sumSubset=0;
		numSubset=0;
		numAns=0;
		profitSubset=0;
		//cards.clear();
		cardsCounter=0;
		for(int i=0; i<numDat;i++){cards[i]=0;}
		cost >> numCards;
	}
	
	
	
}