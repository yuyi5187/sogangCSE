package Problem11;

class PalindromeChecker{
	private static boolean checker;
	private static int length;
	private static int reverse;
	private static int origin;
	
	public static void check(String str){
		length=str.length();
		checker=true;
		for(int i=0;i<length;i++) {
			if(str.charAt(i)!=str.charAt((length-1)-i)) {
				System.out.println(str+" is not a Palindrome.");
				checker=false;
				break;
			}
			
		}
		if(checker)
			System.out.println(str+" is a Palindrome.");
	}
	public static void check(int num) {
		reverse=0;
		origin=num;
	    int num2;
		while (num!=0) {
			num2=num%10;
			reverse=reverse*10+num2;
			num=num/10;
		}
		
		if(origin==reverse)
			System.out.println(origin+" is a Palindrome.");
		else {
			System.out.println(origin+" is not a Palindrome.");
		}
			
	}
	
	
}

public class Problem11 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		PalindromeChecker.check("abcde");
		PalindromeChecker.check("abcba");
		PalindromeChecker.check(1234); 
		PalindromeChecker.check(12321);

	}

}
