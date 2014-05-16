package cs429;

/* instruction encoding
 * 
 * 0 00000 00    halt  ---
 * 
 * 0 00011 dd    jle dd    
 * 0 00110 dd    outch dd  ---
 * 0 00111 dd    show dd   ---
 * 0 01000 dd    ldi dd    ---
 * 
 * 
 * 1 000 ss dd   add ss,dd  ---
 * 1 011 ss dd   cmp ss,dd  ---
 * 
 */

//how much do we need to add to the pc when we jump?

public class Simulator {

	/*Our registers*/
	public static byte R0 = 0;  //00
	public static byte R1 = 0;  //01
	public static byte R2 = 0;  //10
	public static byte R3 = 0;  //11
	public static Integer result = 0;


	public static boolean DEBUG = false;

	public static void debug(String msg, Object... args) {
		if (DEBUG) {
			System.out.printf(msg, args);
		}
	}

	public static void outch(byte val) {
		System.out.printf("%c", val);
	}

	public static void show(int reg, byte val) {
		System.out.printf("reg[%d] = %d 0x%x\n", reg, val, val);
	}

	public static byte run(byte mem[]) {

		/*Variables*/
		String y;
		byte register1 = 0;
		byte register2 = 0;
		int registerNum = 0;
		boolean validInstruction = false;
		for (int i = 0; i < mem.length; i ++){


			/*Convert our Integer into a binary String*/
			y = Integer.toBinaryString(mem[i]& 0xff);

			/*Our halt instruction*/
			if (Integer.valueOf(y).equals(0))
				return (byte) i;

			/*Determine which register we're dealing with*/
			if ((y.charAt(y.length()-1) == '0')){	
				if (y.charAt(y.length()-2) == '0'){
					register1 = R0;
					registerNum = 0;}
				else{
					register1 = R2;
					registerNum = 2;}}
			if ((y.charAt(y.length()-1) == '1')){
				if (y.charAt(y.length()-2) == '0'){
					register1 = R1;
					registerNum = 1;}
				else{
					register1 = R3;
					registerNum = 3;}}


			/*Check if it's an add/cmp and set up the registers*/
			if (y.length() == 8){
				if ((y.charAt(y.length()-3) == '0')){	
					if (y.charAt(y.length()-4) == '0')
						register2 = R0;
					else
						register2 = R2;}
				if ((y.charAt(y.length()-3) == '1')){
					if (y.charAt(y.length()-4) == '0')
						register2 = R1;
					else
						register2 = R3;}

				/*Our instructions for an add*/
				if ((y.charAt(y.length()-8) == '1')  && (y.charAt(y.length()-7) == '0') && (y.charAt(y.length()-6) == '0') && (y.charAt(y.length()-5) == '0')){
					validInstruction = true;
					if ((y.charAt(y.length()-1) == '0')){	

						/*Pick the register*/
						if (y.charAt(y.length()-2) == '0')
							R0 = (byte) (R0 + register2);
						else
							R2 = (byte) (R2 + register2);}
					if ((y.charAt(y.length()-1) == '1')){
						if (y.charAt(y.length()-2) == '0')
							R1 = (byte) (R1 + register2);
						else
							R3 = (byte) (R3 + register2);}

				}

				/* Our instructions for a cmp*/
				if ((y.charAt(y.length()-8) == '1')  && (y.charAt(y.length()-7) == '0') && (y.charAt(y.length()-6) == '1') && (y.charAt(y.length()-5) == '1')){
					validInstruction = true;
					result = register1 - register2;}}


			/*Check if it's a movi*/
			if (y.length() > 5){
				if ((y.charAt(y.length()-6) == '1')){	
					if ((y.charAt(y.length()-3) == '0')  && (y.charAt(y.length()-4) == '0') && (y.charAt(y.length()-5) == '0')){
						validInstruction = true;
						/*Pick the register*/
						if ((y.charAt(y.length()-1) == '0')){	
							if (y.charAt(y.length()-2) == '0')
								R0 = mem[i+1];
							else
								R2 = mem[i+1];}
						if ((y.charAt(y.length()-1) == '1')){
							if (y.charAt(y.length()-2) == '0')
								R1 = mem[i+1];
							else
								R3 = mem[i+1];}
						i++;}}}


			if (y.length() > 4){
				if ((y.charAt(y.length()-5) == '1')){	
					/* Is it a show?*/
					if ((y.charAt(y.length()-4) == '1')  && (y.charAt(y.length()-3) == '1')){
						validInstruction = true;

						/*Pick the register*/
						if ((y.charAt(y.length()-1) == '0')){	
							if (y.charAt(y.length()-2) == '0')
								show(registerNum, R0);
							else
								show(registerNum, R2);}
						if ((y.charAt(y.length()-1) == '1')){
							if (y.charAt(y.length()-2) == '0')
								show(registerNum, R1);
							else
								show(registerNum, R3);}
					}
					/*Is it an outch?*/
					if ((y.charAt(y.length()-4) == '1')  && (y.charAt(y.length()-3) == '0')){
						validInstruction = true;

						/*Pick the register*/
						if ((y.charAt(y.length()-1) == '0')){	
							if (y.charAt(y.length()-2) == '0')
								outch(R0);
							else
								outch(R2);}
						if ((y.charAt(y.length()-1) == '1')){
							if (y.charAt(y.length()-2) == '0')
								outch(R1);
							else
								outch(R3);}}}}

			/*Is it a jle instruction?*/
			if (y.length() == 4){
			if ((y.charAt(y.length()-4) == '1') && (y.charAt(y.length()-3) == '1') ){	
					validInstruction = true;
					if (result <= 0){
						if ((y.charAt(y.length()-1) == '0')){	
							if (y.charAt(y.length()-2) == '0')
								i = (R0 - 1);
							else
								i = (R2 - 1);}
						if ((y.charAt(y.length()-1) == '1')){
							if (y.charAt(y.length()-2) == '0')
								i = (R1 - 1);
							else
								i = (R3 - 1);}}}}

			if (validInstruction == false)
				return (byte) i;}

		return 0;
	}

}
