package Problem08;


interface Shape{
	public abstract double area();
}

class Circle implements Shape{
	private double r;
	Circle(double a) {this.r=a;}
	public double area() {return Math.PI*(Math.pow(r,2));}
}

class Square implements Shape{
	private double len;
	Square(double a){this.len=a;}
	public double area() {return Math.pow(len,2);}
}

class Rectangle implements Shape{
	private double wid, hei;
	Rectangle(double a, double b){this.wid=a;this.hei=b;}
	public double area() {return wid*hei;}
	
}

public class Problem08 {
	public static double sumArea(Shape[] arr) {
		double sum=0;
		
		for(int i=0;i<arr.length;i++) {
			sum+=arr[i].area();
		}
		return sum;
	}
	public static void main(String[] args) {
		
		Shape[] arr= {new Circle(5.0),new Square(4.0), new Rectangle(3.0,4.0),new Square(5.0)};
		System.out.println("Total Area of the shapes is: "+sumArea(arr));
	}

}
