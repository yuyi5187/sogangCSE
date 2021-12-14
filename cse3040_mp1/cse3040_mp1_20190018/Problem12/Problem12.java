package Problem12;

class SubsequenceChecker{
	public static void check(String str,String str2){
		int n=str2.length();
		int n2=str.length();
		int list[]=new int [n];
		int index=0;;
		for(int i=0;i<n2;i++) {
			if(str.charAt(i)==str2.charAt(index)) {
				list[index]=i;
				index++;
			}
			if(index==n2)
				break;
				
		}
		if(index==n) {
			System.out.println(str2+ "is a subsequence of "+str);
			for(int i=0;i<n;i++) 
				System.out.print(list[i]+" ");
			System.out.println();
				
		}
		else 
			System.out.println(str2+" is not a subsequence of"+ str);
			
	}
}

public class Problem12 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SubsequenceChecker.check("supercalifragilisticexpialidocious", "pads"); 
		SubsequenceChecker.check("supercalifragilisticexpialidocious", "padsx");

	}

}
