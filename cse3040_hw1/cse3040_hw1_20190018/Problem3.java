package hw1_20190018;

import java.util.Scanner;

public class Problem3 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in= new Scanner(System.in);
		System.out.print("Enter a text:");
		String text=in.nextLine();
		int count=0;
		int x=text.length();
		while (true) {
			Scanner sc=new Scanner(System.in);
			System.out.print("Enter a letter: ");
			String letter=sc.nextLine();
			if (letter.length()==1) {
				char let=letter.charAt(0);
				for(int i=0;i<x;i++){
					if(text.charAt(i)==let)
						count++;}
				System.out.println("There are "+count +" "+ let+"'s in the text.");
				break;}
			System.out.println("You must enter a single letter.");}
			
	
	}

}
