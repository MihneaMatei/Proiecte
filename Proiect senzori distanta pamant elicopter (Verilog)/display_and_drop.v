`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:24:39 11/12/2021 
// Design Name: 
// Module Name:    display_and_drop 
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
module display_and_drop (
    output   [6 : 0]   seven_seg1, 
    output   [6 : 0]   seven_seg2,
    output   [6 : 0]   seven_seg3,
    output   [6 : 0]   seven_seg4,
    output   [0 : 0]   drop_activated,
    input    [15: 0]   t_act,
    input    [15: 0]   t_lim,
    input              drop_en);
	 
	 reg [6:0] seg1; //am declarat 4 variabile auxiliare cu care vom lucra in always pentru cei 4 7-seg
	 reg [6:0] seg2;
	 reg [6:0] seg3;
	 reg [6:0] seg4;
	 reg [0:0] drop; //am declarat o variabila auxiliara pentru drop_activated, pentru o modificare mai usoara in always
	 
	 always @(*) begin
		drop = 0; //am initializat variabila auxiliara pentru drop cu 0, deoarece in 3 din 4 cazuri aceasta ramane 0
		if ((t_act < t_lim) && (!drop_en)) begin //verific indeplinirea conditiei pentru timp si neindeplinirea celei pentru drop => cold
			seg1 = 7'b0111001; //segmentul 1 afiseaza C
			seg2 = 7'b1011100; //segmentul 2 afiseaza O
         seg3 = 7'b0111000; //segmentul 3 afiseaza L
         seg4 = 7'b1011110; //segmentul 4 afiseaza D
		end else if ((t_act < t_lim) && (drop_en)) begin //verific indep. conditiei pentru timp si indeplinirea cond. pt drop => drop
			drop = 1; //variabila auxiliara pentru drop_activated se modifica in 1
			seg1 = 7'b1011110; //segmentul 1 afiseaza D
         seg2 = 7'b1010000; //segmentul 2 afiseaza R
         seg3 = 7'b1011100; //segmentul 3 afiseaza O
         seg4 = 7'b1110011; //segmentul 4 afiseaza P
		end else if ((t_act > t_lim) && (drop_en)) begin //se verifica indeplinirea conditiilor pentru cazul HOT
			seg1 = 7'b0000000; //segmentul 1 afiseaza spatiu gol
			seg2 = 7'b1110110; //segmentul 2 afiseaza H
         seg3 = 7'b1011100; //segmentul 3 afiseaza O
         seg4 = 7'b1111000; //segmentul 4 afiseaza T
		end else begin //in cazul in care nici conditia de timp, nici cea de drop nu este indeplinita => COLD
			seg1 = 7'b0111001; //segmentul 1 afiseaza C
			seg2 = 7'b1011100; //segmentul 2 afiseaza O
         seg3 = 7'b0111000; //segmentul 3 afiseaza L
         seg4 = 7'b1011110; //segmentul 4 afiseaza D
		end
	 end
	 
	 //prin atribuire continua, se introduc in variabilele de output pentru segmenti cele memorate mai sus
	 assign seven_seg1 = seg1;
	 assign seven_seg2 = seg2;
	 assign seven_seg3 = seg3;
	 assign seven_seg4 = seg4;
	 assign drop_activated = drop; //se atribuie si valoarea retinuta in variabila auxiliara drop
	 
endmodule
