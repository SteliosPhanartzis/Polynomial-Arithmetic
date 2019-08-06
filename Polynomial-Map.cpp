#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

const char* inFl = "./input.txt";
const char* outFl = "./output.txt";

ifstream in(inFl);
ofstream out(outFl);


void print(map<int,int>& poly){
	bool firstFlag = true;
	for(map<int,int>::reverse_iterator itr = poly.rbegin(); itr != poly.rend(); itr++){
		if(itr->second == 0)
			continue;
		if(!firstFlag){
			if(itr->second < 0)
				out << " ";
			else
				out << " +";
		}
		if(itr->second != 1)
			out << itr->second;
		if(itr->first != 0){
			out << "X";
			if(itr->first != 1)
				out << "^" << itr->first;
		}
		firstFlag = false;
	}
	out << endl;
}
void add(map<int, int> &p1, map<int, int> &p2, map<int, int> &sum){
	sum = p1;
	for(auto const& term : p2)
		sum[term.first] += term.second;
}
void subtract(map<int, int> &p1, map<int, int> &p2, map<int, int> &diff){
	diff = p1;
	for(auto const& term : p2)
		diff[term.first] -= term.second;
}
void multiply(map<int,int>& p1, map<int,int>& p2, map<int,int>& prod){
	for(auto const& t1 : p1)
		for(auto const& t2 : p2)
			prod[t1.first + t2.first] += t1.second * t2.second;
}

int main() {
	map<int,int> poly1, poly2, sum, difference, product;
	int coef, exp;
	string line = "";
	
	while(getline(in, line)){
		stringstream stream(line);
		out << line << endl;
		//Construct first polynomial
		while(stream >> coef){
			stream >> exp;
			poly1[exp]= coef;
		}
		//Prep for next line
		getline(in, line);
		stream.clear();
		stream.str(line);
		out << line << endl;
		//Construct second polynomial
		while(stream >> coef){
			stream >> exp;
			poly2[exp] = coef;
		}
		//Polynomial input
		print(poly1); 
		print(poly2);
		//Add
		add(poly1, poly2, sum);
		out << endl << "Added: " << endl;	
		print(sum);
		//Subtract
		subtract(poly1, poly2, difference);
		out << endl << "Subtracted: " << endl;	
		print(difference);
		//Multiply
		multiply(poly1, poly2, product);
		out << endl << "Multiplied: "<< endl;	
		print(product); 
	}

	return 0;
}

