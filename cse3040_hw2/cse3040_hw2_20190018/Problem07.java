package Problem07;

import java.util.Scanner;

interface IntSequenceStr{
	public abstract boolean hasNext();
	public abstract int next();
}

class BinarySequenceStr implements IntSequenceStr{
	private int num;
	public BinarySequenceStr(int n) {num=n;}
	public boolean hasNext() {return num!=0;}
	public int next() {
		int result=0;
		int sum=0;
		double count=0;
		while(num>0) {
		if (num%2==0)
			result=0;
		else
			result=1;
		num=num/2;
		sum+=result*Math.pow(10, count);
		count++;}
		return sum;
	}
}

public class Problem07 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in=new Scanner(System.in);
		System.out.print("Enter a positive number:");
		String str=in.nextLine();
		int num=Integer.parseInt(str);
		in.close();
		System.out.println("Integer: "+num);
		
		IntSequenceStr seq=new BinarySequenceStr(num);
		System.out.print("Binary number:");
		while(seq.hasNext())System.out.print(seq.next());
		System.out.println(" ");

	}

}
