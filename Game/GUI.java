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


class GUI {
	//static {
	//	System.loadLibrary("Game");
	//}
	//public static Game new_game;
	static JButton [][] buttons = new JButton[8][8]; 
	static JTextArea outputField;
	static GUI_Game new_game;
	static ImageIcon wgIcon = new ImageIcon("Game/wg.png");//White piece on green background
	static ImageIcon wmIcon = new ImageIcon("Game/wm.png");//White piece on maroon background
	static ImageIcon bgIcon = new ImageIcon("Game/bg.png");//Black piece on green background
	static ImageIcon bmIcon = new ImageIcon("Game/bm.png");//Black piece on maroon background
	static ImageIcon egIcon = new ImageIcon("Game/eg.png");//Empty piece on green background
	static ImageIcon emIcon = new ImageIcon("Game/em.png");//Empty piece on maroon background
	static String input_txt="Default Input";
	static boolean first=true;
	static boolean turn=true;
	static JTextField input = new JTextField(input_txt);
	static int row_c;
	static int column;
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
		
		/*JLabel r0 = new JLabel(" ");                                                        //UNCOMMENT THIS
>>>>>>> cab95f7c917f04858e79e25b9db30cb9e56e41e4
		JLabel r1 = new JLabel("A");
		JLabel r2 = new JLabel("B");
		JLabel r3 = new JLabel("C");
		JLabel r4 = new JLabel("D");
		JLabel r5 = new JLabel("E");
		JLabel r6 = new JLabel("F");
		JLabel r7 = new JLabel("G");
		JLabel r8 = new JLabel("H");
		
		r0.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r2.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r3.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r4.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r5.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r6.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r7.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		r8.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		
		center.add(r0);
		center.add(r1);
		center.add(r2);
		center.add(r3);
		center.add(r4);
		center.add(r5);
		center.add(r6);
		center.add(r7);
		center.add(r8);
		

		int rowTemp=8;*/                                                                  //UNCOMMENT THI
		
		//Create the 2D array by using two for loops
		for(int row = 0; row < 8; row++) {
			for(int col = 0; col < 8; col++) {
				/*if(col==0){                                                               //UNCOMMENT THIS
					JLabel c0 = new JLabel(Integer.toString(row+rowTemp));
					c0.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
					center.add(c0);
				} */  				//UNCOMMENT THIS
				center.add(buttonIcon(row, col, new_game.board[row][column]+1));
			}
			//rowTemp = rowTemp - 2;                                                         //UNCOMMENT THIS
		}	
		Buttons myButton= new Buttons(buttons, input, first);

	//	set_buttons();
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
	public static String to_result(String command, boolean turn){
		String result="";
		String dir;
		if(command.length()>6){
			int pos_col = (int)command.charAt(0)-(int)command.charAt(6);
			int pos_row = (int)command.charAt(7)-(int)command.charAt(1);
			int mult = turn ? 1 : -1;
			if(pos_row*mult==1){
				result ="" + command.charAt(0) + command.charAt(1);
				switch (mult*pos_col){
					case (-1): 	result += " right";
								break;
					case (0):	result += " fwd";
								break;
					case (1):	result += " left";
								break;
					default : 	result= "Invalid";//column " + (char)pos_col;
								break;
				}
				return result;
			}
			else result= "Invalid";//row :" + (char) pos_row;
		}
		else{
			result = "Invalid";// + (char)command.length();
		}
		return result;
	}
	
	public static JPanel bottomPanel() {
		JPanel bottom = new JPanel(new BorderLayout());

		JButton enter = new JButton("Enter");
	
		enter.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent actionEvent) {
				String result=to_result(input.getText(), turn);
				input.setText(result);
			}
		});
		bottom.add(input);
		bottom.add(enter,BorderLayout.EAST);
		outputField = new JTextArea(5, 20);
		outputField.setText("Default Output");
		bottom.add(outputField,BorderLayout.SOUTH);
		
		return bottom;
	}


    public static void main(String[] args) {
		
		final JFrame frame = new JFrame("          BreakThrough - Team 11");		
		Dimension screenRes = Toolkit.getDefaultToolkit().getScreenSize();
		frame.setLocation(screenRes.width/3-frame.getSize().width, screenRes.height/4-frame.getSize().height);
		
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
		
		
		passF.addActionListener(new ActionListener(){//
			@Override
			public void actionPerformed(ActionEvent e) {
				String passwordText = passF.getText();
				if(passwordText.equals("breakthrough")){
					frame.add(fullPanel(topPanel(),centerPanel()));
					frame.add(bottomPanel(), BorderLayout.SOUTH);
					frame.remove(login);
					SwingUtilities.updateComponentTreeUI(frame);
				} else{
					passF.setText("DENIED!!");
				}
		}
		});
		
		frame.setVisible(true);
		frame.setSize(500,600);
	
	}
}

		