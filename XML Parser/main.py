import xml.etree.ElementTree as ET

mytree = ET.parse('sample.xml')
mytree2 = ET.parse('xml2.xml')
myroot = mytree.getroot()
myroot2 = mytree2.getroot()
index = 11

print("Meniu principal")
print("Pentru a iesi, introduceti x")

ans = input("Introduceti comanda dorita (afisare, inserare, stergere, modificare, cautare, cautare avansata): ")

while(ans!='x'):
    if (ans=='afisare'):
        print("==================================================")
        inp = input("Ce doriti sa afisati? Alege intre angajati, asociati sau departamente: ")
        if (inp == "angajati"):
            inp2 = input("Doriti sa afisati informatii suplimentare? (da,nu): ")
            if (inp2 == 'nu'):
                for x in myroot.findall('ANGAJAT'):
                    item = x.find('NUME').text
                    item2 = x.find('PRENUME').text
                    print(item, item2)
            if (inp2 == 'da'):
                for x in myroot.findall('ANGAJAT'):
                    item = x.find('NUME').text
                    item2 = x.find('PRENUME').text
                    item3 = x.find('VARSTA').text
                    item4 = x.find('DATA_ANGAJARE').text
                    item5 = x.find('DEPARTAMENT').text
                    item6 = x.find('SALARIU').text
                    item7 = x.find('ORE').text
                    print(item+' '+item2+', Varsta: '+item3+', D_A: '+item4+', '+item5+', Salariu: '+item6+', Ore: '+item7)

        if (inp == "asociati"):
            inp2 = input("Doriti sa afisati informatii suplimentare? (da,nu): ")
            if (inp2 == 'nu'):
                for x in myroot.findall('ASOCIAT'):
                    item = x.find('NUME').text
                    item2 = x.find('PRENUME').text
                    print(item, item2)
            if (inp2 == 'da'):
                for x in myroot.findall('ASOCIAT'):
                    item = x.find('NUME').text
                    item2 = x.find('PRENUME').text
                    item3 = x.find('VARSTA').text
                    item4 = x.find('DATA_ANGAJARE').text
                    item5 = x.find('DEPARTAMENT').text
                    item6 = x.find('SALARIU').text
                    item7 = x.find('ORE').text
                    print(item+' '+item2+', Varsta: '+item3+', D_A: '+item4+', '+item5+', Salariu: '+item6+', Ore: '+item7)

        if (inp == "departamente"):
            inp2 = input("Doriti sa afisati informatii suplimentare? (da,nu): ")
            if (inp2 == 'nu'):
                for x in myroot2.findall('DEPARTAMENT'):
                    item = x.find('NUME').text
                    print(item)
            if (inp2 == 'da'):
                for x in myroot2.findall('DEPARTAMENT'):
                    item = x.find('NUME').text
                    item2 = x.find('NUME_MANAGER').text
                    item3 = x.find('PRENUME_MANAGER').text
                    item4 = x.find('BUGET').text
                    print(item + ', Manager: ' + item2 + ' ' + item3 + ', Buget: ' + item4)

    if (ans == 'cautare'):
        inp = input('Ce doriti sa cautati? (angajat, asociat, departament): ')
        if (inp == 'angajat'):
            inp2 = input('Dupa ce criteriu doriti sa cautati? (nume, prenume, varsta, d_a, ore): ')
            if (inp2 == 'nume'):
                inp3 = input('Introduceti numele pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('NUME').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'prenume'):
                inp3 = input('Introduceti prenumele pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('PRENUME').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'varsta'):
                inp3 = input('Introduceti varsta pe care doriti sa o cautati: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('VARSTA').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'd_a'):
                inp3 = input('Introduceti data de angajare pe care o cautati: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('DATA_ANGAJARE').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'ore'):
                inp3 = input('Introduceti nr. de ore pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ORE').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")

        if (inp == 'asociat'):
            inp2 = input('Dupa ce criteriu doriti sa cautati? (nume, prenume, varsta, d_a, ore): ')
            if (inp2 == 'nume'):
                inp3 = input('Introduceti numele pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('NUME').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'prenume'):
                inp3 = input('Introduceti prenumele pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('PRENUME').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'varsta'):
                inp3 = input('Introduceti varsta pe care doriti sa o cautati: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('VARSTA').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'd_a'):
                inp3 = input('Introduceti data de angajare pe care o cautati: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('DATA_ANGAJARE').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'ore'):
                inp3 = input('Introduceti nr. de ore pe care il cautati: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ORE').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('PRENUME').text
                        item3 = x.find('VARSTA').text
                        item4 = x.find('DATA_ANGAJARE').text
                        item5 = x.find('DEPARTAMENT').text
                        item6 = x.find('SALARIU').text
                        item7 = x.find('ORE').text
                        print(item + ' ' + item2 + ', Varsta: ' + item3 + ', D_A: ' + item4 + ', ' + item5 + ', Salariu: ' + item6 + ', Ore: ' + item7)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")

        if (inp == 'departament'):
            inp2 = input('Dupa ce criteriu doriti sa cautati? (nume, nume_man, prenume_man): ')
            if (inp2 == 'nume'):
                inp3 = input('Introduceti numele pe care il cautati: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('NUME').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('NUME_MANAGER').text
                        item3 = x.find('PRENUME_MANAGER').text
                        item4 = x.find('BUGET').text
                        print(item + ', Nume Manager: ' + item2 + ' ' + item3 + ', Buget: ' + item4)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'nume_man'):
                inp3 = input('Introduceti numele pe care il cautati: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('NUME_MANAGER').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('NUME_MANAGER').text
                        item3 = x.find('PRENUME_MANAGER').text
                        item4 = x.find('BUGET').text
                        print(item + ', Nume Manager: ' + item2 + ' ' + item3 + ', Buget: ' + item4)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")
            if (inp2 == 'prenume_man'):
                inp3 = input('Introduceti numele pe care il cautati: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('PRENUME_MANAGER').text == inp3):
                        cnt = 1
                        item = x.find('NUME').text
                        item2 = x.find('NUME_MANAGER').text
                        item3 = x.find('PRENUME_MANAGER').text
                        item4 = x.find('BUGET').text
                        print(item + ', Nume Manager: ' + item2 + ' ' + item3 + ', Buget: ' + item4)
                if (cnt == 0):
                    print("Informatia cautata nu a fost gasita.")

    if (ans == 'modificare'):
        inp = input('Ce doriti sa modificati? (angajat, asociat, departament): ')
        if (inp == 'angajat'):
            inp2 = input('Ce doriti sa modificati? (nume, prenume, varsta, d_a, ore, salariu): ')
            if (inp2 == 'nume'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul nume: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('NUME').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'prenume'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul prenume: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('PRENUME').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'varsta'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noua varsta: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('VARSTA').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'd_a'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noua data de angajare: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('DATA_ANGAJARE').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'ore'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul nr. de ore: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('ORE').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'salariu'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul salariu: ')
                cnt = 0
                for x in myroot.findall('ANGAJAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('SALARIU').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")

        if (inp == 'asociat'):
            inp2 = input('Ce doriti sa modificati? (nume, prenume, varsta, d_a, ore, salariu): ')
            if (inp2 == 'nume'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul nume: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('NUME').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'prenume'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul prenume: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('PRENUME').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'varsta'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noua varsta: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('VARSTA').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'd_a'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noua data de angajare: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('DATA_ANGAJARE').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'ore'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul nr. de ore: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('ORE').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'salariu'):
                id = input('Introduceti ID-ul persoanei pe care doriti sa o modificati: ')
                inp3 = input('Introduceti noul salariu: ')
                cnt = 0
                for x in myroot.findall('ASOCIAT'):
                    if (x.find('ID').text == id):
                        cnt = 1
                        x.find('SALARIU').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")

        if (inp == 'departament'):
            inp2 = input('Ce doriti sa modificati? (nume_man, prenume_man, buget): ')
            if (inp2 == 'nume_man'):
                id = input('Introduceti numele departamentului pe care il modificati: ')
                inp3 = input('Introduceti noul nume al managerului: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('NUME').text == id):
                        cnt = 1
                        x.find('NUME_MANAGER').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'prenume_man'):
                id = input('Introduceti numele departamentului pe care il modificati: ')
                inp3 = input('Introduceti noul prenume al managerului: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('NUME').text == id):
                        cnt = 1
                        x.find('PRENUME_MANAGER').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")
            if (inp2 == 'buget'):
                id = input('Introduceti numele departamentului pe care il modificati: ')
                inp3 = input('Introduceti noul buget: ')
                cnt = 0
                for x in myroot2.findall('DEPARTAMENT'):
                    if (x.find('NUME').text == id):
                        cnt = 1
                        x.find('BUGET').text = inp3
                        print('Operatiunea s-a terminat cu succes!')
                if (cnt == 0):
                    print("Operatiunea s-a terminat cu esec.")

    if (ans == 'inserare'):
        inp = input('Ce doriti sa inserati? (angajat, asociat, departament): ')
        if (inp == 'angajat'):
            ET.SubElement(myroot,'ANGAJATNEW')
            nume = input('Nume angajat: ')
            pren = input('Prenume angajat: ')
            varsta = input('Varsta angajat: ')
            d_a = input('Data angajare: ')
            dept = input('Departament: ')
            sal = input('Salariu: ')
            ore = input('Ore: ')
            for x in myroot.iter('ANGAJATNEW'):
                ET.SubElement(x,'ID')
                x.find('ID').text = index
                index += 1
                ET.SubElement(x,'NUME')
                x.find('NUME').text = nume
                ET.SubElement(x, 'PRENUME')
                x.find('PRENUME').text = pren
                ET.SubElement(x, 'VARSTA')
                x.find('VARSTA').text = varsta
                ET.SubElement(x, 'DATA_ANGAJARE')
                x.find('DATA_ANGAJARE').text = d_a
                ET.SubElement(x, 'DEPARTAMENT')
                x.find('DEPARTAMENT').text = dept
                ET.SubElement(x, 'SALARIU')
                x.find('SALARIU').text = sal
                ET.SubElement(x, 'ORE')
                x.find('ORE').text = ore
            myroot.find('ANGAJATNEW').tag = 'ANGAJAT'
        if (inp == 'asociat'):
            ET.SubElement(myroot,'ASOCIATNEW')
            nume = input('Nume asociat: ')
            pren = input('Prenume asociat: ')
            varsta = input('Varsta asociat: ')
            d_a = input('Data angajare: ')
            dept = input('Departament: ')
            sal = input('Salariu: ')
            ore = input('Ore: ')
            for x in myroot.iter('ASOCIATNEW'):
                ET.SubElement(x, 'ID')
                x.find('ID').text = index
                index += 1
                ET.SubElement(x,'NUME')
                x.find('NUME').text = nume
                ET.SubElement(x, 'PRENUME')
                x.find('PRENUME').text = pren
                ET.SubElement(x, 'VARSTA')
                x.find('VARSTA').text = varsta
                ET.SubElement(x, 'DATA_ANGAJARE')
                x.find('DATA_ANGAJARE').text = d_a
                ET.SubElement(x, 'DEPARTAMENT')
                x.find('DEPARTAMENT').text = dept
                ET.SubElement(x, 'SALARIU')
                x.find('SALARIU').text = sal
                ET.SubElement(x, 'ORE')
                x.find('ORE').text = ore
            myroot.find('ASOCIATNEW').tag = 'ASOCIAT'
        if (inp == 'departament'):
            ET.SubElement(myroot2,'DPTNEW')
            nume = input('Nume departament: ')
            nm = input('Nume manager: ')
            pm = input('Prenume Manager: ')
            buget = input('Buget: ')
            for x in myroot2.iter('DPTNEW'):
                ET.SubElement(x,'NUME')
                x.find('NUME').text = nume
                ET.SubElement(x, 'NUME_MANAGER')
                x.find('NUME_MANAGER').text = nm
                ET.SubElement(x, 'PRENUME_MANAGER')
                x.find('PRENUME_MANAGER').text = pm
                ET.SubElement(x, 'BUGET')
                x.find('BUGET').text = buget
            myroot2.find('DPTNEW').tag = 'DEPARTAMENT'

    if (ans == 'stergere'):
        inp = input('Ce doriti sa stergeti? (angajat, asociat, departament): ')
        if (inp == 'angajat'):
            cnt = 0
            id = input("Introduceti ID-ul pe care doriti sa il stergeti: ")
            for x in myroot.findall('ANGAJAT'):
                if (x.find('ID').text == id):
                    cnt = 1
                    myroot.remove(x)
                    print("Stergerea a avut loc cu succes!")
            if (cnt == 0):
                print('Stergerea nu a avut loc.')
        if (inp == 'asociat'):
            cnt = 0
            id = input("Introduceti ID-ul pe care doriti sa il stergeti: ")
            for x in myroot.findall('ASOCIAT'):
                if (x.find('ID').text == id):
                    cnt = 1
                    myroot.remove(x)
                    print("Stergerea a avut loc cu succes!")
            if (cnt == 0):
                print('Stergerea nu a avut loc.')
        if (inp == 'departament'):
            cnt = 0
            id = input("Introduceti numele dept. pe care doriti sa il stergeti: ")
            for x in myroot2.findall('DEPARTAMENT'):
                if (x.find('NUME').text == id):
                    cnt = 1
                    myroot2.remove(x)
                    print("Stergerea a avut loc cu succes!")
            if (cnt == 0):
                print('Stergerea nu a avut loc.')

    if (ans == 'cautare avansata'):
        print("Meniu de optiuni pentru cautare avansata")
        print("Cauta daca o persoana este salariata: 1")
        print("Cauta daca o persoana este lider pentru un departament: 2")
        print("Cauta daca o persoana a lucrat suplimentar: 3")
        print("Cauta daca o persoana lucreaza part-time: 4")
        print("Cauta daca o persoana are cel mai mare salariu: 5")
        inp = input('Alegeti optiunea: ')
        if (inp == '1'):
            inp2 = input('Introduceti numele persoanei: ')
            inp3 = input('Introduceti prenumele persoanei: ')
            cnt = 0
            for x in myroot.findall('ANGAJAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3):
                    cnt = 1
                    print("Persoana cautata este salariat.")
            for x in myroot.findall('ASOCIAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3):
                    cnt = 1
                    print("Persoana cautata este salariat.")
            if (cnt == 0):
                print("Persoana cautata nu este salariat.")
        if (inp == '2'):
            inp2 = input('Introduceti numele persoanei: ')
            inp3 = input('Introduceti prenumele persoanei: ')
            cnt = 0
            for x in myroot2.findall('DEPARTAMENT'):
                if (x.find('NUME_MANAGER').text == inp2 and x.find('PRENUME_MANAGER').text == inp3):
                    cnt = 1
                    print("Persoana cautata este lider de departament.")
            if (cnt == 0):
                print("Persoana cautata nu este lider de departament.")
        if (inp == '3'):
            inp2 = input('Introduceti numele persoanei: ')
            inp3 = input('Introduceti prenumele persoanei: ')
            cnt = 0
            for x in myroot.findall('ANGAJAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3 and int(x.find('ORE').text) > 40):
                    cnt = 1
                    print("Persoana cautata a lucrat suplimentar.")
            for x in myroot.findall('ASOCIAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3 and int(x.find('ORE').text) > 40):
                    cnt = 1
                    print("Persoana cautata a lucrat suplimentar.")
            if (cnt == 0):
                print("Persoana cautata nu a lucrat suplimentar.")
        if (inp == '4'):
            inp2 = input('Introduceti numele persoanei: ')
            inp3 = input('Introduceti prenumele persoanei: ')
            cnt = 0
            for x in myroot.findall('ANGAJAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3 and int(x.find('ORE').text) < 40):
                    cnt = 1
                    print("Persoana cautata lucreaza part-time.")
            for x in myroot.findall('ASOCIAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3 and int(x.find('ORE').text) < 40):
                    cnt = 1
                    print("Persoana cautata lucreaza part-time.")
            if (cnt == 0):
                print("Persoana cautata nu lucreaza part-time.")
        if (inp == '5'):
            inp2 = input('Introduceti numele persoanei: ')
            inp3 = input('Introduceti prenumele persoanei: ')
            cnt = -1
            for x in myroot.findall('ANGAJAT'):
                if (int(x.find('SALARIU').text) > cnt):
                    cnt = int(x.find('SALARIU').text)
            for x in myroot.findall('ASOCIAT'):
                if (int(x.find('SALARIU').text) > cnt):
                    cnt = int(x.find('SALARIU').text)
            for x in myroot.findall('ANGAJAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3):
                    if (int(x.find('SALARIU').text) == cnt):
                        print("Persoana cautata are cel mai mare salariu.")
                    else:
                        print("Persoana cautata nu are cel mai mare salariu.")
            for x in myroot.findall('ASOCIAT'):
                if (x.find('NUME').text == inp2 and x.find('PRENUME').text == inp3):
                    if (int(x.find('SALARIU').text) == cnt):
                        print("Persoana cautata are cel mai mare salariu.")
                    else:
                        print("Persoana cautata nu are cel mai mare salariu.")

    print("==================================================")
    ans = input("Daca doriti sa continuati, introduceti o alta comanda, altfel introduceti x: ")
mytree.write('new.xml')
mytree2.write('new2.xml')