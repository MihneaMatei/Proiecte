function [Root,index] = Muller(Coeff)

%INPUT: Coeff - vectorul cu coeficientii polinomului

%OUTPUT: Root - vectorul cu radacinile obtinute
        %index - numarul de valori obtinute

%START%

tol = 1e-10; %stabilim acuratetea pana la care se calculeaza
index = 0; %indexul nr radacinilor
bec = 1; %variabila utilizata ca ajutor pentru continuarea algoritmului

%se vor aborda mai intai cazurile simple, cand ecuatia are grad cel mult 1
%si exista solutii usor de calculat

%Desi algoritmul lui Muller se refera la polinoame cu grad >=3, acest
%algoritm ruleaza si pentru grade mai mici

while (bec)
    [~,c] = size(Coeff); %introducem intr-o nr de coloane ale vectorului Coeff
    if (c == 1) %in cazul in care exista un singur coeficient, se renunta la algoritm
        bec = 0;
        break
    elseif (c == 2) %in cazul ecuatiei de grad 1, se va calcula manual solutia
            bec = 0;
            index = index + 1;
            Root(index) = -Coeff(2)/Coeff(1);
            break
    elseif (c >= 3) %in cazul ec cu grad>=2, se va folosi algoritmul lui Muller
                %se vor introduce 3 valori initiale, presupuse de
                %utilizator, cu ajutorul carora se va trasa parabola
                %necesara rezolvarii ecuatiei
                val = input('Dati 3 valori pentru punctele presupuse [x0 x1 x2]: ');
                if isempty(val)
                    val = [1 2 3]; %in cazul in care nu se dau valori, vor fi folosite aceste
                    %3 valori
                end
                %vom folosi functia polyval pt calculul valorii polinomului
                %in diferite puncte
                for i = 1:100 %consideram ca trebuie sa gasim o radacina in 100 de iteratii
                    q1 = val(2)-val(1); %acesta reprezinta numitorul variabilei q descrisa
                    q2 = val(3)-val(2); %numaratorul variabilei q
                    Q = q2/q1;
                    d1 = (polyval(Coeff,val(2))-polyval(Coeff,val(1)))/q1; %var d1 si d2 sunt variabile ajutatoare
                    d2 = (polyval(Coeff,val(3))-polyval(Coeff,val(2)))/q2; %folosite pentru a calcula A, B si C
                    C = (d2-d1)/(q1+q2); %se calculeaza valoarea lui C
                    A = polyval(Coeff,val(3)); %se calculeaza valoarea lui A
                    B = d2 + q2*C; %se calculeaza valoarea lui B
                    Delta = sqrt(B^2-4*A*C); %se calculeaza radicalul numitorului lui x(i+1)
                    if (abs(B-Delta) < abs(B+Delta)) %se calculeaza numitorul lui x(i+1)
                        E = B + Delta;
                    else E = B - Delta;
                    end
                    x = (-2)*A/E; %se calculeaza x(i+1)
                    p = val(3) + x; %se obtine valoarea radacinii
                    if (abs(x) < tol) %se verifica daca radacina este in limitele de toleranta
                        %Pr = [1 -p]; %se calculeaza ecuatia a carei solutii o cunoastem
                        index = index + 1; %crestem numarul de solutii gasite
                        Root(index) = p; %introducem valoarea radacinii in vectorul cu radacini
                        disp('S-a gasit radacina');
                        break;
                    else val = [val(2) val(3) p]; %actualizam valorile ghicite in cazul in care nu s-a gasit o radacina
                        % in limitele de toleranta
                    end
                    if (i == 99) %in cazul depasirii numarului maxim de iteratii, afisam un mesaj corespunzator
                        disp('Nu s-a gasit radacina');
                    end
                end
    end
    [Coeff,rem] = deconv(Coeff,[1 -p]); %calculam polinomul obtinut prin impartirea polinomului initial 
    %coeff la ecuatia a carei solutii o cunoastem pentru a reduce gradul
    %acestuia si salvam in variabila rem restul acestei impartiri
    Coeff;
end

%END

end
                    