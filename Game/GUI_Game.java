package breakthroughGUI;
import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import javax.swing.AbstractButton;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
 
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import sun.awt.image.*;
import java.io.File;
import java.awt.image.BufferedImage;
import javax.imageio.*;
import java.applet.Applet;
import java.io.*;
import java.net.URL;
import java.applet.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

	class GUI_Game{
		public int[][] board= new int[8][8];
		boolean white;
		public java.util.List<int[][]> boards= new ArrayList<int[][]>();
		Connection connection;
		
		GUI_Game(Connection c){
			set_start();
			connection = c;
		}
		
		public void set_start(){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
						switch (i){
							case 0:
							case 1:  board[i][j]=1;
										break;
							case 6:
							case 7: board[i][j]=-1;
										break;
							default: board[i][j]=0;
										break;
						}
				}
			}
			int[][] temp= board;
			white = true;
			boards.add(temp);
		}

		public JButton [][] update_board(String move, JButton [][] buttons) {
			ImageIcon wgIcon = new ImageIcon("Game/wg.png");//White piece on green background
			ImageIcon wmIcon = new ImageIcon("Game/wm.png");//White piece on maroon background
			ImageIcon bgIcon = new ImageIcon("Game/bg.png");//Black piece on green background
			ImageIcon bmIcon = new ImageIcon("Game/bm.png");//Black piece on maroon background
			ImageIcon egIcon = new ImageIcon("Game/eg.png");//Empty piece on green background
			ImageIcon emIcon = new ImageIcon("Game/em.png");//Empty piece on maroon background

			int shift = white ? -1 : 1;
			int dir=0;
			if(move.toUpperCase().endsWith("FWD"))
				dir = 0;
			else if(move.toUpperCase().endsWith("LEFT"))
				dir = -1;
			else if(move.toUpperCase().endsWith("RIGHT"))
				dir = 1;
			else
				System.out.println("ERROR");

			int piece = shift;

			int row1 = 7 - ((int)move.charAt(1)-49);
			int col1 = (int)move.charAt(0)-65;

			int row2 = row1 - piece;
			int col2 = col1 + piece*dir;

			if(row2 >=0 && row2 <= 8 && col2>=0 && col2<8 && row1>=0 && row1 < 8 && col1>=0 && col1<8){
				if(buttons[row1][col1].getIcon()!=emIcon && buttons[row1][col1].getIcon()!=egIcon){
					if(((row1%2==0) && (col1%2==0)) || ((row1%2!=0) && (col1%2!=0))){
						System.out.println("Row: " + row1 + " Col: " + col1);
						System.out.println("Row2: " + row2 + " Col2: " + col2);
						buttons[row1][col1].setIcon(egIcon);
					} else{
						System.out.println("Row: " + row1 + " Col: " + col1);
						System.out.println("Row2: " + row2 + " Col2: " + col2);
						buttons[row1][col1].setIcon(emIcon);
					}

					if(piece==-1){
						if(((row2%2==0) && (col2%2==0)) || ((row2%2!=0) && (col2%2!=0))){
							buttons[row2][col2].setIcon(bgIcon);
						}
						else{
							buttons[row2][col2].setIcon(bmIcon);
						}
					} else if(piece==1){
						if(((row2%2==0) && (col2%2==0)) || ((row2%2!=0) && (col2%2!=0))){
							buttons[row2][col2].setIcon(wgIcon);
						}
						else{
							buttons[row2][col2].setIcon(wmIcon);
						}
					} else{
						System.out.println("ERROR!!!!!!");
					}
				} else{
					System.out.println("Cannot move empty space!!");
				}
			} else{
				System.out.println("HERE OUT OF RANGE: row1 " + row1 + " col1 "+col1+" row2 "+row2+" col2 "+col2);
			}

			white = !white;

			return buttons;
		}
		
		public JButton [][] make_move(String command, JButton [][] buttons){
			int column = (int)command.charAt(0)-65;
			int row = (int)command.charAt(1)-49;
			System.out.println(command + ": " + column + " " + row);
			int shift = white ? 1 : -1;
			if (command.toUpperCase().endsWith("FWD")){
				if((row + shift) < 8 && (row + shift)>0 ){
					board[row+shift][column]=0;
					board[row + shift][column] = shift;
				} else{
					System.out.println("Length 6: The row" + (row+shift) + " or column" + (column) + "is out of range" );
				}
			}
			else if(command.toUpperCase().endsWith("LEFT")){
				if((row + shift) < 8 && (row + shift) > 0 && (column - shift) < 8 && (column - shift) >= 0){
					board[row+shift][column-shift]=0;
					board[row + shift][column - shift] = shift;
				} else{
					System.out.println("Length 7: The row" + (row+shift) + " or column" + (column-shift) + "is out of range" );
				}
			}
			else if(command.toUpperCase().endsWith("RIGHT")){
				if((row + shift) < 8 && (row + shift) > 0 && (column + shift) < 8 && (column + shift) >= 0){
					board[row+shift][column+shift]=0;
					board[row + shift][column + shift] = shift;
				} else{
					System.out.println("Length 8: The row " + (row+shift) + " or column " + (column+shift) + " is out of range" );
				}
			}
			int[][] temp = board;
			white=!white;
			boards.add(temp);

			try {
				if (white){
					return buttons;
				}

				System.out.println("Sending command to server...");
				String server_response = connection.move(command);
				System.out.println("Response from server: " + server_response);

				String next_move = connection.readIgnoringOK();
				if (!white){
					System.out.println("Making AI move: " + next_move);
					buttons = make_move(next_move, buttons);
					buttons = update_board(next_move, buttons);
					white = !white;
					return buttons;
				}
			} catch(Exception e1) {
				e1.printStackTrace();
			}

			return buttons;
		}
		
		public void undo(){
			try {
				System.out.println("Sending UNDO command to server...");
				String server_response = connection.command("UNDO");
				System.out.println("Response from server: " + server_response);
			} catch(Exception e1) {
				e1.printStackTrace();
			}

			boards.remove(boards.size()-1);
			boards.remove(boards.size()-1);
			board= boards.get(boards.size()-1);

		}
		
	}
