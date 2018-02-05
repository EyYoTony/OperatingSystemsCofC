public class BinaryParity {
    private static final String[] PARITY = {"EVEN", "ODD"};

    // using recursion, count the number of one bits in val
    public static int count_bits(int val) {
	if (val == 0)   // base case
	    return 0;   // number is zero, so return 0 for the 1 bit count

	if (val % 2 == 0)              // if last bit is a 0...
	    return count_bits(val/2);  // divide val by 2 and recurse

	// otherwise, (last bit is a 1), divide val by 2, recurse and add 1
	return count_bits(val/2)+1;
    }

    public static void main(String[] args) {
	if (args.length < 1 || Integer.parseInt(args[0]) < 0) {
	    System.out.print("USAGE: java BinaryParity non-negative-integer\n");
	    return;
	}

	int val = Integer.parseInt(args[0]);
	int n = count_bits(val);
	// n divide by 2 == 0 implies even
	System.out.println("The number "+val+" has "+PARITY[n%2]+" parity");
    }  // end main
}  // end Pangram class
