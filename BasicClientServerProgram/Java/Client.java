import java.io.*;
import java.util.Scanner;


//Network libraries
import java.net.ServerSocket;
import java.net.Socket;
import java.net.InetSocketAddress;


class Client{


    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        Socket c = new Socket();

        try{
            c.connect(new InetSocketAddress("192.168.2.57"),6379);
            Msghandlerthread msg = new Msghandlerthread(c);
            String m = null;

            b = true;
            while(b){
                System.out.print("Write the message you want to send: ");
                m = sc.readLine();

                msg.send_message(msg.w,m);
                m = null;
                m = msg.receive_message(c);
                System.out.println(m);
            }

        }catch(IOException e){
            System.out.println("Error while attempting connection");
        }

       
    }
}