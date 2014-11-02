CALINA CRISTIAN FLORIN 313CA

Am incercat sa lucrez cat mai mult in lista , astfel in backend.cpp apeland doar cate o 
functie din lista pentru fiecare functie in parte. Singurul lucru pe care l-am facut in 
backend.cpp a fost undo si redo ,  pentru care am luat cate o stiva si am salvat GetText-ul 
inainte de fiecare operatie ce afecta textul.

Codul este comentat in detaliu pentru fiecare functie in parte , astfel in readme voi face 
doar o prezentare a functiilor si a rolului lor.

Pentru functia add , am apelat o functie add_element din lista care imi introducea un 
element pe un index dat. In aceasta am luat in considerare toate cazurile (si daca lista e 
goala , si daca indecsii sunt invalizi precum si daca indecsii sunt valizi).

Pentru functia copy , am apelat o functie copy din lista care imi adauga in clipboard 
(declarat ca private de tip string in lista) cuvintele cuprinse integral intre indecsii 
primiti ca parametrii. Si pentru aceasta am luat in considerare numeroase conditii (daca 
lista e goala , daca start>=stop , daca start> ultimul index , daca am un singur element in 
lista, si daca nu se executa nici una din conditiile precedent mentionate). Aceasta functie 
imi returneaza clipboardul.

Pentru functia paste , am apelat o functie paste din lista care imi adauga cuvintele din 
clipboard in lista la indexul primit. Si pentru aceasta functie am luat in considerare 
conditiile : daca clipboard este gol , daca lista e goala , daca start e mai mic sau egal 
cu 0 si am un singur element in lista sau daca start e mai mare ca 0 si am un element 
in lista, si daca nu se executa nici una din conditiile enumerate anterior.
In implementarea initiala a functiei paste am facut strtok pe clipboard pentru fiecare 
conditie in parte si am realizat faptul ca este ineficient acest lucru , asa ca am creat o 
functie add_manny ce primea indexul pe care trebuie pus clipboardul si facea strtok , 
introducand dupa la indexul dat fiecare cuvant in parte si crescand indexul pe care 
introducea urmatorul cuvant cu dimensiunea cuvantului deja introdus + 1 (spatiul). 
Ulterior, in gandirea undo-ului si redo-ului am constatat ca aceasta functie este 
indispensabila acestora (face lucrurile mult mai usoare).

Pentru functia cut , am apelat o functie cut din lista care imi adauga in clipboard 
cuvintele cuprinse integral intre indecsii primiti ca parametrii. Aceasta functie are 
aceleasi conditii ca si functia copy , numai ca si sterge nodul dupa ce il adauga in 
clipboard apeland functia remove_node ce primeste ca parametru nodul ce trebuie eliminat. 
De asemenea , pentru nodurile urmatoare de dupa nodul sters , am scazut din indexul lor x-
ul returnat de remove_node (care reprezinta dimensiunea cuvantului de pe nodul sters).

Pentru functia GetText am apelat o functie GetText din lista care declara un static string  
x si un nod ce pointeaza la primul nod si parcurge lista , concatenand la x cuvantul de pe 
nod si spatiu. Functia returneaza x-ul. 

Pentru functia Undo am declarat in backend.h o stiva undo (de stringuri) de dimensiune 
100 (nu are un motiv anume dimensiunea). La fiecare operatie ce modifica lista
(add,cut,paste,redo) , am introdus GetText in stiva, astfel , cand se apela functia Undo, 
am luat doua conditii: Daca lista nu este goala , am sters lista si am introdus prin functia 
add_many incepand cu indexul 0, undo.pop() (ultimul GetText salvat). Iar daca lista e goala 
si am ceva in clipboard (am apelat functia get_clipboard care imi returneaza clipboard) , 
am adaugat incepand cu elementul 0 clipboardul.

Pentru functia Redo am declarat in backend.h o stiva redo (de stringuri) de dimensiune 100
(acelasi motiv ca la undo) , iar la fiecare operatie de undo , in cazul in care lista nu 
era goala adaugam  in redo GetTextul inainte de a o sterge. Altfel , daca lista era goala si 
aveam ceva in clipboard, adaugam in redo "" (gol). In functia redo verific daca stiva redo 
este goala si in caz contrar , adaug in undo GetText() , apoi sterg lista si adaug incepand 
cu indexul 0 , redo.pop.

Pentru a verifica daca am memory leakuri am folosit checkerul pus de Laurentiu Stamate care
continea o comanda ce verifica toate testele cu valgrind (acest checker m-a ajutat sa rezolv
o problema la testul 15 dupa ce am scos toate leakurile).
