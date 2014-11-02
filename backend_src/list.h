/*CALINA CRISTIAN FLORIN 313CA*/
#ifndef LIST__H
#define LIST__H

#include <string.h>
#include <iostream>

using namespace std; //pentru a nu mai pune std::

struct Node {
		string data; //cuvantul
    	Node *next;  //vecinul
    	int index;   //indexul (numarul literei) din cuvant
    };

class LinkedList {
    private:
    	Node *pFirst;
		string clipboard; //clipboardul pentru copy/paste
    public:
		//Constructor
    	LinkedList(){
    		pFirst = NULL; //initializez pFirst cu NULL
    	}
		//Destructor
    	~LinkedList(){
			//initializez un nod temporar ce pointeaza la pFirst-ul
			Node *tmp = pFirst;
			//parcurg lista
			while (tmp != NULL) {
				//pFirst ia valoarea vecinului sau
				pFirst = pFirst->next;
				//sterg tmp(care pointa la primul pFirst)
				delete tmp;
				//ii atribui lui tmp noul pFirst
				tmp = pFirst;
			}
			//ii atribui lui pFirst NULL pentru a-l elimina
			pFirst = NULL;
		}
		
		//Functia DeleteList
		//Pentru apelarea din undo (nu puteam apela destructorul
		//pentru ca dadea erori de double free).
		void DeleteList(){
			Node *tmp = pFirst;

			while (tmp != NULL) {
				pFirst = pFirst->next;
				delete tmp;
				tmp = pFirst;
			}
			pFirst = NULL;
		}
		
		//Functia GetText
    	const char* GetText(){
			//initializez un string x de tip static (pentru a se pastra
			//la iesirea din functie) cu "".
			static string x; 
			x = "";
			Node *node = pFirst; //parcurg lista
			while (node != NULL) {
				x += node->data + " "; //concatenez la x cuvantul si spatiu.
				node = node->next;
			}
			return x.c_str(); //returnez x de forma const char*.
		}
		
		//Functia last_index
    	//Functie ce retine indexul ultimului cuvant
    	int last_index(){
			//tmp pointeaza la pFirst si parcurg lista pana la ultimul nod
			Node *tmp = pFirst;
			while (tmp->next != NULL){
				tmp = tmp->next;
			}
			return tmp->index; //returnez indexul ultimului nod.
		}

		//Functia add_element
    	void add_element(int index, string word) {
			//Daca lista e goala initializez pFirst si ii pun 
			//word pe pFirst->data , vecinul sau va fi NULL si
			//indexul sau 0 (fiind primul element al listei).
			if (isEmpty()) {
				pFirst = new Node;
				pFirst->data = word;
				pFirst->next = NULL;
				pFirst->index = 0;
			}
			//Daca indexul este inaintea primului nod
			else if (index<=0) {
				//initializez un nod auxiliar
				Node *aux = new Node;
				//caruia ii pun pe aux->data cuvantul din parametru,
				//indexul va fi 0 (il pun in locul lui pFirst)
				//lui pFirst ii atribui aux, iar lui aux
				//ii atribui aux -> next.
				aux->data = word;
				aux->index = 0;
				aux->next = pFirst;
				pFirst = aux;
				aux = aux->next;
				//parcurg lista si cresc fiecare index de dupa cuvantul nou
				//adaugat cu dimensiunea cuvantului nou adaugat + 1 (spatiu).
				while (aux != NULL)
				{
					aux->index = aux->index + strlen(word.c_str()) + 1;
					aux = aux->next;
				}
			}
			//daca indexul din parametrii este mai mare decat indexul ultimului 
			//cuvant, creez un nod aux temporar si un nod tmp care pointeaza la
			//pFirst si parcurge lista pana la ultimul element.
			else if (index>last_index()) {
				Node *aux = new Node;
				Node *tmp = pFirst;
				while (tmp->next != NULL){
					tmp = tmp->next;
				}
				//lui aux ii atribui pe aux->data cuvantul din parametrii,
				//indexul ultimului cuvant + dimensiunea ultimului cuvant,
				//ultimul nod (tmp) va avea ca next pe aux iar aux va avea ca 
				//next null fiind noul ultim nod.
				aux->data = word;
				aux->index = tmp->index + strlen(tmp->data.c_str()) + 1;
				tmp->next = aux;
				aux->next = NULL;
			}
			//In cazul in care nu se executa conditiile de mai sus,
			//iau un nod aux care pointeaza la pFirst si un nod tmp
			//caruia ii atribui pe tmp->data cuvantul din parametrii.
			else {
				Node *aux;
				Node *tmp = new Node;
				tmp->data = word;
				//aux va parcurge lista pana cand se ajunge la indexul
				//unde trebuie introdus cuvantul.
				aux = pFirst;
				while (aux->next->index < index) {
					aux = aux->next;
				}
			//lui tmp (nodul pe care trebuie sa il introduc) ii atribui
			//ca next , nextul cuvantului dupa care trebuie introdus word,
			//iar nextul cuvantului dupa care trebuie introdus word va fi 
			//tmp. Dupa cresc indexul lui tmp cu indexul lui aux + dimensiunea
			//lui aux + 1 (spatiu) dupa aceea parcurg cuvintele de dupa tmp si
			//le cresc indexul cu dimensiunea cuvantului introdus + 1 (spatiu)
				tmp->next = aux->next;
				aux->next = tmp;
				tmp->index = aux->index + strlen(aux->data.c_str()) + 1;
				aux = tmp->next;
				while (aux != NULL) {
					aux->index = aux->index + strlen(word.c_str()) + 1;
					aux = aux->next;
				}
			}
		}
		
		//Functia copy
		string copy(const int start,const int stop) {
			//initializez la fiecare apelare clipboardul cu "" (gol).
			clipboard="";
			
			//daca lista e goala returnez clipboardul.
			if (isEmpty()){
				return clipboard;
			}
			//daca start>=stop (indecsi invalizi) returnez clipboard.
			else if (start >= stop){
				return clipboard;
			}
			//daca start e mai mare ca indexul ultimului cuvant returnez 
			else if (start > last_index()){ //clipboard.
				return clipboard;
			}
			//daca lista are un singur element in ea verific daca 
			//startul e mai mic sau egal cu indexul iar in caz afirmativ
			//concatenez la clipboard cuvantul din lista + spatiu (" ").
			else if (pFirst->next == NULL){
				if (start <= pFirst->index) {
					clipboard += pFirst->data + " ";
				}
				//chit ca se executa sau nu if-ul returnez clipboard.
				return clipboard; 
			}
			//Daca pana acum nu am iesit din functie (nu s-a executat 
			//nici una din conditii , intializez un nod care pointeaza la
			//pFirst si parcurg pana cand ori next-ul nodului e null ori
			//am ajuns la indexul de la care trebuie sa copiez.
			Node *node = pFirst;
			while ((node->index < start)&&(node->next !=NULL )){
				node = node->next;
			}
			//dupa aceea parcurg in continuare pana cand indexul nodului
			//depaseste indexul de stop si la fiecare nod parcurs concatenez
			//in clipboard cuvantul nodului parcurs si spatiu (" ").
			//Castul e pentru a nu da warning la compilare.
			while ((int) (node->index + strlen(node->data.c_str()) + 1) <= (int) stop){
				clipboard += node->data + " ";
				//daca next-ul nodului e NULL returnez clipboard.
				if (node->next == NULL){
					return clipboard;
				}
				node = node->next;
			}
			return clipboard;
		}
		
		//Functia add_many
		//Initial construita pentru a usura paste, ulterior descoperita
		//ca fiind indispensabila pentru undo/redo.
		//Primeste ca parametrii un index (de la care sa introduca cuvintele)
		//si un string clipboard (cuvintele ce trebuie inserate).
		void add_many (int index , string clipboard){
			//declar un clip temporar (tmpclip) si un token pentru strtok
			//precum si un s ce este initializat cu parametrul index.
			char *tmpclip;
			char *token;
			int s = index;
			//construiesc tmpclip de dimensiunea clipboardului  + 1(spatiu)
			tmpclip = new char [strlen(clipboard.c_str())+1];
			//copiez in tmpclip clipboardul (transformat in const char*).
			strcpy(tmpclip,clipboard.c_str());
			//incep functia strtok cu separatorul spatiu.
			token = strtok (tmpclip," ");
			while (token != NULL){
				//pentru fiecare cuvant intorduc in lista apeland
				//functia add_element cu indexul s si cuvantul token
				add_element(s,token);
				//cresc indexul s cu dimensiunea cuvantului si spatiu.
				s += strlen(token) + 1;
				//trec la urmatorul cuvant
				token = strtok(NULL," ");
			}
			//sterg tmpclip-ul.
			delete []tmpclip;
		}
		
		//Functia paste
		void paste(const int start){
			//daca clipboardul e gol ies din functie
			if (clipboard == ""){
				return;
			}
			//altfel daca lista e goala adaug clipboardul incepand cu
			//indexul 0 prin functia add_many.
			else if (isEmpty()){
				add_many(0,clipboard);
			}
			//altfel daca startul este inainte de indexul primului element
			//iar lista are minim 2 elemente , adaug incepand de la pozitia 0
			//clipboardul.
			else if ((start<=0)&&(pFirst->next!=NULL)) {
				add_many(0,clipboard);
			}
			//altfel daca lista are doar un element, verific daca startul este
			//mai mic sau egal cu indexul primului cuvant (0) , iar in caz 
			//afirmativ adaug clipboardul incepand cu indexul 0. In caz contrar,
			//adaug clipboardul incepand cu dimensiunea primului cuvant 
			//+ 1 (spatiu) 
			else if (pFirst->next == NULL) {
				if (start <= pFirst->index) {
					add_many(0,clipboard);
				}
				else {
					add_many((strlen(pFirst->data.c_str())+1),clipboard);
				}
			}
			//In cazul in care nu s-a executat nici una din instructiuniile
			//de mai sus, initializez un nod temporar care pointeaza la
			//pFirst , si parcurg lista pana cand indexul tmp-ului + dimensiunea
			//lui + 1 (spatiu) e mai mare sau egal cu start-ul.
			//Dupa aceea apelez functia add_many incepand cu indexul cuvantului
			// + dimensiunea lui + 1 si clipboard.
			else {
				Node *tmp = pFirst;
				//Castul e pentru a nu da warning la compilare.
				while (((int) (tmp->index + strlen(tmp->data.c_str())+1) < (int) start)
						&&(tmp->next != NULL)) {
					tmp = tmp->next;
				}
				add_many((tmp->index + strlen(tmp->data.c_str())+1) ,clipboard);
			}
		}
		//Functia cut
		//Are aceleasi conditii ca si copy doar ca mai adaug si o functie
		//pentru stergerea nodurilor.
		string cut (const int start, const int stop){
			clipboard="";
			if (isEmpty()){
				return clipboard;
			}

			else if (start >= stop){
				return clipboard;
			}
			//Castul e pentru a nu da warning la compilare.
			else if (( start > last_index()) || 
				((int) stop <= ((int) strlen(pFirst->data.c_str())))) {
				return clipboard;
			}
			//Daca lista are doar un element si startul e mai mic sau egal
			//cu indexul elementului (0) , concatenez la clipboard 
			//cuvantul si iau un nod temporar tmp = pFirst, ii atribui lui
			//pFirst NULL si sterg nodul tmp (pentru a nu avea mem leaks).
			else if (pFirst->next == NULL){
				if (start <= pFirst->index){
					clipboard += pFirst->data + " ";
					Node *tmp = pFirst;
					pFirst = NULL;
					delete tmp;
				}
				return clipboard;
			}
			else {
				Node *node = pFirst;
				while ((node->index < start)&&(node->next !=NULL )){
					node = node->next;
				}
				//initializez un s cu indexul + dimensiunea cuvantului
				int s = node->index + strlen(node->data.c_str())+1;
				while (s <= stop){
					//concatenez la clipboard cuvantul de pe nod + spatiu.
					clipboard += node->data + " ";
					//daca sunt la ultimul nod si s<=stop sterg nodul
					//prin funtia remove_node.
					if (node->next == NULL){
						if (s <= stop){
							remove_node(node);
						}
						return clipboard;
					}
					//x va lua valoarea de retur a functiei remove_node
					//initializez un aux inainte de a sterge nodul ce pointeaza
					//la node->next si dupa ce am sters nodul , lui node ii voi
					//atribui aux-ul.
					Node *aux = node->next;
					int x = remove_node(node);
					node = aux;
					//s creste cu dimensiunea cuvantului de pe noul nod.
					s += strlen(node->data.c_str())+1;
					//initializez un nod temporar care pointeaza la node
					//si parcurg lista incepand de la el pana la ultimul
					//element scazand din index-ul fiecarui nod x-ul.
					Node *tmp = node;
					while (tmp != NULL){
						tmp->index -= x;
						tmp = tmp->next;
					}
				}
				return clipboard;
			}
		}
		//Functia remove_node
		int remove_node(Node* node){
			//initializez x cu dimensiunea cuvantului din nod + 1 (spatiu).
			int x = strlen (node->data.c_str()) + 1;
			//Daca nodul reprezinta singurul element din lista il sterg
			if (pFirst->next == NULL){
					Node *tmp = pFirst;
					pFirst = NULL;
					delete tmp;
					return x;
			}
			//altfel daca nodul e primul din lista si lista nu e goala
			//ii atribui lui pFirst urmatorul nod si sterg nodul.
			else if ((node == pFirst)&&(pFirst->next != NULL)) {
				pFirst = pFirst->next;
				delete node;
			}
			else {
				//altfel parcurg lista pana la nodul dinaintea nodului ce 
				//trebuie sters cu un nod temporar initializat cu pFirst
				Node *aux = pFirst;
				while (aux->next != node){
					aux = aux->next;
				}
				//si ii atribui nextului nodului dinaintea nodului ce trebuie 
				//sters nextul nodului ce trebuie sters iar dupa sterg nodul.
				aux->next = node->next;
				delete node;
			}
			return x;
		}
		//Functia last_node
		//Parcurg lista cu un nod temporar pana la ultimul nod si il intorc
		Node* last_node(){
			Node *tmp = pFirst;
			while (tmp->next!=NULL){
				tmp = tmp->next;
			}
			return tmp;
		}
		//Functia get_clipboard
		//Intoarce clipboardul
		string get_clipboard() {
			return clipboard;
		}
		//Functia isEmpty
		//Intoarce true daca pFirst e NULL si false daca pFirst != NULL
    	bool isEmpty(){
    		return (pFirst == NULL);
    	}
    };

    #endif //LIST__H
