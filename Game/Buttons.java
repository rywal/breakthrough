	package game;
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
	
	class Buttons{
		
		static JButton [][] buttons = new JButton[8][8]; 
		static JTextField input;
		static String input_txt;
		static boolean first;
		
		Buttons( JButton[][] buts, JTextField in, boolean f){
			buttons=buts;
			input=in;
			first=f;
			set_buttons();
		}
		public static void set_buttons(){
			buttons[0][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A8 to " : input_txt + "A8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B8 to " : input_txt + "B8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C8 to " : input_txt + "C8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D8 to " : input_txt + "D8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E8 to " : input_txt + "E8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F8 to " : input_txt + "F8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G8 to " : input_txt + "G8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[0][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H8 to " : input_txt + "H8";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A7 to " : input_txt + "A7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B7 to " : input_txt + "B7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C7 to " : input_txt + "C7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D7 to " : input_txt + "D7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E7 to " : input_txt + "E7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F7 to " : input_txt + "F7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G7 to " : input_txt + "G7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[1][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H7 to " : input_txt + "H7";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A6 to " : input_txt + "A6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B6 to " : input_txt + "B6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C6 to " : input_txt + "C6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D6 to " : input_txt + "D6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E6 to " : input_txt + "E6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F6 to " : input_txt + "F6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G6 to " : input_txt + "G6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[2][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H6 to " : input_txt + "H6";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A5 to " : input_txt + "A5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B5 to " : input_txt + "B5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C5 to " : input_txt + "C5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D5 to " : input_txt + "D5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E5 to " : input_txt + "E5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F5 to " : input_txt + "F5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G5 to " : input_txt + "G5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[3][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H5 to " : input_txt + "H5";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A4 to " : input_txt + "A4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B4 to " : input_txt + "B4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C4 to " : input_txt + "C4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D4 to " : input_txt + "D4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E4 to " : input_txt + "E4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F4 to " : input_txt + "F4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G4 to " : input_txt + "G4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[4][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H4 to " : input_txt + "H4";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A3 to " : input_txt + "A3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B3 to " : input_txt + "B3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C3 to " : input_txt + "C3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D3 to " : input_txt + "D3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E3 to " : input_txt + "E3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F3 to " : input_txt + "F3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G3 to " : input_txt + "G3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[5][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H3 to " : input_txt + "H3";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A2 to " : input_txt + "A2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B2 to " : input_txt + "B2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C2 to " : input_txt + "C2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D2 to " : input_txt + "D2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E2 to " : input_txt + "E2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F2 to " : input_txt + "F2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G2 to " : input_txt + "G2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[6][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H2 to " : input_txt + "H2";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][0].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "A1 to " : input_txt + "A1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][1].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "B1 to " : input_txt + "B1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][2].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "C1 to " : input_txt + "C1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][3].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "D1 to " : input_txt + "D1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][4].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "E1 to " : input_txt + "E1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][5].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "F1 to " : input_txt + "F1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][6].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "G1 to " : input_txt + "G1";
					first=!first;
					input.setText(input_txt);
			}
		});
			buttons[7][7].addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent actionEvent) {
					input_txt= first ? "H1 to " : input_txt + "H1";
					first=!first;
					input.setText(input_txt);
			}
		});
	}
	}
		