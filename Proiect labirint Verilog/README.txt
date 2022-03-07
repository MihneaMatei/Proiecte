	Prezentare generala
	Circuitul creat este un circuit secvential sincron ce are ca scop parcurgerea unui labirint de dimensiune 64x64. Peretii labirintului sunt notati cu 1, iar caile libere cu 0. Algoritmul isi propune gasirea iesirii folosind algoritmul Wall Follower cu regula mainii drepte. Practic, prin urmarirea constanta a peretelui din dreapta se garanteaza iesirea din labirint, in caz ca aceasta exista, iar in caz contrar se garanteaza revenirea la pozitia initiala. In cazul trecerii printr-o pozitie favorabila (notata cu 0), vom introduce valoarea 2 in aceasta pozitie, pentru a retine pe unde am mers.
	In implementare, am folosit, pe langa cele 2 variabila aferente starilor curenta si urmatoare, inca 3 variabile auxiliare, dintre care 2 (cr, cc) au rolul de a retine coordonatele pozitiei anterioare, iar una retine directia de mers  (dir; 0-dreapta, 1-sus, 2-stanga, 3-jos; directiile au fost luate uitandu-ma de sus la labirint).
	Blocul always secvential are rolul de a continua algoritmul, schimband starea curenta a automatului la fiecare tact de ceas (cand variabila done este 0).

	Starea 0 – stare initiala a automatului
	Dupa initializarea in afara starilor automatului a variabilelor de iesire si a variabilei pentru starea urmatoare, in starea 0 se initializeaza atat variabilele de rand si coloana curente, cat si copiile acestora, cu coordonateles de inceput. Variabilla de write-enable este pus pe 1, deoarece stim ca plecam dintr-o pozitie favorabila, iar variabila de directie este initializata cu 0, deoarece 0 inseamna dreapta. Trecem in starea 1.

	Starea 1 – starea de miscare si activare a semnalului de citire pentru noua pozitie
	Se verifica valoarea variabilei de directie (dir) si se incrementeaza variabilele de rand si coloana aferente. Se activeaza semnalul de citire,  maze_oe si se trece in starea 2.

	Starea 2 – stare decizionala, in functie de pozitia pe care am ajuns
	In aceasta stare se ia decizia revenirii la starea 1, cand pozitia nu este favorabila, sau continuarea in starea 3, cand pozitia este favorabila.
	Se verifica pozitia pe care suntem: daca este 1, variabilele de rand si coloana, incrementate anterior pentru noua pozitie, reiau valorile stocate in variabilele copie, pentru a reveni la coordonatele anterioare. Variabila de directe ia valoarea urmatoarei directii stabilite si se revine in starea 1.
	In cazul in care pozitia este favorabila, adica suntem pe 0, verificam prima data daca ne aflam pe marginea labirintului, adica daca am gasit o iesire. In caz afirmativ, activam semnalul de scriere (maze_we) si sarim in starea 99 (am folosit un numar mare pentru ca nu eram sigur la cate stari va ajunge automatul in final si pentru a nu confunda cumva), stare de final. In cazul in care nu suntem pe marginea labirintului, activam semnalul de scriere, retinem in variabilele-copie ale coordonatelor noile coordonate, pentru ca ne aflam pe un 0 si cel mai important, stabilim noua directie de dreapta a omuletului. In variabila dir pentru directie, la fiecare mutare ramane directia de ‘inainte’ pentru omuletul nostru (practic, spre acea directie este orientat el), asadar, pentru a orienta omuletul spre dreapta, directia noastra trebuie decrementata cu o unitate (inainte fiind 1, trebuie sa ajunge spre dreapta care e 0, iar daca este orientat spre dreapta, il voi orienta in jos 0 devenind 3). Se trece inapoi in starea 1.

	Starea 99 – starea de stop
	Cand am ajuns pe o pozitie de iesire din labirint, ajungem in aceasta stare, in care done devine 1 si se opreste algoritmul.

PS: Initial, cand am gandit automatul, avea ceva mai multe stari, insa am tot eliminat din ele pana am ajuns la o varianta cu 5 stari (prima varianta urcata pe checker), dupa care am constatat o micsorare a numarului de ciclii in urma eliminarii acelei stari. In varianta de fata, cred ca s-ar mai putea elimina cel mult 2 ciclii/test prin eliminarea starilor de initializare si stop. 
