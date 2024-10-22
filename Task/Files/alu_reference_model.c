// Author: Noman Rafiq
// Dated: Oct 21, 2024

#include <svdpi.h>

void alu_reference_model(const svLogicVecVal* A, 
                         const svLogicVecVal* B, 
                    	 const svLogicVecVal* ALU_Sel,
                         svLogicVecVal* ALU_Out,
                         svLogic* Carry_Out) {
    
  // Type-Cast values to 8-bit vectors
  unsigned char a = (A->aval) & 0xFF;
  unsigned char b = (B->aval) & 0xFF;
  unsigned char select = (ALU_Sel->aval) & 0xF;	// Use only last 4-bits
  unsigned char result;
  
//	printf("a = %0d, b = %0d, select = %0d, A->aval = %0d, B->aval = %0d", a, b, select, A->aval, B->aval);
  
  switch(select) {
    
    // ADD CASE
    case 0:
    result	= a + b;
    *Carry_Out	= (result < a)? 1:0; 

    //     printf("A = %0d, B = %0d, ALU_Out(ADD) = %0d\n", A, B, ALU_Out);

    //     printf("C Side :: Select = %0d\n", select);
    break;
    
    // SUB CASE
    case 1:
    result	= a - b;
    *Carry_Out	= (result > a)? 1:0;
    break;
    
    // MULT CASE
    case 2:
    result		= a * b;
    *Carry_Out	= 0;
    break;
    
    // DIV CASE
    case 3:
    result		= (b != 0) ? a / b : 0;
    *Carry_Out	= 0;
    break;
        
    // Left-Shift CASE
    case 4:
    result		= a << 1;
    *Carry_Out	= (a & 0x80)? 1:0;
    break;
    
    // Right-Shift CASE
    case 5:
    result		= a >> 1;
    *Carry_Out	= (a & 0x01)? 1:0;
    break;
    
    // Rotate-Left CASE
    case 6:
    result		= (a << 1) | (a >> 7);
    *Carry_Out	= 0;
    break;
    
    // Rotate-Right CASE
    case 7:
    result		= (a >> 1) | (a << 7);
    *Carry_Out	= 0;
    break;
    
    // AND CASE
    case 8:
    result		= a & b;
    *Carry_Out	= 0;
    break;
    
    // OR CASE
    case 9:
    result		= a | b;
    *Carry_Out	= 0;
    break;
    
    // XOR CASE
    case 10:
    result		= a ^ b;
    *Carry_Out	= 0;
  	break;
    
    // NOR CASE
    case 11:
    result		= ~(a | b);
    *Carry_Out	= 0;
    break;
    
    // NAND CASE
    case 12:
    result		= ~(a & b);
    *Carry_Out	= 0;
    break;
    
    // XNOR CASE
    case 13:
    result		= ~(a ^ b);
    *Carry_Out	= 0;
    break;
    
    // Greater CASE
    case 14:
    result		= (a > b) ? 1:0;
    *Carry_Out	= 0;
    break;
    
    // Equal CASE
    case 15:
    result		= (a == b) ? 1:0;
    *Carry_Out	= 0;
    break;
    
    default:
    result		= a + b;
    *Carry_Out	= (result < a)? 1:0;
    break;
  }
  
  // Assign values to Actual variable
  ALU_Out->aval = result;
  ALU_Out->bval = 0;
  
//   printf("result = %0d", result);
  
}
