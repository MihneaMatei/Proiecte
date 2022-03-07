-- INTEROGARI SIMPLE

-- 1.Afisati numele si prenumele judecatorului care s-a ocupat de procesul reclamantului X [REZOLVAT]

select j.Nume, j.Prenume
from Judecatori as j inner join Proces as p
on p.JudecatorID=j.JudecatorID
inner join Civili as c 
on c.IDCivil=p.IDCivilReclamant
where c.Nume = 'Vioreanu' and c.Prenume = 'Aurelia'

-- 2.Afisati toti judecatorii care au judecat un proces la care a luat parte X ca Avocat al acuzarii [REZOLVAT]
select *from Proces
select j.Nume, j.Prenume
from Judecatori as j inner join Proces as p
on p.JudecatorID=j.JudecatorID
inner join Avocati as a
on a.AvocatID = p.AvocatReclamantID
where a.Nume = 'Clinciu' and a.Prenume = 'Monica'

-- 3.Sa se afiseze judecatoriile unde au fost procese pe dosare de violenta domestica judecate de judecatorul selectat [REZOLVAT]

select o.Nume_Oras
from CategorieDosare as cd inner join Dosare as d
on cd.CategorieID = d.CategorieID
inner join Proces as p
on d.DosarID = p.DosarID
inner join Judecatorie as jde
on jde.JudecatorieID = p.JudecatorieID
inner join Judecatori as j
on p.JudecatorID = j.JudecatorID
inner join Orase as o
on jde.OrasID = o.OrasID
where cd.Descriere = 'Violenta domestica'
and j.Nume='Serbanescu'

-- 4.Sa se afiseze toate categoriile de dosare si motivul acestora ale civilului X [REZOLVAT]

select cde.Descriere, d.Motiv
from Dosare as d inner join CategorieDosare as cde
on d.CategorieID = cde.CategorieID
inner join Civili as c
on c.IDCivil = d.IDCivilParat or c.IDCivil = d.IDCivilReclamant
where c.Nume = 'Cotoiu'

-- 5.Sa se afiseze orasul cu cele mai multe procese la activ [REZOLVAT]

select top 1 o.Nume_Oras, count(p.ProcesID) as Nr_Procese
from Judecatorie as jde inner join Proces as p
on jde.JudecatorieID = p.JudecatorieID
inner join Orase as o
on o.OrasID = jde.OrasID
group by o.Nume_Oras
order by Nr_Procese desc

-- 6.Afisati orasele care au o judecatorie [REZOLVAT]
select o.Nume_Oras
from Orase as o inner join Judecatorie as jde
on o.OrasID = jde.OrasID

-- INTEROGARI COMPLEXE

-- 1.Gasiti cei mai tineri avocati din fiecare oras [REZOLVAT]
select a.Nume, a.Prenume, a.DataNasterii, o.Nume_Oras
from Avocati as a inner join Orase as o
on o.OrasID = a.OrasID
where a.DataNasterii in
(select max(b.DataNasterii) from Avocati b
where a.OrasID = b.OrasID)
order by a.DataNasterii desc

-- 2. Afisati avocatii cu cel mai mare salariu din fiecare oras [REZOLVAT]
select a.Nume, a.Prenume, a.Salariu, o.Nume_Oras
from Avocati as a inner join Orase as o
on a.OrasID = o.OrasID
where a.Salariu = (select max(b.Salariu) from Avocati as b
	where a.OrasID = b.OrasID)
order by o.Nume_Oras asc

-- 3. Afisati data celui mai apropiat proces de data X si civilii care participa la el [REZOLVAT]
select p.DataProces, (c1.Nume + ' ' + c1.Prenume) as Civil_Parat, (c2.Nume + ' ' + c2.Prenume) as Civil_Reclamant
from Proces as p inner join Civili as c1
on c1.IDCivil = p.IDCivilParat
inner join Civili as c2
on c2.IDCivil = p.IDCivilReclamant
where p.DataProces = (select top 1 p2.DataProces from Proces as p2
	where p2.DataProces > '01/01/2021' order by p2.DataProces asc)

-- 4. In ce an s-au angajat cei mai multi avocati?
select YEAR(A.DataAngajarii) as AN, count(A.DataAngajarii) as NR_ANG
from Avocati A
group by YEAR(A.DataAngajarii)
having count(A.DataAngajarii)>=(select TOP 1 count(B.DataAngajarii) from Avocati B group by YEAR(B.DataAngajarii)
order by count(B.DataAngajarii) desc)