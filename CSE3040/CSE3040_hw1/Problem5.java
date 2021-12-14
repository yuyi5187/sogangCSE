package hw1_20190018;

import java.util.Scanner;

public class Problem5 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int []x=new int [5];
		System.out.println("Enter exam scores of each student ");
		
		for (int i=0;i<5;i++) {
			Scanner in= new Scanner(System.in);
			System.out.print("Score of student "+(i+1)+": ");
			int n=in.nextInt();
			x[i]=n;
		}
		
		int max=x[0];
		int maxIndex=1;
		int maxTwo=max;
		int maxtwoIndex=maxIndex;
		
		for(int i=0;i<5;i++) {
			if(max<x[i]) {
				maxTwo=max;
				maxtwoIndex=maxIndex;
				max=x[i];
				maxIndex=i+1;
			}
			else if(maxTwo<x[i]&&max>x[i]||max==maxTwo) {
				maxTwo=x[i];
				maxtwoIndex=i+1;
			}
		}
		System.out.println("The 1st place is student "+maxIndex+" with "+max+" points.");
		System.out.println("The 2st place is student "+maxtwoIndex+" with "+maxTwo+" points.");
			

	}


}
