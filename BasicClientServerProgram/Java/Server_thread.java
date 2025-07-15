import java.io.*;
import java.util.Scanner;


//network libraries
import java.net.ServerSocket;
import java.net.Socket;

class Serverthread{

    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);
    

        ServerSocket fd_server = null;


        try{
            fd_server = new ServerSocket(6379);
        }catch(IOException e1){
            System.out.println("Error in socket activation");
        }

    while(true){
    Socket temp = null;

      if(fd_server != null){
        try{
             temp = fd_server.accept();
             System.out.println("Client connected.....");
        }catch(IOException e2){
            System.out.println("Error during client connection");
        }      
      }

    final Socket fd_client = temp;
    Thread t = new Thread(()->{
        
        Msghandlerthread msg = new Msghandlerthread(fd_client);
        String m = null;

         boolean b = true;
         while(b){
                m = msg.receive_message(msg.r);
                if(m == null)
                b = false;
                else{
                System.out.println("Client "+Thread.currentThread().getId()+" says: "+m);
                msg.send_message(msg.w,"Message received");
                }
            }
        
        try{
            fd_client.close();
        }catch(IOException e5){
            System.out.println("Error closing a socket");
        }

    });
    t.start();
  }    
 }

}
