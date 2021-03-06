package breakthroughGUI;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;
import java.lang.Exception;


public class Connection{

    private String hostname;
    private int port;
    private Socket socket;
    private BufferedReader in;
    private PrintWriter out;

    public void write(String message) throws Exception{
        out.flush();
        out.println(message);
        out.flush();
    }

    public void authenticate(String password) throws Exception{
        write(password);
    }

    public void close() throws Exception{
        write("EXIT");
        write("EXIT");
        socket.close();
    }

    public String read() throws Exception{
        // buffer for storing file contents in memory
        StringBuffer responseBuffer = new StringBuffer("");
        // for reading one line
        String line = "";
        // keep reading till readLine returns null
        while (in.ready()) {
//            System.out.print("Ready and reading: ");
            line = in.readLine();
//            System.out.println(line + ".");
            // keep appending last line read to buffer
            responseBuffer.append(line);
        }

        return responseBuffer.toString();
    }

    public String command(String command) throws Exception{
        write(command);
        String response = read();

        return response;
    }

    public String readIgnoringOK() throws Exception{
        String response = read();

        while(response.length() == 0) {
            if (response.startsWith("OK")) {
                System.out.println("Skipping an OK");
                response = "";
            }

            if (response.startsWith("ILLEGAL")) {
                return "ILLEGAL";
            }
            response = read();
        }

        Thread.sleep(200);
        return response;
    }

    public String readUntilOK() throws Exception{
        String response = read();

        while(response.length() == 0) {
            if (response.startsWith("OK")) {
                System.out.println("Skipping an OK");
                return "";
            }

            response = read();
        }

        return response;
    }

    public String move(String command) throws Exception{
        write(command);
        String response = readIgnoringOK();

        return response;
    }

    public Connection(String hostname, int port, String password) throws Exception{
        this.hostname = hostname;
        this.port = port;
        socket = new Socket(hostname, port);
        in =  new BufferedReader(new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        String response = read();
        if(response.startsWith("PASSWORD")) {
            System.out.println("PASSWORD - " + response);
            authenticate(password);
            System.out.println(password);
        }
    }

    // newGame for AI-AI type, with extra info needed
    public void newGame(String gameType, String difficulty1, String difficulty2, String address, String port, String password) throws Exception{
        String command_response;

        if (!difficulty2.isEmpty() && !address.isEmpty() && !port.isEmpty() && !password.isEmpty()) {
//            System.out.println("Doing my magic here");
            String command = gameType + " " +
                    address + " " +
                    port + " " +
                    password + " " +
                    difficulty1 + " " +
                    difficulty2;
            write(command);
            System.out.println("Command: " + command);
//            System.out.println("New game response(A-A): " + command_response);
            return;
        }

        command_response = command(gameType + " " + difficulty1);
        System.out.println("New game(H-A) response: " + command_response);
    }

    // newGame for HUMAN-AI type
    public void newGame(String gameType, String difficulty1) throws Exception{
        System.out.println("Sending H-A game type to extended method");
        newGame(gameType, difficulty1, "", "", "", "");
    }

//    public static void main(String[] args) {
//
//        try {
//            Connection connection = new Connection("127.0.0.1", 5155, "breakthrough");
//            String response;
//
//            connection.newGame("HUMAN-AI", "HARD");
//
//            response = connection.move("A2 FWD");
//            System.out.println("A2 FWD: " + response);
//
//
//            response = connection.readIgnoringOK();
//            System.out.println("AI: " + response);
//
//            response = connection.move("A1 LEFT");
//            System.out.println("A1 LEFT: " + response);
//
//            response = connection.move("A3 FWD");
//            System.out.println("A3 FWD: " + response);
//
//            response = connection.readIgnoringOK();
//            System.out.println("AI: " + response);
//
//            connection.close();
//        } catch(Exception e) {
//            e.printStackTrace();
//        }
//
//        try {
//            Connection connection = new Connection("127.0.0.1", 5155, "breakthrough");
//            String response;
//
//            connection.newGame("AI-AI", "HARD", "HARD", "127.0.0.1", "5156", "breakthrough");
//            String line = connection.read();
//            while(true) {
//                if (line.length() > 0 && !line.startsWith(";")) {
//                    System.out.println(line);
//                }
//
//                line = connection.read();
//            }
//
////            connection.close();
//        } catch(Exception e) {
//            e.printStackTrace();
//        }
//    }
}
