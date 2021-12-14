package Problem06;

interface InterSequence{
	public abstract boolean hasNext();
	public abstract int next();}

class FibonacciSequence implements InterSequence{
	public int num=-1;
	public int num2=0;
	public boolean hasNext() {return true;}
	public int next() {
		if (num<1) {
			num++;
			return num;
		}
		int result=num+num2;
		num2=num;
		num=result;
		return result;
	}
}
	

public class Problem06 {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		InterSequence seq=new FibonacciSequence();
		for(int i=0;i<20;i++) {
			if(seq.hasNext()==false) break;
			System.out.print(seq.next()+" ");
		}
		System.out.println(" ");


	}


}
