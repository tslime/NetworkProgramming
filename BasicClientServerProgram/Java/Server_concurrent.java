import java.io.*;
import java.util.Scanner;

//Network libraries
import java.nio.*;
import java.nio.channels.*;
import java.nio.charset.*;
import java.net.InetSocketAddress;
import java.util.Set;
import java.util.Iterator;

class Serverconcurrent{


    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        ServerSocketChannel fd_server = null;
        Selector fd_manager = null;

        try{
            fd_server = ServerSocketChannel.open();
            fd_server.bind(new InetSocketAddress(6379));
            fd_server.configureBlocking(false);
        }catch(IOException e1){
            System.out.println("Error opening socket channel");
        }

        try{
            fd_manager = Selector.open();
            fd_server.register(fd_manager,SelectionKey.OP_ACCEPT);
        }catch(IOException e2){
            System.out.println("Error creating event watcher");
        }
    

    try{

    
        while(true){
            int num_events = fd_manager.select();

            Set<SelectionKey> keys = fd_manager.selectedKeys();
            Iterator<SelectionKey> i = keys.iterator();

            while(i.hasNext()){

                SelectionKey k = i.next();
                i.remove();

                if(k.isAcceptable()){
                    
                    try{
                        ServerSocketChannel s = (ServerSocketChannel)k.channel();
                        SocketChannel c = s.accept();
                        c.configureBlocking(false);
                        c.register(fd_manager,SelectionKey.OP_READ);

                        System.out.println("New connection....");
                    }catch(IOException e1){
                        System.out.println("Error establishing connection");
                    }

                }else{
                    SocketChannel c = (SocketChannel)k.channel();
                    Msghandlerconc m = new Msghandlerconc(1024);
                    m.receive_message(c,k.hashCode());
                    m.send_message(c);
                }

            } 
             
        }

    }catch(IOException e3){
        System.out.println("Error of events selection");
    }
         
  }
}