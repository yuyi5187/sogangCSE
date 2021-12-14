package Problem20;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;


class BookInfo implements Comparable<BookInfo>{
	private int rank;
	private String title;
	private String name;
	private String price;
	
	public BookInfo(int rank, String title, String name, String price) {
		this.rank=rank;
		this.title=title;
		this.name=name;
		this.price=price;
	}	
	public String getName() {return this.name;}
	public String getTitle() {return this.title;}
	public int getRank() {return this.rank;}
	public String getPrice() {return this.price;}
	public String toString() {return "#"+String.valueOf(rank)+" "+title+", "+name+", "+price;}
	
	@Override
	public int compareTo(BookInfo e) {
		if(this.rank > e.getRank()) return -1;
		else return 1;
		//return this.title.compareTo(e.getTitle());
	}
}

class BookReader{
	private static ArrayList<BookInfo>booklist=new ArrayList<BookInfo>();

	public static ArrayList<BookInfo> readBooksJsoup(String name){
		
		String url=name;
		Document doc = null;
		try {
		doc = Jsoup.connect(url).get();
		} catch(IOException e) {
			e.printStackTrace();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
		
		Elements rank=doc.select("div.count");
		rank = rank.select("div");
				
		Elements booktitles=doc.select("h3.product-info-title");
		Elements titles = booktitles.select("[href]");
		
		Elements bookauthor = doc.select("div.product-shelf-author");
		Elements author = bookauthor.select("a[href]");
						
		Elements bookprice= doc.select("span.current");
		Elements price=bookprice.select("[href]");
		
		
		for(int i=0; i<rank.size(); i++) {
			BookInfo box=new BookInfo(Integer.parseInt(rank.eq(i).text()),titles.eq(i).text(),author.eq(i).text(),price.eq(i).text());
			booklist.add(box);
			
			}
		
		return booklist;
	}
}

public class Problem20 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<BookInfo> books; books = BookReader.readBooksJsoup("https://www.barnesandnoble.com/b/books/_/N-1fZ29Z8q8"); 
		Collections.sort(books); 
		for(int i=0; i<books.size(); i++) {
			BookInfo book = books.get(i); System.out.println(book);
		}

	}}