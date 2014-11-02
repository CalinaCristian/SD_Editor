/*CALINA CRISTIAN FLORIN 313CA*/
#include <iostream>
#include "backend.h"

//nu am nevoie de constructor/destructor pentru backend.
Backend::Backend()
{
}

Backend::~Backend()
{
}

//apelez functia cut din lista si salvez inainte GetText() in stiva undo.
void Backend::Cut(const int start, const int stop)
{
	std::cout << "Cut from " << start << " to " << stop << "\n";
	undo.push(list.GetText());
	list.cut(start,stop);
}

//apelez functia copy din lista
void Backend::Copy(const int start, const int stop)
{
	std::cout << "Copy from " << start << " to " << stop << "\n";
	list.copy(start,stop);
}

//apelez functia paste din lista si inainte salvez in stiva undo GetText().
void Backend::Paste(const int start)
{
	std::cout << "Paste from " << start << "\n";
	undo.push(list.GetText());
	list.paste(start);
}
//Daca lista nu e goala salvez GetText()-ul din ea in stiva redo, 
//o sterg si adaug incepand cu elementul 0 folosind functia add_many()
//GetText()-ul anterior din varful stivei undo prin pop()
void Backend::Undo(void)
{
	if (!list.isEmpty()) {
		std::cout << "Undo!\n";
		redo.push(list.GetText());
		list.DeleteList();
		list.add_many(0,undo.pop());
	}
//Daca lista e goala si am ceva in clipboard(am facut cut), adaug in 
//varful stivei redo "" (lista goala) si folosesc functia add_many()
//pentru a introduce de pe elementul 0 clipboardul.
	else if ((list.isEmpty())&&(list.get_clipboard()!=""))
	{
		std::cout << "Undo!\n";
		redo.push("");
		list.add_many(0,list.get_clipboard());
	}
}
//Daca stiva redo nu e goala , adaug in undo GetText()-ul pentru a 
//putea reveni la forma precedenta , golesc lista si introduc de pe 
//elementul 0 pop()-ul redo-lui prin functia add_many() a listei.
void Backend::Redo(void)
{
	if (!redo.isEmpty()){
		std::cout << "Redo!\n";
		undo.push(list.GetText());
		list.DeleteList();
		list.add_many(0,redo.pop());
	}
}
//apelez functia add_element() din lista si inainte salvez in stiva 
//undo GetText().
void Backend::Add(const int index, const char *word)
{
	std::cout << "Adding \"" << word << "\" from " << index << "\n";
	undo.push(list.GetText());
	list.add_element(index,word);
}
//apelez functia GetText() din lista.
const char *Backend::GetText(void)
{
	std::cout << "Sending back text!\n";
	return list.GetText();
}
