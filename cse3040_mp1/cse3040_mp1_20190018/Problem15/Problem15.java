package Problem15;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class Item{
	private String name;
	private int num;
	public Item(String name, int num) {
		this.name=name;
		this.num=num;
	}
	public String getName(){return name;}
	public int getNum(){return num;}
	public void setNum(int num) {this.num=num;}
	public String toString() {return name+" "+String.valueOf(num);}
}

class MyFileReader{
	private static BufferedReader br;
	private static String str;
	private static String data[];
	
	private static boolean bool;
	private static int n;
	public static boolean readDataFromFile(String name, ArrayList<Item> list){
		try {
			File file=new File(name);
			br=new BufferedReader(new FileReader(file));}
		catch(FileNotFoundException e) {
			return false;
		}
		try {
		String line=br.readLine();
		StringBuilder temp=new StringBuilder();
		while(true) {
			if(line==null) break;
			temp.append(line);
			line=br.readLine();
		}
		str=temp.toString().toLowerCase();
		data=str.split(" ");
	
		}
		catch(IOException e) {
			e.printStackTrace();
			return false;
		}
		catch(Exception e) {
			e.printStackTrace();
			return false;
		}
	
		for(int i=0;i<data.length;i++) {
			bool=false;
			n=0;
			for(Item item:list) {
				if(item.getName().equals(data[i])) {
					n=item.getNum()+1;
					item.setNum(n);
					bool=true;}

			}
			if (!bool){
				Item newItem=new Item(data[i],1);
				list.add(newItem);
			}
		
		}
		return true;
	}
	
}

public class Problem15 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<Item> list = new ArrayList<>(); 
		boolean rv = MyFileReader.readDataFromFile("input_prob15.txt", list); 
		if(rv == false) { 
			System.out.println("Input file not found.");
			return; 
			} 
		for(Item it: list) System.out.println(it); 
	}

}
