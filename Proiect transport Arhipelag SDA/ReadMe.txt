Nume si prenume: Matei Mihnea-Cristian
Lucrare: Marele arhipelag Eao-Zinci

Scopul lucrarii: Automatizarea unui sistem de transport prin crearea unui cod capabil sa efectueze calculele necesare
cu privire la mutarea avioanelor de pe insule, in cazul in care este necesar. Scopul lucrarii este usurarea tranzitului aerian
in arhipelagul Eao-Zinci prin schimbarea traseului sau aeroportului unor avioane pentru a se evita aglomeratii.

Structuri folosite:

Structura Resursa
Structura Island
Structura Graph folosita pentru a stoca datele cerintei 3

Fiecare functie este descrisa detaliat in dreptul ei, in fisierul .c.

Cum functioneaza programul?

	Programul va primi prin intermediul argumentului 1 din linia de comanda datele necesare rezolvarii cerintelor. Acestea
vor fi stocate intr-un vector de insule. Se vor citi din fisier numarul de insule, insulele, resursele insulelor si conexiunile 
insulelor. Conexiunile intre insule si costul efectuarii zborurilor intre insule vor fi stocate intr-o matrice.

	Pentru etapa de Proiectare: se va citi de la tastatura primul cuvant de pe linie si se va verifica care este acesta.
In cazul in care cuvantul este conexiune, vor fi citite urmatoarele doua cuvinte si vor fi transformate in cifrele aferente insulelor.
Va fi verificata existenta drumului intre insule si va fi afisat mesajul corespunzator. In cazul in care se cere legatura unei insule,
va fi transformat urmatorul cuvant citit in cifre si vor fi cautate legaturile existente in matrice cu acesta. Pentru cazul "adauga_zbor"
va fi adaugat un nou drum in matrice, iar pentru "anulare_zbor" va fi sters, cu acelasi algoritm. Pentru functia "max_res", vor fi intro-
duse intr-un vector toate resursele existente pe harta, vor fi ordonate lexicografic, iar mai apoi vor fi sterse dublurile. "Max_cant"
va fi abordat asemanator, insa va fi calculata resursa gasita cel mai mult cantitativ, dupa care vor fi cautate insulele pe care se
gaseste in cantitatea respectiva.

	Pentru etapa de Analiza: se va compara cuvantul citit cu cerintele existente la aceasta etapa. In cazul citirii cerintei
"drum_zbor", se va apela algoritmul lui Dijkstra pentru crearea unui vector de distante intre sursa data si celelalte insule. De ase-
menea, va retine si parintii sursei pentru afisarea acestora. In cazul citirii "timp_zbor", folosind tot algoritmul lui Dijkstra,
se va calcula distanta de la sursa data la destinatie si, in cazul in care exista, va fi afisata. In cazul citirii cerintei "min_zbor",
pe langa algoritmul lui Dijkstra, vor fi apelatie doua functii: functia "min_zbor1", care creeaza o noua matrice ce va adauga in
dreptul legaturilor care nu contin insula sursa timpul de stationare de 15 min. In urma apelarii functiei "min_zbor2" se va efectua
din nou algoritmul lui Dijsktra pe noua matrice si va fi afisata cea mai scurta distanta gasita.

	Pentru etapa de Gestiune: se citeste noul set de date si este trimis in functia "gestiune". Aceasta functie verifica
prima data existenta avioanelor in plus la vreo insula. In cazul in care nu gaseste, afiseaza normal insulele. In cazul in care 
gaseste, verifica numarul acestora, daca depaseste toleranta totala. In caz afirmativ, se afiseaza mesajul corespunzator. In caz 
negativ, se vor efectua operatiile necesare mutarii avioanelor. Avioanele in exces vor fi asezate intr-un vector cu id-uri, iar 
numarul acestora va fi stocat intr-un vector in care indicele va fi insula pe care se afla in exces.
