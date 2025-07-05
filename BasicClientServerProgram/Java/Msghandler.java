import java.io.*;
import java.util.Scanner;

//Network libraries
import java.net.Socket;
import java.net.ServerSocket;
import java.nio.*;
import java.nio.channels.*;
import java.nio.ByteBuffer;
import java.nio.charset.*;


class Msghandler{
    

    ByteBuffer buffer;

    /*
    InputStream in;
    OutputStream out;
    BufferedReader r;
    PrintWriter w;
    */

      public Msghandler(int size){
            this.buffer = ByteBuffer.allocate(size);
     
    }

    /*
    public Msghandler(Socket c){
    
        try{
            this.in = c.getInputStream();
            this.out = c.getOutputStream();
            this.r = new BufferedReader(new InputStreamReader(in));
            this.w = new PrintWriter(out,true);
        }catch(IOException e){
            System.out.println("Error during the creation of message pipeline");
        }
    }*/

   public void receive_message(SocketChannel s){
    int msg_length;
    String msg = "";

    try{
        
        while( (msg_length = s.read(this.buffer)) > 0 ){
            this.buffer.flip();
            msg += StandardCharsets.UTF_8.decode(this.buffer).toString();
        
        }
        

        System.out.println("Client says: "+msg);
        }catch(IOException e){
            System.out.println("Error processing message");
        }

   }

   /*
    public boolean receive_message(BufferedReader rc,long client_num){
        
        try{
            String m = rc.readLine();
            
            if(m == null)
            return false;
            else {
                 System.out.println("Client "+client_num+" says: "+m);
                 return true;
                }

        }catch(IOException e){
            System.out.println("Error during message reception");
            return false;
        }
    }
    public void send_message(PrintWriter wr){

        wr.println("Message received");
      
        if(wr.checkError())
        System.out.println("Error during message transmission");
        

    }*/

    
    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        System.out.println("test");
    }
}