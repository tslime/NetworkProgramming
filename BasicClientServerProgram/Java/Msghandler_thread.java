import java.io.*;
import java.util.Scanner;

//Network libraries
import java.net.Socket;
import java.net.ServerSocket;



class Msghandlerthread{
    


    InputStream in;
    OutputStream out;
    BufferedReader r;
    PrintWriter w;
    

    public Msghandlerthread(Socket c){
    
        try{
            this.in = c.getInputStream();
            this.out = c.getOutputStream();
            this.r = new BufferedReader(new InputStreamReader(in));
            this.w = new PrintWriter(out,true);
        }catch(IOException e){
            System.out.println("Error during the creation of message pipeline");
        }
    }


    
    public String receive_message(BufferedReader rc){
         String m = null;

        try{
          m = rc.readLine();        
        }catch(IOException e){
            System.out.println("Error during message reception");
        }

         return m;  
    }


    public void send_message(PrintWriter wr,String m){

        wr.println(m);
      
        if(wr.checkError())
        System.out.println("Error during message transmission");
        
    }




 

    /*
    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

        System.out.println("test");
    }*/
}





 