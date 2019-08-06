#include <fstream>
#include <iostream>
#include <sstream>
#include <string> 
using namespace std;

//Term Class
class Term{
private:
	int coefficient, exponent;

public:
	//Constructors
	Term(){
		coefficient = 0;
		exponent = 0;
	}
	Term(int c, int e){
		coefficient = c;
		exponent = e;
	}
	//Get and Set Methods
	void coef(int c){coefficient = c;}
	void exp(int e){exponent = e;}
	int exp(){return exponent;}
	int coef(){return coefficient;}
	//Makes << accessible by this class
	friend ostream& operator<<(ostream& os, Term s);
};

//Overloads << to print polynomial
ostream& operator<<(ostream& os, Term s){
	cout<<s.coef()<< "x^" << s.exp();
	return os;
}; 
//Assisting functions
void addPoly(Term &p,Term &q){
	p.coef(p.coef() + q.coef());
	p.exp(q.exp()); 
}

void subtractPoly(Term &p,Term &q){
	p.coef(p.coef() - q.coef()); 
	p.exp(q.exp());
}

void multSort(Term prod[], Term prodout[], int itr){
	int minExp=0;
	for(int i = 0; i <= itr;i++)
		if(minExp>prod[i].exp())
			minExp = prod[i].exp();
	for(int i = 0; i <= itr;i++){
		prodout[prod[i].exp() - minExp].coef(prod[i].coef());
	}
	prod = prodout; 
}
void multiplyPoly(Term p[],Term q[], int size){
	int iter = 0;
	cout << "size: " << size << endl;
	Term product[size * size];
	for(int i = 0; i < size; i++){
		if(p[i].coef() != 0){
			for(int j = 0; j < size; j++){
				if(p[i].coef() != 0 && q[j].coef() != 0)
					product[(i*size)+j] = Term((p[i].coef() * q[j].coef()),(p[i].exp() + q[j].exp()));			
			}
		}
	}
	for(int i = 0; i < size * size; i++)
		if(product[i].coef()!=0){
			p[iter]=product[i];
			product[i]=Term();
			iter++;
		}
	multSort(p,product,iter);
}

//void dividePoly(Term &p,Term &q){
//	p.exp(p.exp() - q.exp()); 
//	p.exp(p.exp() / q.exp()); 
//}

int main(){
	const char* filename = "./input.txt";
	ifstream infile(filename);
	ofstream outfile;
	int in, iter = 0, poly = 0, maxExp = 0, minExp = 0, oneD = 200;
	Term test[oneD][oneD];
	Term add[oneD], subtract[oneD], multiply[oneD];
	
	int input[oneD];
	for(int i=0; i<oneD; i++){
		input[i]=NULL;
		add[i] = Term();
		subtract[i] = Term();
	}
	string s;
	while(getline(infile,s)){
		stringstream t(s);
		while(t>>in){
			if((iter - 1)%2 == 0 && in < minExp)
				minExp = in;
			if((iter - 1)%2 == 0 && in > maxExp) 
				maxExp = in;
		}
		iter++;
	}
	cout << minExp << endl;
	cout << maxExp << endl;
	//reset iterator
	iter = 0;
	infile.clear();
	infile.seekg(0);
	//Iterate through input
	while(getline(infile,s)){
		stringstream t(s);
		while(t>>in){
			cout<<in<<" ";
			input[iter] = in;
			if((iter - 1)%2 == 0){
				Term x(input[iter-1],input[iter]);
				//Saves individual polynomials
				addPoly(test[poly][input[iter] - minExp],x);
				//Stores first polynomial to multiply
				if(poly == 0)
					addPoly(multiply[input[iter] - minExp],x);
				//Sum of polynomials
				addPoly(add[input[iter] - minExp],x);
				//Difference of polynomials
				if(poly == 0)
				    addPoly(subtract[input[iter] - minExp],x);
				else
				    subtractPoly(subtract[input[iter] - minExp],x);
			}
			iter++;
		}
		poly++;
		cout<<endl;
	}
	outfile.open("output.txt");
	//Polynomials
	outfile << "Polynomials" << endl;
	for(int i=0; i<poly; i++){
		for(int j = 0; j<oneD; j++){
			if(test[i][j].coef() != 0)
				outfile << test[i][j].coef() << "X^" << test[i][j].exp() << "+";
		}
		outfile << endl;
	}
	//Addition
	outfile << "Sum" << endl;
	for(int i=0; i<oneD; i++){
		if(add[i].coef() != 0){
			outfile << add[i].coef() << "X^" << add[i].exp() << "+";
		}
	}
	outfile << endl;
	//Subtraction
	outfile << "Difference" << endl;
	for(int i=0; i<oneD; i++){
		if(subtract[i].coef() != 0){
			outfile << subtract[i].coef() << "X^" << subtract[i].exp() << "+";
		}
	}
	outfile << endl;
	//Multiplication WIP
	outfile << "Product" << endl;
	multiplyPoly(multiply,test[1],oneD);
	for(int i=0; i<oneD;i++){
		if(multiply[i].coef() != 0)
		outfile << multiply[i].coef() << "X^" << multiply[i].exp() << "+";
	}
	outfile.close();
	return 0;
}

