package Problem14;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

class Fruit {
	private String name;
	private double price;
	public Fruit(String name, double price) {
		this.name=name;
		this.price=price;
	}
	public String getName() {return this.name;}
	public double getPrice() {return this.price;}
	public String toString() {return name+" "+String.valueOf(price);}
	
}

//class box<T extends Fruit>{
class FruitBox<T extends Fruit>{
	private List<T> list;
	public FruitBox() {
	list=new ArrayList<T>();}
	private T max;
	private T min;	
	T get(int i) {return list.get(i);}
	int size() {return list.size();}
	public String toString() {return list.toString();}	
	private int count=0;
	private double sum=0;
	void add(T item) {
		list.add(item);
	System.out.println(item);
	sum+=item.getPrice();
	count++;
	if(list.size()==1) {
		max=item;
		min=item;
		
	}
	else {
	if(item.getPrice()>max.getPrice()) 
		max=item;
	if(item.getPrice()<min.getPrice()) 
		min=item;
	}
	}
	public int getNumItems() {return list.size();}
	public String getMaxItem() {return max.getName();}
	public double getMaxPrice() {return max.getPrice();}
	public String getMinItem() {return min.getName();}
	public double getMinPrice() {return min.getPrice();}
	public double getAvgPrice() {
		double avg=sum/count;
		return avg;
	}
	
}
//class FruitBox<T extends Fruit> extends box<T>{}

class ItemReader{
	private static BufferedReader br;
	public static boolean fileToBox(String name, FruitBox<Fruit> box){		
		try {
			File file=new File(name);
			br=new BufferedReader(new FileReader(file));}
		catch(FileNotFoundException e) {
			System.out.println("Input file not found");
			return false;
		}
		try {
		String line=br.readLine();
		while(true) {
			if(line==null) break;
			String [] data=line.split(" ");
			Fruit fruit=new Fruit(data[0],Double.parseDouble(data[1]));
			box.add(fruit);
			line=br.readLine();
		}
		}
		catch(IOException e) {
			System.out.println("Error!");
			return false;
		}
		return true;
		
	}
}

public class Problem14 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		FruitBox<Fruit> box = new FruitBox<>();
		boolean rv = ItemReader.fileToBox("input_prob14.txt", box); 
		if(rv == false) return; 
		box.add(new Fruit("orange", 9.99)); 
		System.out.println("----------------"); 
		System.out.println(" Summary"); 
		System.out.println("----------------");
		System.out.println("number of items: " + box.getNumItems());
		System.out.println("most expensive item: " + box.getMaxItem() + " (" + box.getMaxPrice() + ")"); 
		System.out.println("cheapest item: " + box.getMinItem() + " (" + box.getMinPrice() + ")"); 
		System.out.printf("average price of items: %.2f", box.getAvgPrice());
		

	}

}
