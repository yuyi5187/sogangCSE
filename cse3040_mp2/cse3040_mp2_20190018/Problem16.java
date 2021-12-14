package Problem16;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
//import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
//import java.util.List;


class Element implements Comparable<Element>{
	private String name;
	private double price;
	
	public Element(String name, double price) {
		this.name=name;
		this.price=price;
	}	
	public String getName() {return this.name;}
	public double getPrice() {return this.price;}
	public String toString() {return name+" "+String.valueOf(price);}
	
	public int compareTo(Element e) {
		if(this.price > e.getPrice()) return 1;
		if(this.price < e.getPrice()) return -1;
		return this.name.compareTo(e.getName());
		}
}


class ElementReader<T extends Element>{
	private static ArrayList<Element> elements = new ArrayList<>();
	private static BufferedReader br;
	
	public static ArrayList<Element> readElements(String name){		
		try {
			File file=new File(name);
			br=new BufferedReader(new FileReader(file));}
		catch(FileNotFoundException e) {
			System.out.println("Input file not found");
			
		}
		try {
		String line=br.readLine();
		while(true) {
			if(line==null) break;
			String [] data=line.split(" ");
			Element element=new Element(data[0],Double.parseDouble(data[1]));
			elements.add(element);
			line=br.readLine();
		}
		}
		catch(IOException e) {
			e.printStackTrace();
		
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		return elements;
		
	}
}

public class Problem16 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<Element> list = ElementReader.readElements("input.txt"); 
		if(list == null) { System.out.println("Input file not found.");
		return; } 
		Collections.sort(list); 
		Iterator<Element> it = list.iterator();
		while(it.hasNext()) System.out.println(it.next());

	}

}
