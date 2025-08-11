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
            c.connect(new InetSocketAddress("IP_NUM",PORT_NUM));
            Msghandlerthread msg = new Msghandlerthread(c);
            String m = null;

            boolean b = true;
            while(b){
                System.out.println("Write the message you want to send: ");
                m = sc.nextLine();

                msg.send_message(msg.w,m);
                m = null;
                m = msg.receive_message(msg.r);
                System.out.println(m);
                m = null;
            }

        try{
            c.close();
            }catch(IOException e1){
                System.out.println("Error during socket closure");
            }

        }catch(IOException e2){
            System.out.println("Error while attempting connection");
        }

       
    }
}