package hw1_20190018;

import java.util.Scanner;

public class Problem2 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int n=(int)(100*Math.random());
		int a=1;
		while (true) {
			Scanner in=new Scanner(System.in);
			System.out.print("["+a+"]"+" Guess a number (1-100):");
			int x;
			x=in.nextInt();
			if (x==n) {
				System.out.println("Correct! Number of guesses: "+a);
				break;
			}
			else if (x<n) {
				System.out.println("Too small!");
			}
			else if (x>n){
				System.out.println("Too large!");
			}
			else 
				System.out.println("Not in range!");
			a++;			
		}
	}

}
