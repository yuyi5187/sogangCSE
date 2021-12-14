package hw1_20190018;

import java.util.Scanner;

public class Problem1 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in=new Scanner(System.in);
		System.out.print("ASCII code teller. Enter a letter:");
		String name=in.nextLine();
		char a=name.charAt(0);
		String s="The ASCII code of "+name+" is "+(int)a;
		int length=name.length();
		
		if (length==1) {
			System.out.println(s);
		}
		else
			System.out.println("You must input a single uppercase or lowercase alphabet.");
		in.close();
	}
	

}
