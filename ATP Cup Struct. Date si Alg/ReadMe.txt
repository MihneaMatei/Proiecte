Nume si prenume: Matei Mihnea-Cristian
Lucrare: ATP-Cup

Scopul lucrarii: Automatizarea unui turneu de tenis prin crearea unui cod capabil sa efectueze calculele necesare
cu privire la calificarea tarilor in turneu, dar si la calificarile ulterioare in etapele superioare ale acestuia. Prin introducerea
datelor corespunzatoare, programul isi propune sa usureze munca organizatorilor turneului. Calificarile se vor efectua pe baza
regulilor stabilite de acestia.

Structuri folosite:

Structura Player 
Structura Country
Structura BSTNode pentru nodurile arborelui
Structura Elem pentru nodurile listei dublu inlantuite, circulare, cu santinela -> Node
Structura nodes pentru nodurile stivelor -> stackNode
Structurea meci pentru meciurile intre tari -> Meci
struct Qnode pentru nodurile cozilor
struct Q pentru legatura intre nodurile cozilor -> Queue

Fiecare functie este descrisa detaliat in dreptul ei, in fisierul .c.

Cum functioneaza programul?

   Programul va primi prin intermediul argumentului 1 din linia de comanda cerintele ce vor fi stocate sub forma unui
vector cu numar cunoscut de elemente (5), iar efectuarea cerintelor va fi bazata pe acest vector. In cazul existentei
cerintei 5 (v[4]=1), vor fi citite in doua variabile ajutatoare elementele acestei cerinte.

   In cazul existentei cerintei 1: se vor citi elementele aflate in argumentul 2, date.in. Fiecare informatie este 
scrisa intr-o anumita ordine, datele fiind stocate ca atare. Aceste date memorate intr-o variabila auxiliara de tip
Country vor fi copiate intr-un nou nod al listei. La final, va fi creata santinela si legata de restul elementelor. 
In cazul existentei cerintei 1 in mod exclusiv, se va face afisarea listei create fara alte modificari.

   In cazul existentei cerintei 2: se va calcula numarul de tari ce trebuie sterse din lista pentru a incepe turneul
(pe baza unui criteriu dat - 2^n < nr tari), dupa care, lista va fi trimisa intr-o functie (calificari) ce are ca scop 
reducerea tarilor la nr corespunzator astfel: se va calcula minimul (pe baza criteriilor date) aflat in lista; va fi
cautata tara care corespunde minimului; se va sterge tara cautata; se micsoreaza numarul de tari ce trebuie sterse si
se va relua algoritmul pana cand numarul tarilor ce trebuiesc sterse este 0. Cand se implineste aceasta conditie, va fi
scrisa lista cu tarile ramase in fisierul de rezultate.

   In cazul existentei cerintei 3: va fi apelata functia etape. Tarile ramase in lista vor fi adaugate intr-o stiva. 
Tarile vor fi scoase din stiva 2 cate 2 pentru a efectua meciuri intre ele. Meciurile vor fi stocate intr-o variabila
ajutatoare si urcate in cozi (o coada pentru fiecare 2 tari). Dupa fiecare meci, pe baza criteriile vor fi rescrise
scorurile atribuite jucatorilor si vor fi retinute in doua variabile ajutatoare scorurile locale pe baza carora va fi
desemnata tara castigatoare. Tara castigatoare va fi urcata mai apoi in stiva WINNER ce va fi scrisa la finalul etape.
Tarile aflate in stiva vor fi urcate inapoi in stiva initiala pentru a se evita 'rasturnarea' listei initiale. Se
pastreaza o variabila ajutatoare 'alfa' pentru a tine contor tarilor ramase in turneu. Cand numarul tarilor ajunge <=4
jucatorii din tarile ramase vor fi adaugati intr-un vector (chiar si de mai multe ori) pentru a putea ajuta la cerinta 4.
Scrierea stivelor WINNER se va face cat timp alfa este diferit de 1, adica exista mai multe tari in turneu. Ultima
scriere va avea loc cand mai este doar o tara, alfa va fi 1 si va iesi din do-while.

    In cazul existentei cerintei 4: va fi folosit vectorul ajutator cls care contine toti jucatorii din ultimele 4 tari 
ramase in turneu, unii dintre ei in mai multe instante (acelasi jucator cu scoruri diferite). Acestia vor fi sortati
descrescator in functie de scor, dupa care vor fi stersi jucatorii care apar de mai multe ori, ramanand cu scorul cel
mai mare inregistrat, dupa care va fi verificata cerinta pentru jucatori cu acelasi scor si se vor efectua operatiile
cerute. Jucatorii vor fi urcati in BST direct din vector in clasamentul in forma finala.

    In cazul existentei cerintei 5: se va cauta existenta jucatorilor in clasament si se va numara numarul de scoruri
aflate intre ale lor. In cazul inexistentei in clasament al unui jucator, se va afisa mesajul corespunzator.
