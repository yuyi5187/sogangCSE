package hw1_20190018;

import java.util.Scanner;

public class Problem4 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in= new Scanner(System.in);
		System.out.print("Enter a text: ");
		String text=in.nextLine();
		int count=0;
		int x=text.length();
		while (true) {
			Scanner sc=new Scanner(System.in);
			System.out.print("Enter a letter: ");
			String str=sc.nextLine();
			int y=str.length();
			if(str.length()>=1) {
				for(int i=0;i<=x-y;i++) {
					if (text.substring(i,i+y).equals(str))
						count++;
				}
				System.out.println("There are "+count+" instances of "+str);
				break;
			}
			else 
				System.out.println("You must enter a string.");
		}

	}

}
