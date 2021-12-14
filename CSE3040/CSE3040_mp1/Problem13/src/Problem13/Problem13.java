package Problem13;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Text{
	private String str;
	private BufferedReader br;
	public boolean readTextFromFile(String name) {
		try {
			File file=new File(name);
		
			br=new BufferedReader(new FileReader(file));}
		catch(FileNotFoundException e) {
			System.out.println("Input file not found");
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
			str=temp.toString().toLowerCase();}
			catch(IOException e) {
				System.out.println("Error!");
				return false;
			}
				return true;
			}
	
		public int countChar(char c) {
			int count=0;
			for(int i=0;i<str.length();i++) {
				if(str.charAt(i)==c)
					count++;
			}
			return count;
			
		}
		
	
}

public class Problem13 {

		public static void main(String[] args) { 
			Text t = new Text(); 
			if(t.readTextFromFile("input_prob13.txt")) {
				for(char c = 'a'; c <= 'z'; c++) { 
					System.out.println(c + ": " + t.countChar(c)); 
					}
				} 

	}

}
