`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:41:31 12/01/2021 
// Design Name: 
// Module Name:    maze 
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
module maze(
input 		          clk,
input [maze_width - 1:0]  starting_col, starting_row, 	// indicii punctului de start
input  			  maze_in, 			// ofera informa?ii despre punctul de coordonate [row, col]
output reg [maze_width - 1:0] row, col,	 		// selecteaza un rând si o coloana din labirint
output reg			  maze_oe,			// output enable (activeaza citirea din labirint la rândul ?i coloana date) - semnal sincron	
output reg			  maze_we, 			// write enable (activeaza scrierea în labirint la rândul ?i coloana date) - semnal sincron
output reg			  done		 	// ie?irea din labirint a fost gasita; semnalul ramane activ 
);

parameter maze_width = 6;

reg [maze_width:0] cr, cc; //folosim copii ale variabilelor pt rand si coloana
reg [1:0] dir; //variabila pentru retinerea directiei: 0-dreapta, 1-sus, 2-stanga, 3-jos
//a se retine ca directiile au fost gandite privind labirintul de sus, ca pe o harta

reg [7:0] state, next_state ; //variabile pentru starile automatului

always @(posedge clk) begin //pe tactul ceasului se verifica daca algoritmul continua (nu s-a gasit iesirea)
	if(done == 0)
		state <= next_state; //in cazul in care algoritmul continua, trecem la starea urmatoare
end

always @(*) begin
	next_state = 0; 
	maze_oe = 0; //deocamdata nu se citeste si nu se scrie nimic
	maze_we = 0;
	done = 0;
	case(state)
		0: begin //starea initiala
			row = starting_row; //initializam atat var pentru rand si col, cat si copiile acestora
			col = starting_col;
			cr = row;
			cc = col;
			maze_we = 1; //activam scrierea, pentru ca stim ca ne aflam in 0
			dir = 0; //incercam prima data in dreapta (right-hand follow)
			next_state = 1;
		end
		
		1: begin //starea in care se efectueaza miscarea si citirea de pe noua pozitie
			if (dir == 0) begin //verificam directia in care am stabilit ca mergem si, dupa caz, incrementam/decrementam variabila aferenta
				col = col + 1;
			end else if (dir == 1) begin
				row = row - 1;
			end else if (dir == 2) begin
				col = col - 1;
			end else begin
				row = row + 1;
			end
			maze_oe = 1; //citim ce se afla pe noua pozitie
			next_state = 2;
		end
		
		2: begin //stare in care se verifica ce valoare are pozitia pe care am ajuns
			if (maze_in == 1) begin //daca am ajuns pe 1
				col = cc; //revin pe coordonatele anterioare
				row = cr;
				case(dir) //se schimba directia pentru urmatoarea parcurgere
					0: dir = 1;
					1: dir = 2;
					2: dir = 3;
					3: dir = 0;
				endcase
				next_state = 1; //revin in starea in care efectuez miscarea omuletului
			end else if (maze_in == 0) begin //daca ajung pe 0
				if (col == 0 || row == 0 || col == 63 || row == 63) begin //verific daca ma aflu pe vreo margine
					maze_we = 1;
					next_state = 99;
				end else begin
					maze_we = 1; //scriu 2 pe aceasta pozitie
					cc = col; //retin noile coordonate
					cr = row;
					case(dir) //pentru a urmari in continuare regula mainii drepte, decrementam cu 1 unit. directia, deoarece, cum pentru cazul
						0: dir = 3; //exemplului de pe site, daca directia de verificat ar ramane aceeasi, path ul omuletului nu ar mai urmari
						1: dir = 0; //mereu peretele din dreapta lui
						2: dir = 1;
						3: dir = 2;
					endcase
					next_state = 1;
				end
			end
		end
		
		99: begin //starea in care done devine 1 pentru ca am ajuns pe margine
			done = 1;
		end
		
		default: ;
	endcase
end

endmodule
