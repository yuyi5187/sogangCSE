package cse3040fp;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;



public class Server {
	
	private static BufferedReader br;
	private static TreeMap<String, TreeMap<String,String>> Library=new TreeMap<String, TreeMap<String,String>>();
	public static void readtxt(TreeMap<String, TreeMap<String,String>> Library){
		
	try {
	File file=new File("books.txt");
	br=new BufferedReader(new FileReader(file));
	}
	catch(FileNotFoundException e) {
		System.out.println("Input file not found");	
	}
	
	try {
	String line=br.readLine();
	while(true) {
		if(line==null) break;
		String [] data=line.split("\t");
		Library.put(data[0],new TreeMap<String, String>());
		TreeMap<String, String> book=Library.get(data[0]);
		book.put(data[1], data[2]);
	
		line=br.readLine();
	    }
	}catch(Exception e) {e.printStackTrace();}
	return;
	}
	
	public static void writetxt(TreeMap<String, TreeMap<String,String>> Library) {
		try {
			File file=new File("books.txt");
			FileOutputStream output = new FileOutputStream(file);
			Set<Map.Entry<String,TreeMap<String,String>>> set = Library.entrySet();
			Iterator<Map.Entry<String,TreeMap<String,String>>> it=set.iterator();
			while(it.hasNext()) {
				Map.Entry<String,TreeMap<String,String>> e = (Map.Entry<String,TreeMap<String,String>>)it.next();
				Set<Map.Entry<String,String>> subset = e.getValue().entrySet();
				Iterator<Map.Entry<String,String>> subIt = subset.iterator();
				String str=e.getKey();
				//byte[] bytes = str.getBytes();
				//output.write(bytes);

				while(subIt.hasNext()) {
				Map.Entry<String,String> subE = (Map.Entry<String,String>)subIt.next();
				String author = subE.getKey();
				String user = subE.getValue();
				String str2=str+"\t"+author+"\t"+user+"\n";
				byte[] bytes2= str2.getBytes();
				output.write(bytes2);
				}
				
		
		}
			output.close();
	}catch(Exception e) {e.printStackTrace();}
   }
	static boolean contain(Map<String,TreeMap<String,String>> L,String str) {
		boolean result=false;
		String str2=str.toLowerCase();
		Iterator<Map.Entry<String,TreeMap<String,String>>> it = L.entrySet().iterator();
		
		while(it.hasNext()) {
		Map.Entry<String,TreeMap<String,String>> entry = it.next();
		String key = entry.getKey().toLowerCase();
		if(key.equals(str2)) {
			result=true;
			break;
			
		}
		}	
		return result;
			
	}
	static String change(Map<String,TreeMap<String,String>> L,String str) {
		String key="";
		String str2=str.toLowerCase();
		Iterator<Map.Entry<String,TreeMap<String,String>>> it = L.entrySet().iterator();
		
		while(it.hasNext()) {
		Map.Entry<String,TreeMap<String,String>> entry = it.next();
	    key = entry.getKey();
		String str3=key.toLowerCase();
		if(str3.equals(str2)) {
			return key;
			
		}
		}
		return key;	
			
	}
	static boolean spaceCheck(String spaceCheck)
	{
	    for(int i = 0 ; i < spaceCheck.length() ; i++)
	    {
	        if(spaceCheck.charAt(i) == ' ')
	            return false;
	    }
	    return true;
	}


	static boolean specialCheck(String str) {
		if(!str.matches("[0-9|a-z|A-Z|¤¡-¤¾|¤¿-¤Ó|°¡-Èþ]*")) return false;
		else return true;
	}
	
	static boolean UpperCheck(String str) {
		String str2=str.toLowerCase();
		if(str.equals(str2)) return true;
		else return false;
	}
	
	static void add(String title, String author, String user) {
		Library.put(title, new TreeMap<String,String>());
		TreeMap<String, String> B=Library.get(title);
		B.put(author,user);
		writetxt(Library);
	}
	
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//TreeMap<String, TreeMap<String,String>> library=new TreeMap<String, TreeMap<String,String>>();
		
		if(args.length!=1) {
			System.out.print("Please give the port number as an argument.");
			System.exit(1);
		}
		
		try {
		
        ServerSocket serverSocket = new ServerSocket(Integer.parseInt(args[0])); 
        System.out.println("server is ready.");
       
        while (true) {            	
        	Socket socket = serverSocket.accept();
        	//System.out.println("a new connection from [" + socket.getInetAddress() + ":" + socket.getPort() + "]");
            Thread thread = new ServerReceiver(socket);
        	thread.start();
	     } }catch(Exception e) {}
	
	}


	
	private static class ServerReceiver extends Thread{
		
		
			Socket socket;
			DataInputStream in;
			DataOutputStream out;
			
			
			ServerReceiver(Socket socket) {
			this.socket = socket;
			try {
			in = new DataInputStream(socket.getInputStream());
			out = new DataOutputStream(socket.getOutputStream());
			} catch(IOException e) {e.printStackTrace();}}
			
			
			
			public void run() {
				readtxt(Library);
				Scanner scanner = new Scanner(System.in);
				String name="";
								
				try {
					out.writeUTF("Enter user ID>>");
					name=in.readUTF();
					//if entered right ID//
					boolean check=spaceCheck(name)&& UpperCheck(name) && specialCheck(name);
					while(!check) {
					 	out.writeUTF("UserID must be a single word with lowercase alphabets and numbers.\n");
						out.writeUTF("Enter user ID>>");
						name=in.readUTF();
						check=spaceCheck(name)&& UpperCheck(name) && specialCheck(name);
					}
					out.writeUTF("Hello "+name+"!\n");
					prompt(name);
					
				
				}catch(Exception e) {e.printStackTrace();}
			}
			public void prompt(String name) {

				String str="";
				
				try {
				while(true) {
				out.writeUTF(name+">>");
				str=in.readUTF();
				
				if(str.equals("add")) {
					//add
					String title,author;
					out.writeUTF("add-title>");
					title=in.readUTF();
					
					if(title.length()>0) {
						 out.writeUTF("add-author>");
						 author=in.readUTF();
					   if(author.length()>0) {
						  
						   if(! contain(Library,title)) {
								Library.put(title, new TreeMap<String,String>());
								TreeMap<String, String> book=Library.get(title);
								book.put(author,"-");
								writetxt(Library);
								out.writeUTF("A new book added to the list.\n");
								}
						   else out.writeUTF("The book already exists in the list.\n");
						 }
					   
			        }
					
										
				}
				
				else if(str.equals("borrow")) {
					//borrow
					String title;
					out.writeUTF("borrow-title>");
					title=in.readUTF();
					
					if(title.length()>0) {
						if(contain(Library,title)) {
					    //out.writeUTF("lower");
					    String Utitle=change(Library,title);
						TreeMap<String, String> book=Library.get(Utitle);
						Set<Map.Entry<String,String>>entries=book.entrySet();
						for(Map.Entry<String,String>entry:entries) {
							String user,author;
							author=entry.getKey();
							user=entry.getValue();
							//out.writeUTF(author+user);
							if(user.equals("-")) {
								add(Utitle,author,name);
								out.writeUTF("You borrow a book. - "+Utitle+"\n");
								}
							else out.writeUTF("the book is not available.\n");
						  }						
						}
						else out.writeUTF("the book is not available\n");
					}
					
				}
				else if(str.equals("return")) {
					//return
					String title;
					out.writeUTF("return-title>");
					title=in.readUTF();
					if(title.length()>0) {
						if(contain(Library,title)) {
					    //out.writeUTF("lower");
					    String Utitle=change(Library,title);
						TreeMap<String, String> book=Library.get(Utitle);
						Set<Map.Entry<String,String>>entries=book.entrySet();
						for(Map.Entry<String,String>entry:entries) {
							String user,author;
							author=entry.getKey();
							user=entry.getValue();
							if(user.equals(name)) {
							add(Utitle,author,"-");
							out.writeUTF("You returned a book.- "+Utitle+"\n");
							}
							else out.writeUTF("You did not borrow the book\n");}
						}
						else out.writeUTF("You did not borrow the book\n");
				      }
				}
				
				else if(str.equals("search")) {
					//search
					String search="";
					out.writeUTF("search-string>");
					search=in.readUTF();
					if(search.length()>0) {
					while(search.length()<3) {
						out.writeUTF("Search string must be longer than 2 characters.\n");
						out.writeUTF("search-string>");
						search=in.readUTF();
					}
					search=search.toLowerCase();
					Set<Map.Entry<String,TreeMap<String,String>>> set = Library.entrySet();
					Iterator<Map.Entry<String,TreeMap<String,String>>> it=set.iterator();
					
					int i=0;
					String line="";
					while(it.hasNext()) {
						Map.Entry<String,TreeMap<String,String>> e = (Map.Entry<String,TreeMap<String,String>>)it.next();
						Set<Map.Entry<String,String>> subset = e.getValue().entrySet();
						Iterator<Map.Entry<String,String>> subIt = subset.iterator();
						String title=e.getKey().toLowerCase();
						String Title=e.getKey();
						
						
						while(subIt.hasNext()) {
						Map.Entry<String,String> subE = (Map.Entry<String,String>)subIt.next();
						String Author = subE.getKey();
						String author=subE.getKey().toLowerCase();
						String user = subE.getValue();
						if(title.contains(search) || author.contains(search)) {
							i++;
							line+=Title+", "+Author+"\n";
							
						}
					}
					
					}
					int count=1;
					String[] l=line.split("\n");
					if(i==0) out.writeUTF("Your search matched 0 results\n");
					else {
						out.writeUTF("Your search matched "+i+ " results.\n");
						for(int j=0;j<l.length;j++) {
							out.writeUTF(count+". "+l[j]+"\n");
							count++;
						}
					}
				   }
				}
				else if(str.equals("info")) {
					//info
					Set<Map.Entry<String,TreeMap<String,String>>> set = Library.entrySet();
					Iterator<Map.Entry<String,TreeMap<String,String>>> it=set.iterator();
					int i=0;
					String line="";
					while(it.hasNext()) {
						Map.Entry<String,TreeMap<String,String>> e = (Map.Entry<String,TreeMap<String,String>>)it.next();
						Set<Map.Entry<String,String>> subset = e.getValue().entrySet();
						Iterator<Map.Entry<String,String>> subIt = subset.iterator();
						String title=e.getKey();
						while(subIt.hasNext()) {
						Map.Entry<String,String> subE = (Map.Entry<String,String>)subIt.next();
						String author = subE.getKey();
						String user = subE.getValue();
						
						//byte[] br=line.getBytes();
						if(user.equals(name)) {
							line+=title+", "+author+"\n";
							i++;
						    }
					  }
				   }
					
					String []l=line.split("\n");
					if(i==0) {
						out.writeUTF("You are currently borrowing "+i+" books\n");
					}
					else {
						out.writeUTF("You are currently borrowing "+ i +" books:\n");
						int count=1;
						for(int j=0;j<l.length;j++) {
							out.writeUTF(count+". "+l[j]+"\n");
							count++;
						}
					}
					
				}
				else {
					//print
					out.writeUTF("[available commands]\n");
					out.writeUTF("add: add a new book to the list of books.\n");
					out.writeUTF("borrow: borrow a book from the library.\n");
					out.writeUTF("return: return a book to the library.\n");
					out.writeUTF("info: show list of books I am currently borrowing.\n");
					out.writeUTF("search: search for books.\n");
				}
				}
			}catch(Exception e) {e.printStackTrace();}
			}
			
	}


}




