package cse3040fp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Scanner;





public class Client {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
	
		if(args.length!=2) {
			System.out.print("Please give the port number as an argument.");
			System.exit(1);
		}
		try {	
        String serverIP=args[0];
		Socket socket=new Socket(serverIP, Integer.parseInt(args[1]));
		
		//System.out.println("connected to server");
		Sender sender =new Sender(socket);
		Receiver receiver=new Receiver(socket);
		sender.start();
		receiver.start();
		
		}catch(ConnectException e) {
			System.out.print("Connection establishment failed.");}
		catch (IOException e) {
			//System.out.println("Connection establishment failed.");
			}
		catch(Exception e) {}
		

	}

}


class Receiver extends Thread {
Socket socket;
DataInputStream in;
Receiver(Socket socket) {
this.socket = socket;
try {
in = new DataInputStream(socket.getInputStream());
} catch(IOException e) {e.printStackTrace();}
}
public void run() {
while ( in != null ) {
try {
System.out.print(in.readUTF());
} catch(IOException e) {e.printStackTrace();}
}
}
}

class Sender extends Thread {
Socket socket;
DataOutputStream out;
String name;
Sender(Socket socket) {
this.socket = socket;
try {
out = new DataOutputStream(socket.getOutputStream());
//name = "["+socket.getInetAddress()+":"+socket.getPort()+"]";
} catch(Exception e) {e.printStackTrace();}
}
public void run() {
Scanner scanner = new Scanner(System.in);
while (out != null) {
try {
out.writeUTF(scanner.nextLine());
} catch(IOException e) {e.printStackTrace();}
}
}
}


