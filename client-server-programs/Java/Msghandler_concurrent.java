import java.io.*;
import java.util.Scanner;

//Network libraries
import java.net.Socket;
import java.net.ServerSocket;
import java.nio.*;
import java.nio.channels.*;
import java.nio.ByteBuffer;
import java.nio.charset.*;


class Msghandlerconc{
    

    ByteBuffer buffer;


    public Msghandlerconc(int size){
            this.buffer = ByteBuffer.allocate(size);
     
    }


   public void receive_message(SocketChannel s,int num){
    int msg_length = 0;
    String msg = "";

    try{
        
        while( (msg_length = s.read(this.buffer)) > 0 ){
            this.buffer.flip();
            msg += StandardCharsets.UTF_8.decode(this.buffer).toString();
            this.buffer.clear();
        }
        
        System.out.println("Client "+num+" says: "+msg);
        }catch(IOException e){
            System.out.println("Error processing message");
        }

    if(msg_length == -1)
    System.out.println("Client closed connection");

   }
    
    
    public void send_message(SocketChannel s){

        String msg = "Message received\n";
        this.buffer = ByteBuffer.wrap(msg.getBytes(StandardCharsets.UTF_8));
        
        try{
            s.write(buffer);
        }catch(IOException e){
            System.out.println("Error sending message");
        }

        this.buffer.clear();

    }
}