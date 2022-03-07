`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:12:03 11/08/2021 
// Design Name: 
// Module Name:    square_root 
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
//pentru implementare a fost ales algoritmul CORDIC ce se bazeaza pe adunare, inmultire si verificare
module square_root (
    output [15:0] out,
    input  [7:0] in );

	 reg [31:0] baza; //se stabileste dimensiunea bazei (avand in vedere ca vom shifta intrarea, luam o baza mare, minim de ordinul out-ului, adica 2^15
	 reg [15:0] y; //luam o variabila ajutatoare pentru calcului radicalului, aceasta variabila va fi atribuita in out
	 
	 reg [31:0] in2; //varriabila ajutatoare de dimensiune minima in+out, deoarece aici vom shifta input-ul astfel incat sa obtinem outputul cerut
	 
	 reg signed [7:0] i; //variabila folosita in bucla for
	 
	 always @(*) begin
		baza = 32768; //initializam baza cu 2^15
		y = 0; //initializam rezultatul cu 0
		in2 = in << 16; //initializam variabila ajutatoare pentru input cu in shiftat de 16 ori la stanga, deoarece pentru fiecare
		//doua shiftari la stanga ale inputului, rezultatul va fi shiftat o data
		for (i = 0; i <= 15; i = i + 1) begin
			y = y + baza; //se aduna baza la rezultat
			if ((y * y) > in2 ) begin //se verifica daca rezultatul este mai mare decat inputul
				y = y - baza; //in caz afirmativ, baza se scade din rezultat
			end
			baza = baza >> 1; //baza este shiftata la dreapta pentru a o injumatati (din aproape in aproape se va obtine rezultatul)
		end
	 end
	assign out = y; //se atribuie valoarea output-ului
endmodule
