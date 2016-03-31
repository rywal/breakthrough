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
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
 
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
import java.awt.event.*;
import javax.swing.text.*;
import javax.swing.event.*;


class GUI {
	static JButton [][] buttons = new JButton[8][8];
	static JTextArea outputField;
	static Connection connection;
	static final JFrame frame = new JFrame("                     BreakThrough - Team 11");
	static GUI_Game new_game;
	static ImageIcon wgIcon = new ImageIcon("Game/wg.png");//White piece on green background
	static ImageIcon wmIcon = new ImageIcon("Game/wm.png");//White piece on maroon background
	static ImageIcon bgIcon = new ImageIcon("Game/bg.png");//Black piece on green background
	static ImageIcon bmIcon = new ImageIcon("Game/bm.png");//Black piece on maroon background
	static ImageIcon egIcon = new ImageIcon("Game/eg.png");//Empty piece on green background
	static ImageIcon emIcon = new ImageIcon("Game/em.png");//Empty piece on maroon background
	static String[] gameTypeString = {"Game Type", "human-ai", "ai-ai"};
	static String[] aiString1 = {"Difficulty #1", "EASY", "MEDIUM", "HARD"};
	static String[] aiString2 = {"Difficulty #2", "EASY", "MEDIUM", "HARD"};
	static final JComboBox aiDif1 = new JComboBox(aiString1);
	static final JComboBox aiDif2 = new JComboBox(aiString2);
	static final JComboBox gameType = new JComboBox(gameTypeString);
	static String input_txt="Default Input";
	static int moveAlreadyMade=0;
	static boolean first=true;
	static boolean turn=true;
	static JTextField input = new JTextField(input_txt);
	static JTextField inputHolder = new JTextField(input_txt);
	static int row_c;
	static int column;
	static JPanel full;
	static JPanel center = new JPanel(new GridLayout(8, 8));
	static boolean aiAiTog = false;
	
	public static JLabel fullPanel() {
		JLabel backboard=new JLabel(new ImageIcon("Game/login.png"));
		backboard.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 20));
		backboard.add(topPanel());
		backboard.add(centerPanel());
		backboard.add(bottomPanel());
		/*full = new JPanel(new BorderLayout());
		full.add(topPanel(), BorderLayout.NORTH);
		full.add(centerPanel(), BorderLayout.CENTER);
		full.add(bottomPanel(), BorderLayout.SOUTH);
		return full;*/
		return backboard;
	}
	
	public static void aiAiToggle(JPanel bottom){
		aiAiTog = !aiAiTog;
		if(aiAiTog){
			bottom.add(aiDif2);
		} else{
			aiDif2.setSelectedIndex(0);
			bottom.remove(aiDif2);
		}
	}
	
	public static JPanel topPanel() {
		JPanel fullTop = new JPanel(new BorderLayout());
		
		JPanel top = new JPanel(new BorderLayout());
		//JLabel title = new JLabel("Breakthrough - Team 11");
		//title.setFont(new Font("TimesRoman", Font.PLAIN, 30));
		
		//title.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		JButton undo = new JButton("Undo");
		JButton start = new JButton("Start");
		
		undo.addActionListener(new ActionListener(){//
			@Override
			public void actionPerformed(ActionEvent e) {
				//UNDO!!
				System.out.println("THE UNDO BUTTON HAS BEEN CLICKED!!!");
				new_game.undo();
			}
		});
		
		start.addActionListener(new ActionListener(){//
			@Override
			public void actionPerformed(ActionEvent e) {
				//START OVER
				if(gameType.getSelectedItem().toString()=="human-ai"){
					if(aiDif1.getSelectedItem().toString()!="Difficulty #1"){
						try{
							connection.newGame("HUMAN-AI", aiDif1.getSelectedItem().toString() );
						} catch(Exception e1) {
							e1.printStackTrace();
						}
					}
				} else if(gameType.getSelectedItem().toString()=="ai-ai"){
					if(aiDif2.getSelectedItem().toString()!="Difficulty #2" && aiDif1.getSelectedItem().toString()!="Difficulty #1"){
						//Start ai-ai aiDif1.getSelectedItem().toString() aiDif2.getSelectedItem().toString();
					}
				}
			}
		});
		
		//top.add(title, BorderLayout.NORTH);
		top.add(undo, BorderLayout.WEST);
		top.add(start, BorderLayout.EAST);
		
		final JPanel bottom = new JPanel(/*new GridLayout(2, 1)*/);
		
		bottom.add(gameType);
		bottom.add(aiDif1);
			
		ItemListener gameT = new ItemListener() {
			public void itemStateChanged(ItemEvent itemEvent) {
				if(itemEvent.getItem().toString()=="ai-ai"){
					aiAiToggle(bottom);
					SwingUtilities.updateComponentTreeUI(frame);
				}
			}
		};
		gameType.addItemListener(gameT);
				
		fullTop.add(top, BorderLayout.NORTH);
		fullTop.add(bottom, BorderLayout.SOUTH);
		fullTop.setBackground(new Color(0, 0, 0, 0));
		return fullTop;
	}
	
	public static JButton buttonIcon(int row, int col, int piece){//-1=black, 0=empty, 1=white
		
		if(piece==-1 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(bgIcon);
			
		} else if(piece==-1 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(bmIcon);
		} else if(piece==1 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(wgIcon);
		} else if(piece==1 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(wmIcon);
		} else if(piece==0 && (((row%2==0) && (col%2==0)) || ((row%2!=0) && (col%2!=0)))){
			buttons[row][col] = new JButton(egIcon);
		} else if(piece==0 && (((row%2!=0) && (col%2==0)) || ((row%2==0) && (col%2!=0)))){
			buttons[row][col] = new JButton(emIcon);
		} else{
			buttons[row][col] = new JButton(emIcon); //Just in case
		}
		return buttons[row][col];
	}
	
	public static JPanel centerPanel() {
		
		//Create the 2D array by using two for loops
		for(int row = 0; row <8; row++) {
			for(int col = 0; col < 8; col++) {
		//			System.out.print(row);
		//			System.out.print(col);
		//			System.out.println(new_game.board[row][col]);
				center.add(buttonIcon(row, col, new_game.board[7-row][column]));
			}
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
	
	public static void updateBoard(int row1, int col1, int dir, int piece) {
		
		int row2 = row1 - piece;
		int col2 = col1 + piece*dir;

		if(row2>=0 && row2 < 8 && col2>=0 && col2<8 && row1>=0 && row1 < 8 && col1>=0 && col1<8){
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
			System.out.println("OUT OF RANGE: row1 " + row1 + " col1 "+col1+" row2 "+row2+" col2 "+col2);
		}
	}
	
	
	public static String to_result(String command, boolean turn){
		String result="";
		String dir;
		System.out.println(" ");
		if(command.length()>6){
			int pos_col = ((int)command.charAt(0)-65)-((int)command.charAt(6)-65);
			System.out.println("Col: " + command.charAt(0) + " - " + command.charAt(6) + " = " + pos_col);
			int pos_row = ((int)command.charAt(7)-49)-((int)command.charAt(1)-49);
			System.out.println("Row: " + command.charAt(7) + " - " + command.charAt(1) + " = " + pos_row);
			int mult = turn ? 1 : -1;
			System.out.println(command.charAt(0));
			System.out.println(command.charAt(1));
			System.out.println(command.charAt(6));
			System.out.println(command.charAt(7));
			if(pos_row*mult == 1){
				result = "" + command.charAt(0) + command.charAt(1);
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
			} else {
				result = "Invalid";//row :" + (char) pos_row;
			}
		} else{
			result = "Invalid";// + (char)command.length();
		}
		return result;
	}

	public static void move(String move) {
		int shift = turn ? 1 : -1;
		int dir=0;
		if(move.toUpperCase().endsWith("FWD"))
			dir = 0;
		else if(move.toUpperCase().endsWith("LEFT"))
			dir = -1;
		else if(move.toUpperCase().endsWith("RIGHT"))
			dir = 1;
		else
			System.out.println("ERROR");

		int row = 7 - ((int)move.charAt(1)-49);
		int column = (int)move.charAt(0)-65;

		System.out.println("Row: " + row + " Col: " + column + " Dir: " + dir + " Shift: " + shift);
		updateBoard(row, column, dir, shift);
		turn=new_game.white;
	}

	public static JPanel bottomPanel() {
		JPanel bottom = new JPanel(new BorderLayout());

	
		input.addCaretListener(new CaretListener() {
			@Override
			public void caretUpdate(CaretEvent e) {
				if(input.getText().length()==8 && moveAlreadyMade==0){
					moveAlreadyMade=1;
					System.out.println("Sent to result: " + input.getText() + ", " + turn);
					String result = to_result(input.getText(), turn);
					System.out.println("Result: " + result);
					//sendto server
					if(!result.startsWith("Invalid")){//server.response=="OK"){
						//input.setText(result);
						inputHolder.setText(result);
						new_game.make_move(result);

						move(result);
					}
				} else if(input.getText().length()==6){
					moveAlreadyMade=0;
					inputHolder.setText(input.getText());
				}

			}
		});

		bottom.add(inputHolder);

		return bottom;
	}


    public static void main(String[] args) {
		
		Dimension screenRes = Toolkit.getDefaultToolkit().getScreenSize();
		frame.setLocation(screenRes.width/3-frame.getSize().width, screenRes.height/4-frame.getSize().height);
		frame.setLayout(new BorderLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		final JPanel login = new JPanel(new BorderLayout());
		final JTextField passF = new JTextField("breakthrough");
		passF.setHorizontalAlignment(JTextField.CENTER);
		passF.setPreferredSize( new Dimension( 400, 24 ) );
		
		JLabel background=new JLabel(new ImageIcon("Game/login.png"));
		
		login.add(background);
		background.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 250));
		background.add(passF);
		
		login.setVisible(true);
		
		frame.add(login);
		
		
		passF.addActionListener(new ActionListener(){//
			@Override
			public void actionPerformed(ActionEvent e) {
				String passwordText = passF.getText();
				if(passwordText.equalsIgnoreCase("breakthrough")){
					try {
						connection = new Connection("127.0.0.1", 5155, "breakthrough");
						connection.newGame("HUMAN-AI", "HARD");
						new_game = new GUI_Game(connection);
					} catch(Exception e1) {
						e1.printStackTrace();
					}

					frame.remove(login);
					frame.add(fullPanel());
					
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

		