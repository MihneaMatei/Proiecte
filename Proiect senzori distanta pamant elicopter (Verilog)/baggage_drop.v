`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:42:37 11/12/2021 
// Design Name: 
// Module Name:    baggage_drop 
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
module baggage_drop (
    output   [6 : 0]   seven_seg1, 
    output   [6 : 0]   seven_seg2,
    output   [6 : 0]   seven_seg3,
    output   [6 : 0]   seven_seg4,
    output   [0 : 0]   drop_activated,
    input    [7 : 0]   sensor1,
    input    [7 : 0]   sensor2,
    input    [7 : 0]   sensor3,
    input    [7 : 0]   sensor4,
    input    [15: 0]   t_lim,
    input              drop_en);
	 
	 wire [7:0] h; //declar variabila ajutatoare pentru inaltime, variabila coresp. out-ului de la modulul
	 //de sensors_input si variabila de intrare pentru modulul square_root
	 wire [15:0] radacina; //declar var. aux. pentru valoarea radacinii patrate a inaltimii; aceasta var. este
	 //output al modulului square_root si input al procesului de prelucrare intermediara a t_act
	 wire [15:0] timp_act; //var. aux. pentru t_act => out pt prelucrarea interm. si in pentru display_and_drop
	 
	 sensors_input mod1(h, sensor1, sensor2, sensor3, sensor4); //se instantiaza modulul 1, cel pentru senzori
	 
	 square_root mod2(radacina, h); //se instantiaza modulul 2, pentru radacina patrata
	 
	 assign timp_act = radacina >> 1; //prelucrez radacina dupa formula primita si o atribui variabilei aux. coresp.
	 
	 //instantiez modulul pentru afisare si output.
	 display_and_drop mod3(seven_seg1, seven_seg2, seven_seg3, seven_seg4, drop_activated, timp_act, t_lim, drop_en);
	 
endmodule
