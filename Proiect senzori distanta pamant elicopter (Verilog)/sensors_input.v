`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:14:25 11/07/2021 
// Design Name: 
// Module Name:    sensors_input 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module sensors_input (
   output   [7 : 0]   height,
   input    [7 : 0]   sensor1,
   input    [7 : 0]   sensor2,
   input    [7 : 0]   sensor3,
   input    [7 : 0]   sensor4);
	
	reg [15:0] hh; //declar variabila cu care voi lucra in ciclul repetitiv. aceasta are un nr mai mare de biti 
	//deoarece exista o mare posibilitate ca suma senzorilor sa depaseasca 8 biti
	always @(*)begin
		hh = 0; //initializam variabila ajutatoare pentru inaltime cu 0 pentru a nu se lucra cu val precedente
		if (sensor1!=0 && sensor2!=0 && sensor3!=0 && sensor4!=0) begin //verific existenta vreunei valori de 0 la senzori
			hh = (sensor1 + sensor2 + sensor3 + sensor4); //se calculeaza suma tuturor senzorilor
			if (hh[0] && hh[1]) begin //se verifica daca restul impartirii nr la 4 ar fi 3
				hh = hh + 1; //in caz afirmativ, pentru a rotunji de la .75, adaugam 2 pentru a imparti rotund la 4
			end else if (!hh[0] && hh[1]) begin //se verifica daca restul este 2
				hh = hh + 2; //in caz afirmativ pentru a rotunji de la .5, adaugam 2 pentru a imparti rotund la 4
			end
			hh = hh >> 2; //se shifteaza la dreapta cu puterea 2 a lui 2 pentru a obtine impartire la 4
		end else if (sensor1 == 0 || sensor3 == 0) begin //verific perechea 1 de senzori
			hh = (sensor2 + sensor4); //se calculeaza suma celeilalte perechi de senzori
			if (hh[0]) begin //in cazul in care suma este reprezentata de un numar impar, numarul va fi incrementat cu 1 pentru
			//a rotunji prin adaos
				hh = hh + 1;
			end
			hh = hh >> 1; //se shifteaza la dreapta cu puterea 1 a lui 2 pentru a obtine impartire la 2
		end else if (sensor2 == 0 || sensor4 == 0) begin //se verifica perechea 2 de senzori
			hh = (sensor1 + sensor3); //se calculeaza suma celeilalte perechi
			if (hh[0]) begin //in cazul in care suma este reprezentata de un numar impar, numarul va fi incrementat cu 1 pentru
			//a rotunji prin adaos
				hh = hh + 1;
			end
			hh = hh >> 1; //se shifteaza la dreapta cu puterea 1 pentru a obtine impartire la 2
		end
	end
	
	assign height = hh; //se atribuie valoarea pentru output		
endmodule
