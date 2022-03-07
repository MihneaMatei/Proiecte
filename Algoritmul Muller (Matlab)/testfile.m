disp('Polinomul introdus va fi de forma Coeff[1]x^n + Coeff[2]x^(n-1) + ... + Coeff[n]x^0');
disp('Introduceti coef. ca vector; de ex. [ 1 2 3 ...]');
%%Coeff = input('Introduceti coeficientii sub forma aratata mai sus: ');
Coeff=randn(1,7);
x = -10:0.1:10;
plot(x,polyval(Coeff,x));
[Root,index]=Muller(Coeff);

disp(['Exista ' num2str(index) ' radacini: ']);
for i = 1:index
    disp(['Radacina ' num2str(i) '  este ' num2str(Root(i)) ' .'])
end



