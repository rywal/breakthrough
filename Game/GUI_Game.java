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
		
		public static int[][] board= new int[8][8];
		static boolean white;
		public static java.util.List<int[][]> boards= new ArrayList<int[][]>();
		
		GUI_Game(){
			set_start();
		}
		
		public static void set_start(){
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
		
		public static void make_move(String command){
			int column = (int)command.charAt(0)-65;
			int row = (int)command.charAt(1)-49;
			System.out.print(column);
			System.out.print(row);
			int shift = white ? 1 : -1;
			//board[row][column]=0;
			if (command.length()==6){
				if((row + shift)< 8 && (row + shift)>0 ){
					board[row + shift][column]= shift;
				} else{
					System.out.println("Length 6: The row" + (row+shift) + " or column" + (column) + "is out of range" );
				}
			}
			else if(command.length()==7){
				if((row + shift)< 8 && (row + shift)>0 && (column - shift)<8 && (column - shift)>0){
					board[row + shift][column - shift] = shift;
				} else{
					System.out.println("Length 7: The row" + (row+shift) + " or column" + (column-shift) + "is out of range" );
				}
			}
			else if(command.length()==8){
				if((row + shift)< 8 && (row + shift)>0 && (column + shift)<8 && (column + shift)>0){
					board[row + shift][column + shift] = shift;
				} else{
					System.out.println("Length 8: The row" + (row+shift) + " or column" + (column+shift) + "is out of range" );
				}
			}
			int[][] temp = board;
			white=!white;
			boards.add(temp);
		}
		
		public static void undo(){
			boards.remove(boards.size()-1);
			boards.remove(boards.size()-1);
			board= boards.get(boards.size()-1);
		}
		
	}
