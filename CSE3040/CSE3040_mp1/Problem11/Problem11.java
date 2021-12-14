package Problem11;

class PalindromeChecker{

	
	public static void check(String str){
		int length=str.length();
		boolean checker=true;
		for(int i=0;i<length;i++) {
			int begin=i;
			int end=(length-1)-i;
			if(str.charAt(begin)!=str.charAt(end)) {
				System.out.println(str+" is not a Palindrome.");
				checker=false;
				break;
			}
			
		}
		if(checker)
			System.out.println(str+" is a Palindrome.");
	}
	public static void check(int num) {
		
		int reverse=0;
		int origin=num;
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
