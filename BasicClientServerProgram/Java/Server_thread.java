import java.io.*;
import java.util.Scanner;


//network libraries
import java.net.ServerSocket;
import java.net.Socket;

class Serverthread{

    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        ServerSocket fd_server = null;
        Socket fd_client = null;
        InputStream in = null;
        OutputStream out = null;
        BufferedReader r = null;
        PrintWriter w = null;


        try{
            fd_server = new ServerSocket(6379);
        }catch(IOException e1){
            System.out.println("Error in socket activation");
        }


      if(fd_server != null){
        try{
             fd_client = fd_server.accept();
             System.out.println("Client connected.....");
        }catch(IOException e2){
            System.out.println("Error during client connection");
        }      
      }

    try{
        in = fd_client.getInputStream();
        out = fd_client.getOutputStream();
     }catch(IOException e3){
        System.out.print("Failed to get stream");
    }
     
    try{
        r = new BufferedReader(new InputStreamReader(in));
        w = new PrintWriter(out,true);

        while(true){
        String client_msg = r.readLine();
        System.out.println("Client says: "+client_msg);
        w.println("Message received");
        }
        
    }catch(IOException e4){
        System.out.println("Error during message exchange");
    } 
   

  try{
    fd_client.close();
    fd_server.close();
  }catch(IOException e5){
    System.out.println("Error closing a socket");
  }


      
  }

}