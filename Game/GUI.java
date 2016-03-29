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

class GUI {
	
	static JButton [][] buttons = new JButton[8][8]; 
	static JTextArea outputField;
	
	static ImageIcon wgIcon = new ImageIcon("Game/wg.png");//White piece on green background
	static ImageIcon wmIcon = new ImageIcon("Game/wm.png");//White piece on maroon background
	static ImageIcon bgIcon = new ImageIcon("Game/bg.png");//Black piece on green background
	static ImageIcon bmIcon = new ImageIcon("Game/bm.png");//Black piece on maroon background
	static ImageIcon egIcon = new ImageIcon("Game/eg.png");//Empty piece on green background
	static ImageIcon emIcon = new ImageIcon("Game/em.png");//Empty piece on maroon background
	
	public static JPanel fullPanel(JPanel topPanel, JPanel centerPanel) {
		JPanel full = new JPanel(new BorderLayout());
		full.add(topPanel, BorderLayout.NORTH);
		full.add(centerPanel, BorderLayout.CENTER);
		return full;
	}
	
	public static JPanel topPanel() {
		JPanel fullTop = new JPanel(new BorderLayout());
		
		JPanel top = new JPanel(new BorderLayout());
		JLabel title = new JLabel("Breakthrough - Team 11");
		title.setFont(new Font("TimesRoman", Font.PLAIN, 30));
		
		title.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		JButton undo = new JButton("Undo");
		JButton startOver = new JButton("Start Over");
		top.add(title, BorderLayout.NORTH);
		top.add(undo, BorderLayout.WEST);
		top.add(startOver, BorderLayout.EAST);
		
		JPanel bottom = new JPanel(/*new GridLayout(2, 1)*/);
		String[] gameTypeString = {"Game Type", "human-ai", "ai-ai"};
		String[] aiString1 = {"Difficulty #1", "Easy", "Medium", "Hard"};
		String[] aiString2 = {"Difficulty #2", "Easy", "Medium", "Hard"};
		
		JComboBox gameType = new JComboBox(gameTypeString);
		JComboBox aiDif1 = new JComboBox(aiString1);
		JComboBox aiDif2 = new JComboBox(aiString2);
		
		//gameType.addActionListener(this);
		bottom.add(gameType);
		bottom.add(aiDif1);
		bottom.add(aiDif2);
		
		fullTop.add(top, BorderLayout.NORTH);
		fullTop.add(bottom, BorderLayout.SOUTH);
		
		return fullTop;
	}
	
	public static JButton buttonIcon(int row, int col, int white){//0=black, 1=white, 2=empty
		if(white==0 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(bgIcon);
		} else if(white==0 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(bmIcon);
		} else if(white==1 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(wgIcon);
		} else if(white==1 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(wmIcon);
		} else if(white==2 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(egIcon);
		} else if(white==2 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(emIcon);
		} else{
			buttons[row][col] = new JButton(emIcon); //Just in case
		}
		
		return buttons[row][col];
	}
	
	public static JPanel centerPanel() {
		JPanel center = new JPanel(new GridLayout(8, 8));

		//Create the 2D array by using two for loops
		for(int row = 0; row < 8; row++) {
			for(int col = 0; col < 8; col++) {
				if(row<2){
					center.add(buttonIcon(row, col, 0));
				} else if(row<8 && row>5){
					center.add(buttonIcon(row, col, 1));
				} else if(row<6 && row>1){
					center.add(buttonIcon(row, col, 2));
				}
			}
		}
		
		/*
		//Create the 2D array by using state
		for(int row = 0; row < 8; row++) {
			for(int col = 0; col < 8; col++) {
				if(current_state.get_board()[row][col]=='x'){
					buttons[row][col] = new JButton(xIcon);
				} else if(current_state.get_board()[row][col]=='x'){
					buttons[row][col] = new JButton(emptyIcon);
				} else {
					buttons[row][col] = new JButton(oIcon);
				}	
				buttons[row][col].setPreferredSize(new Dimension(1,1));
				center.add(buttons[row][col]);
			}
		}
		center.setPreferredSize(new Dimension(450, 450));
		return center;
		*/
		
		center.setPreferredSize(new Dimension(450, 450));
		return center;
	}
	
	public static JPanel bottomPanel() {
		JPanel bottom = new JPanel(new BorderLayout());
		JTextField input = new JTextField("Default Input");
		JButton enter = new JButton("Enter");
		bottom.add(input);
		bottom.add(enter,BorderLayout.EAST);
		outputField = new JTextArea(5, 20);
		outputField.setText("Default Output");
		bottom.add(outputField,BorderLayout.SOUTH);
		
		return bottom;
	}

	
	
	
    public static void main(String[] args) {
		
		JFrame frame = new JFrame();
		frame.setLayout(new BorderLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		/*JPanel login = new JPanel(new GridLayout(2, 1));   //DO NOT DELETE
		
		JPanel loginTop = new JPanel(new BorderLayout());
		JLabel enterPas = new JLabel("Enter Password to Continue", JLabel.CENTER);
		
		JPanel enterPasPan2 = new JPanel(new BorderLayout());
		JTextField passF = new JTextField("Enter Password");
		JButton enterP = new JButton("Enter");
		enterPasPan2.add(passF);
		enterPasPan2.add(enterP,BorderLayout.EAST);				
		
		loginTop.add(enterPas);
		loginTop.add(enterPasPan2, BorderLayout.SOUTH);
		
		JPanel loginBot = new JPanel();
		
		loginBot.setOpaque(true);
		loginTop.setOpaque(true);
		loginBot.setBackground(Color.CYAN);
		loginTop.setBackground(Color.CYAN);
		
		login.add(loginTop);
		login.add(loginBot);
		
		login.setVisible(true);
		
		frame.add(login);*/                                //DO NOT DELETE
		
		//passF.addActionListener(this);
		
		
		frame.add(fullPanel(topPanel(),centerPanel()));
		frame.add(bottomPanel(), BorderLayout.SOUTH);
		
		
		frame.setVisible(true);
		frame.setSize(500,625);
		
		
	}
}
		