package game;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;


public class Connection{

    private String hostname;
    private int port;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    public void authenticate(String password) throws Exception{
        out.println(password);
        out.flush();
    }

    public void close() throws Exception{
        socket.close();
    }

    public void write(String message) throws Exception{
        out.println(message);
        out.flush();
    }

    public String read() throws Exception{
        return in.readLine();
    }

    public Connection(String hostname, int port, String password) throws Exception{
        this.hostname = hostname;
        this.port = port;
        socket = new Socket(hostname, port);
        in =  new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        String response = in.readLine();
        if(response.startsWith("PASSWORD")) {
            authenticate(password);
        }
    }

    public void play() throws Exception{
      String response;
        try{
            response = read();
            if(response.startsWith("PASSWORD")){
                System.out.println("please enter a password\n");
                String user_input;
                Scanner ui = new Scanner(System.in);
                user_input = ui.nextLine();
                write(user_input);
            }
            while(true){
                response = read();
                System.out.println(response);
                if(response.startsWith("WELCOME")) {
                    write("DISPLAY");
                } else if(response.startsWith("OK")){
                    String user_input;
                    Scanner ui = new Scanner(System.in);
                    user_input = ui.nextLine();
                    write(user_input);
                }
            }
        }
        finally{
            socket.close();
        }
    }


    public static void main(String arg[]) throws Exception{
        //Creating a SocketClient object
        while(true){
            Connection connection = new Connection ("localhost", 5155, "breakthrough");
            connection.play();
            break;
        }
    }
}
