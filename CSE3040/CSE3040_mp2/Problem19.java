package Problem19;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.Collections;



class BookInfo implements Comparable<BookInfo>{
	private int rank;
	private String title;
	private String name;
	private Double price;
	
	public BookInfo(int rank, String title, String name, Double price) {
		this.rank=rank;
		this.title=title;
		this.name=name;
		this.price=price;
	}	
	public String getName() {return this.name;}
	public String getTitle() {return this.title;}
	public int getRank() {return this.rank;}
	public Double getPrice() {return this.price;}
	public String toString() {return "#"+String.valueOf(rank)+" "+title+", "+name+", $"+String.valueOf(price);}
	
	@Override
	public int compareTo(BookInfo e) {
		if(this.rank > e.getRank()) return -1;
		else return 1;
		}
}


class BookReader{
	private static ArrayList<String> lines=new ArrayList<String>();
	private static String address;
	
	private static String temp0,temp1,temp2,temp3;
	
	private static ArrayList<BookInfo>booklist=new ArrayList<BookInfo>();
	
	public static ArrayList<BookInfo>readBooks(String name) {
		address=name;
		URL url=null;
		BufferedReader input=null;
		String line="";
		try {
			url=new URL(address);
			input =new BufferedReader(new InputStreamReader(url.openStream()));
			while((line=input.readLine())!=null) {
				if(line.trim().length()>0) lines.add(line);
			}
			input.close();
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		
		int status=0;
		
		temp0="";
		temp1="";
		temp2="";
		temp3="";
		for(int i=0; i<lines.size(); i++) {
	         String l = lines.get(i);
	         
	         if (status == 0) {
	            if(l.contains("div class=\"count\"")) {
	               int begin = l.indexOf("class=\"count\">") + "class=\"count\">".length();
	               int end = l.indexOf("</div>");	        
	               temp0+=l.substring(begin, end);          
	               	               
	               status = 1;
	            }
	         }
	         if (status == 1) {
	            if(l.contains("img")) {
	               int begin = l.indexOf("class=\"full-shadow\"") + "class=\"full-shadow\" alt=\"".length();
	               int end = l.indexOf("/>") - 2;	               	                          
	               temp1+=l.substring(begin, end)+" ";  
	               

	               status = 2;
	            }
	         }
	         if (status == 2) {
	            if(l.contains("<div class=\"product-shelf-author contributors\">by")) {
	               int begin = l.indexOf(">") + 1;
	               l = l.substring(begin);
	               begin = l.indexOf(">") + 1;
	               int end = l.indexOf("</a>");
	               temp2+=l.substring(begin, end)+" "; 
	               	
	               status = 3;
	          
	            }
	         }
	         if (status == 3) {
	            if(l.contains("<a title=\"\" class=\" current link\" onclick=\"set_cookie")) {
	               int begin = l.indexOf(">") + 2;
	               int end = l.indexOf("</a></span>");
	               
	               
	               temp3+=l.substring(begin, end)+" ";  
	               
	               BookInfo box=new BookInfo(Integer.parseInt(temp0),temp1,temp2,Double.parseDouble(temp3));
	               booklist.add(box);
	               status = 0;
	               temp0=""; temp1=""; temp2="";temp3="";
	            }
	         }
	         }
	         return booklist;
	      }
	}


	


public class Problem19 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<BookInfo> books; 
		books = BookReader.readBooks("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8");
		Collections.sort(books); 
		for(int i=0; i<books.size(); i++) {
			BookInfo book = books.get(i); 
			System.out.println(book);
		}

	}

}
