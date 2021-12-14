package Problem17;


import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import java.util.Map;

import java.util.TreeMap;



@SuppressWarnings("serial")
class PrintableTreeMap<K, V> extends TreeMap<K, V> {
    @Override
    public String toString() {

        StringBuilder sb = new StringBuilder();
        forEach((key, value) -> sb.append(key).append(" ").append(value).append("\n"));      
        return sb.toString();
    }
}

class MapManager {
	private static BufferedReader br;
	
	private static TreeMap<String, Double> map = new PrintableTreeMap<>();
	@SuppressWarnings("unchecked")

	
	public static TreeMap<String,Double>readData(String name){
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
			
			map.put(data[0],Double.parseDouble(data[1]));	
			line=br.readLine();
		    }
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		
		      	
	return map;}
	  
}

public class Problem17 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Map<String, Double> map = MapManager.readData("input.txt"); 
		if(map == null) {
			System.out.println("Input file not found.");
			return; 
		} 
		System.out.println(map); 

	}

}
