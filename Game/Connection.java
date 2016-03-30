//package game;

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
        String response = in.readLine();
        String nextLine = in.readLine();
        while (nextLine != null){
            response += nextLine;
            nextLine = in.readLine();
        }
        return response;
    }

    public Connection(String hostname, int port, String password) throws Exception{
        this.hostname = hostname;
        this.port = port;
        socket = new Socket(hostname, port);
        in =  new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        String response = in.readLine();
        if(response.startsWith("PASSWORD")) {
            System.out.println("PASSWORD - " + response);
            authenticate(password);
            System.out.println(password);
        }
    }

  //  public void newGame(String )

    public void play() throws Exception{
      String response;
        try{
            response = read();
            System.out.println("Input: " + response);
            while(true){
                System.out.println("Loop. Input: " + response);
                if(response.startsWith("WELCOME")) {
                    write("HUMAN-AI HARD");
                    System.out.println("HUMAN-AI HARD");
                    write("DISPLAY");
                    System.out.println("DISPLAY");
                } else if(response.startsWith("OK")){
                    String user_input;
                    Scanner ui = new Scanner(System.in);
                    user_input = ui.nextLine();
                    write(user_input);
                }
                response = read();
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

            try{

            }
            finally{
                socket.close();
            }

            connection.play();
            break;
        }
    }
}
