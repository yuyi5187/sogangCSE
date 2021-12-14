package Problem09;

class Point{
	private double[] d;
	public Point (double[] d) {
		this.d=new double[d.length];
		this.d=d;
	}
	public int getlen() {return this.d.length;}
	public double getItem(int i) {return this.d[i];}	
}

class EuclideanDistance {
	private static double sum;
	public static double getDist(Point p1, Point p2) {
		if (p1.getlen() != p2.getlen()) {return -1;}
		int n=p1.getlen();
		for (int i=0;i<n;i++) {
			sum+= Math.pow(p1.getItem(i)-p2.getItem(i),2);
		}
		sum=Math.sqrt(sum);
		return sum;
	}
}

class ManhattanDistance{
	private static double sum;
	public static double getDist(Point p1, Point p2) {
		if(p1.getlen()!=p2.getlen()) {return -1;}
		int n=p1.getlen();
		for(int i=0;i<n;i++) {
			sum+=Math.sqrt(Math.pow(p1.getItem(i)-p2.getItem(i),2));
		}
		return sum;
	}
}
public class Problem09 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Point p1 = new Point(new double[] {1.0, 2.0, 3.0});
		Point p2 = new Point(new double[] {4.0, 5.0, 6.0}); 
		System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p1, p2));
		System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p1, p2)); 
		Point p3 = new Point(new double[] {1.0, 2.0, 3.0}); 
		Point p4 = new Point(new double[] {4.0, 5.0}); 
		System.out.println("Euclidean Distance: " + EuclideanDistance.getDist(p3, p4));
		System.out.println("Manhattan Distance: " + ManhattanDistance.getDist(p3, p4));

	}

}
