/*CALINA CRISTIAN FLORIN 313CA*/
#ifndef STACK__H
#define STACK__H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template<int N>

class Stack {
	 private:
		string stackArray[N];
		int topLevel;
		
	public:
		//Constructor
		//Initializez topLevel cu -1.
		Stack() {
			topLevel = -1;
		}
		//Destructor (nu folosesc)
		~Stack() {
		}
		//Functia Push
		//cresc topLevel si adaug pe pozitia topLevel din
		//array elementul x.
		void push(string x) {
			topLevel++;
			stackArray[topLevel]=x;
		}
		//Functia Pop
		//retin in x elementul din varful stivei si scad topLevel
		//returnand la sfarsit x.
		string pop() {
			string x = stackArray[topLevel];
			topLevel--;
			return x;
		}
		//Functia peek
		//returnez elementul de pe pozitia topLevel.
		string peek() {
			return stackArray[topLevel];
		}
		//Functia isEmpty
		//returnez 0 (false) daca topLevel este mai mare sau egal cu 0
		//(am cel putin un element sau 1 (true) in caz contrar.
		int isEmpty() {
			return (topLevel<0);
		}

};
 
#endif // STACK__H
