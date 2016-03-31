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
	//static {
	//	System.loadLibrary("Game");
	//}
	//public static Game new_game;
	static JButton [][] buttons = new JButton[8][8]; 
	static JTextArea outputField;
	static final JFrame frame = new JFrame("                     BreakThrough - Team 11");		
	static GUI_Game new_game= new GUI_Game();
	static ImageIcon wgIcon = new ImageIcon("Game/wg.png");//White piece on green background
	static ImageIcon wmIcon = new ImageIcon("Game/wm.png");//White piece on maroon background
	static ImageIcon bgIcon = new ImageIcon("Game/bg.png");//Black piece on green background
	static ImageIcon bmIcon = new ImageIcon("Game/bm.png");//Black piece on maroon background
	static ImageIcon egIcon = new ImageIcon("Game/eg.png");//Empty piece on green background
	static ImageIcon emIcon = new ImageIcon("Game/em.png");//Empty piece on maroon background
	static String[] gameTypeString = {"Game Type", "human-ai", "ai-ai"};
	static String[] aiString1 = {"Difficulty #1", "Easy", "Medium", "Hard"};
	static String[] aiString2 = {"Difficulty #2", "Easy", "Medium", "Hard"};
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
	
	
	public static JPanel fullPanel(JPanel topPanel, JPanel centerPanel) {
		full = new JPanel(new BorderLayout());
		full.add(topPanel, BorderLayout.NORTH);
		full.add(centerPanel, BorderLayout.CENTER);
		return full;
	}
	
	public static void aiAiToggle(JPanel bottom){
		aiAiTog = !aiAiTog;
		if(aiAiTog){
			bottom.add(aiDif2);
		} else{
			bottom.remove(aiDif2);
		}
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
		
		final JPanel bottom = new JPanel(/*new GridLayout(2, 1)*/);
		
		bottom.add(gameType);
		bottom.add(aiDif1);
			
		ItemListener dif2 = new ItemListener() {
			public void itemStateChanged(ItemEvent itemEvent) {
				if(itemEvent.getItem().toString()=="ai-ai"){
					aiAiToggle(bottom);
					SwingUtilities.updateComponentTreeUI(frame);
				}
			}
		};
		gameType.addItemListener(dif2);
				
		fullTop.add(top, BorderLayout.NORTH);
		fullTop.add(bottom, BorderLayout.SOUTH);
		
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
		//JPanel center = new JPanel(new GridLayout(8, 8));
		
		/*JLabel r0 = new JLabel(" ");                                                        //UNCOMMENT THIS
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
		for(int row = 0; row <8; row++) {
			for(int col = 0; col < 8; col++) {
				/*if(col==0){                                                               //UNCOMMENT THIS
					JLabel c0 = new JLabel(Integer.toString(row+rowTemp));
					c0.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
					center.add(c0);
				} */  				//UNCOMMENT THIS
					System.out.print(row);
					System.out.print(col);
					System.out.println(new_game.board[row][col]);
				center.add(buttonIcon(row, col, new_game.board[7-row][column]));
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
	
	public static void updateBoard(int row1, int col1, int dir, int piece) {
		
		int row2 = row1 - piece;
		int col2 = col1 + piece*dir;

		if(row2>=0 && row2 < 8 && col2>=0 && col2<8 && row1>=0 && row1 < 8 && col1>=0 && col1<8){
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
	
	public static JPanel bottomPanel() {
		JPanel bottom = new JPanel(new BorderLayout());

		//JButton enter = new JButton("Enter");
		
		/*input.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				String result=to_result(input.getText(), turn);
				//sendto server
				if(true){//server.response=="OK"){				
					input.setText(result);
					new_game.make_move(result);
					int shift = turn ? 1 : -1;
					int dir=0;
					if(result.length()==6)
						dir = 0;
					else if(result.length()==7)
						dir = -1;
					else if(result.length()==8)
						dir = 1;
					else
							System.out.println("ERROR");
					updateBoard(7-((int)result.charAt(1)-49), (int)result.charAt(0)-65, dir, shift);
					frame.repaint();
					turn=new_game.white;
				}
				else{
				//	input.setText(server_response)
				}
				//frame.repaint();
				//SwingUtilities.updateComponentTreeUI(frame);

			}
		});*/
		
		input.addCaretListener(new CaretListener() {
			@Override
			public void caretUpdate(CaretEvent e) {
				if(input.getText().length()==8 && moveAlreadyMade==0){
					moveAlreadyMade=1;
					/*String result=to_result(input.getText(), turn);
					inputHolder.setText(result);
					
					new_game.make_move(result);
					
					updateBoard(1, 1, -1, 1);*/
					System.out.println("Sent to result: " + input.getText() + ", " + turn);
					String result=to_result(input.getText(), turn);
					System.out.println("Result: " + result);
					//sendto server
					if(true){//server.response=="OK"){
						//input.setText(result);
						inputHolder.setText(result);
						new_game.make_move(result);
						int shift = turn ? 1 : -1;
						int dir=0;
						if(result.length()==6)
							dir = 0;
						else if(result.length()==7)
							dir = -1;
						else if(result.length()==8)
							dir = 1;
						else
								System.out.println("ERROR");

						int row = 7 - ((int)result.charAt(1)-49);
						int column = (int)result.charAt(0)-65;

						System.out.println("Row: " + row + " Col: " + column + " Dir: " + dir + " Shift: " + shift);
						updateBoard(row, column, dir, shift);
						//frame.repaint();
						turn=new_game.white;
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
		
		final JPanel login = new JPanel(new GridLayout(2, 1));
		
		JPanel loginTop = new JPanel(new BorderLayout());
		JLabel enterPas = new JLabel("Enter Password to Continue", JLabel.CENTER);
	
		final JTextField passF = new JTextField("breakthrough");
		passF.setHorizontalAlignment(JTextField.CENTER);
		
		loginTop.add(enterPas);
		loginTop.add(passF, BorderLayout.SOUTH);
		
		JPanel loginBot = new JPanel();
		
		loginBot.setOpaque(true);
		loginTop.setOpaque(true);
		loginBot.setBackground(Color.CYAN);
		loginTop.setBackground(Color.CYAN);
		
		login.add(loginTop);
		login.add(loginBot);
		
		login.setVisible(true);
		
		frame.add(login);
		
		passF.addActionListener(new ActionListener(){//
			@Override
			public void actionPerformed(ActionEvent e) {
				String passwordText = passF.getText();
				if(passwordText.equalsIgnoreCase("breakthrough")){
					fullPanel(topPanel(),centerPanel());
					frame.add(full);
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

		