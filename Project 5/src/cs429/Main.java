package cs429;

public class Main {

	public static void doit(String name, int... prog) {
		final byte[] memory = new byte[prog.length];
		for (int i = 0; i < prog.length; i++) {
			memory[i] = (byte) prog[i];
		}
		System.out.printf("\n::: running %s :::\n", name);
		byte pc = Simulator.run(memory);
		System.out.printf("\nterminated at pc = %d\n",pc);
	}

	public static void main(String args[]) {

		doit("t0", 32, 104, 24, 32, 101, 24, 32, 108, 24, 32, 108,
			24, 32, 111, 24, 32, 10, 24, 0);

		doit("t1", 33, 10, 29, 34, 20, 30, 134, 30, 0);

		doit("t2", 33, 10, 32, 5, 28, 29, 34, 12, 177, 14, 29, 0,
				28, 0);

		doit("t3", 33, 10, 32, 5, 28, 29, 34, 12, 177, 14, 28, 0,
				29, 0);

	}

}
