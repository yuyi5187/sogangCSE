package Problem18;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;



@SuppressWarnings("serial")
class PrintableTreeMap<K,V> extends LinkedHashMap<K,V>{
	
	
    @Override
	 public String toString() {

	        StringBuilder sb = new StringBuilder();
	        forEach((key, value) -> sb.append(key).append(" ").append(value).append("\n"));      
	        return sb.toString();
	    }

}



class MapManager{
	
	 
	private static BufferedReader br;
	private static Set<Map.Entry<String, Double>> set;
	private static List<Map.Entry<String, Double>> list;
	private static Iterator<Map.Entry<String,Double>> it;
	
	//private static TreeMap<String, Double> sortedmap = new PrintableTreeMap<>();
	//private static TreeMap<String, Double> map = new PrintableTreeMap<>();
	private static Map<String, Double> map=new PrintableTreeMap<>();
	//private static HashMap<String, Double> result;
 


	public static Map<String,Double>readData(String name) {

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
		 List<Entry<String, Double>> list = new LinkedList<Entry<String, Double>>(map.entrySet());

	       Collections.sort(list, new Comparator<Entry<String, Double>>() {

	           @Override
	           public int compare(Entry<String, Double> entry1, Entry<String, Double> entry2) {

	               if (entry1.getValue() > entry2.getValue())
	                   return +1;
	               else if (entry1.getValue() < entry2.getValue())
	                   return -1;
	               else
	                   return entry1.getKey().compareTo(entry2.getKey());

	           }

	       });
	       Map<String, Double> sortedMap = new PrintableTreeMap<String, Double>();
	       for (Entry<String, Double> entry : list) {
	           sortedMap.put(entry.getKey(), entry.getValue());
	       }
	
	return sortedMap;}

	  
	   }

public class Problem18 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Map<String, Double> map = MapManager.readData("input.txt"); 
		if(map == null) { System.out.println("Input file not found."); 
		return; } 
		System.out.println(map);

	}

}
