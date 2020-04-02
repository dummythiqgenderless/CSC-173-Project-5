/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Mon Nov 28 14:22:27 EST 2016 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* Circuits_and3() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);
	Gate* and0 = new_AndGate(in0, in1);
	Gate* and1 = new_AndGate(Gate_getOutput(and0), in2);

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(and1);
	Gate** gates = new_Gate_array(2);
	gates[0] = and0;
	gates[1] = and1;
	return new_Circuit(3, inputs, 1, outputs, 2, gates);
}

//Circuit A, following the circuit simulator template above
static Circuit* Circuits_A() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);

	Gate* not0 = new_Inverter(in1);
	Gate* and0 = new_AndGate(in1, in2);
	Gate* and1 = new_AndGate(in0, Gate_getOutput(not0));
	Gate* or0 = new_OrGate(Gate_getOutput(and0), Gate_getOutput(and1));

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(or0);
	Gate** gates = new_Gate_array(4);
	gates[0] = not0;
	gates[1] = and0;
	gates[2] = and1;
	gates[3] = or0;
	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

//Circuit B
static Circuit* CircuitsB() {
	//Circuit has three values = x, y, z

	//x
	Value* in0 = new_Value(false);
	//y
	Value* in1 = new_Value(false);
	//z
	Value* in2 = new_Value(false);


	//Gate for NOT y
	Gate* not0 = new_Inverter(in1);

	//Gate for NAND not y and x
	Gate* NANDyx = new_NandGate(Gate_getOutput(not0), in0);

	//Gate for NAND for y and z
	Gate* NANDyz = new_NandGate(in1, in2);

	//Gate for NOR of the above relations
	Gate* final = new_NorGate(Gate_getOutput(NANDyz), Gate_getOutput(NANDyx));


	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(final);
	Gate** gates = new_Gate_array(4);
	gates[0] = not0;
	gates[1] = NANDyx;
	gates[2] = NANDyz;
	gates[3] = final;
	return new_Circuit(3, inputs, 1, outputs, 4, gates);
}

static Circuit* Circuits_C() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);

	Gate* andA = new_AndGate(in0, in1);
	Gate* notB = new_Inverter(in0);
	Gate* notC = new_Inverter(in1);
	Gate* andD = new_AndGate(Gate_getOutput(notB), Gate_getOutput(notC));
	Gate* orE = new_OrGate(Gate_getOutput(andA), Gate_getOutput(andD));

	Value** inputs = new_Value_array(2);
	inputs[0] = in0;
	inputs[1] = in1;
	Value** outputs = new_Value_array(1);
	outputs[0] = Gate_getOutput(orE);
	Gate** gates = new_Gate_array(5);
	gates[0] = andA;
	gates[1] = notB;
	gates[2] = notC;
	gates[3] = andD;
	gates[4] = orE;
	return new_Circuit(2, inputs, 1, outputs, 5, gates);

}

static Circuit* Circuits_oneBitAdder() {
	Value* in0 = new_Value(false);
	Value* in1 = new_Value(false);
	Value* in2 = new_Value(false);

	Gate* not0 = new_Inverter(in0);
	Gate* not1 = new_Inverter(in1);
	Gate* not2 = new_Inverter(in2);

	Gate* and0 = new_And3Gate(Gate_getOutput(not0), Gate_getOutput(not1), in2);
	Gate* and1 = new_And3Gate(Gate_getOutput(not0), in1, Gate_getOutput(not2));
	Gate* and2 = new_And3Gate(Gate_getOutput(not0), in1, in2);
	Gate* and3 = new_And3Gate(in0, Gate_getOutput(not1), Gate_getOutput(not2));
	Gate* and4 = new_And3Gate(in0, Gate_getOutput(not1), in2);
	Gate* and5 = new_And3Gate(in0, in1, Gate_getOutput(not2));
	Gate* and6 = new_And3Gate(in0, in1, in2);

	Gate* orZ = new_Or4Gate(Gate_getOutput(and0), Gate_getOutput(and1), Gate_getOutput(and3), Gate_getOutput(and6));
	Gate* orD = new_Or4Gate(Gate_getOutput(and2), Gate_getOutput(and4), Gate_getOutput(and5), Gate_getOutput(and6));

	Value** inputs = new_Value_array(3);
	inputs[0] = in0;
	inputs[1] = in1;
	inputs[2] = in2;
	Value** outputs = new_Value_array(2);
	outputs[0] = Gate_getOutput(orD);
	outputs[1] = Gate_getOutput(orZ);
	Gate** gates = new_Gate_array(12);
	gates[0] = not0;
	gates[1] = not1;
	gates[2] = not2;
	gates[3] = and0;
	gates[4] = and1;
	gates[5] = and2;
	gates[6] = and3;
	gates[7] = and4;
	gates[8] = and5;
	gates[9] = and6;
	gates[10] = orZ;
	gates[11] = orD;
	return new_Circuit(3, inputs, 2, outputs, 12, gates);
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	//Circuit_dump(circuit);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}


/**
* Returns an array representing a binary tupleNumber
* index refers to the current iteration of which row of a truth table we are looking at
* k i the number of arguments (number of binary digits);
*/
static void binaryDigit(int* val, int index, int k) {
	for(int i = 0; i < k; i++) {
		// >> is bitwise shift right i times
		// this gets us each binary combination for truth table arguments
		val[k-i-1] = (index >> i) & 1;
	}
}

static void testCircuit(Circuit* c) {
	int k = Circuit_numInputs(c);
	int numOutputs = 1;
	for(int i = 0; i< k; i++) {
		numOutputs = numOutputs * 2;
	}
	for(int i = 0; i < numOutputs; i++) {
		//BinaryNum n = toBinary(i, k);
		int binary[k];
		binaryDigit(binary, i, k);
		for(int j = 0; j < k; j++) {
			Circuit_setInput(c, j, binary[j]);
			printf("%s ", b2s(binary[j]));
		}
		Circuit_update(c);
		printf("-> ");

		for(int h = 0; h < Circuit_numOutputs(c); h++){
			printf("%s ", b2s(Circuit_getOutput(c, h)));
		}
		printf("\n");
	}

}


int main(int argc, char **argv) {
	Circuit* circuit = Circuits_and3();
	printf("Some input(s) false: should be false\n");
	test3In1Out(circuit, true, true, false);
	printf("All inputs true: should be true\n");
	test3In1Out(circuit, true, true, true);

	Circuit* a = Circuits_A();
	Circuit* b = CircuitsB();
	Circuit* c = Circuits_C();
	Circuit* adder = Circuits_oneBitAdder();

	printf("\nCircuir A: \n");
	testCircuit(a);

	printf("\nCircuit B: \n");
	testCircuit(b);

	printf("\nCircuit C: \n");
	testCircuit(c);

	printf("\nOne bit adder (x y c -> d z): \n");
	testCircuit(adder);
}
