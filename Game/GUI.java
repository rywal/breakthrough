import java.util.*;
import javax.swing.*;
import java.awt.*;
import javax.swing.AbstractButton;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.ImageIcon;
 
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

class GUI{
	
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
		//JTextField input_field = new JTextField();
		//full.add(input);
		//full.add(bottomPanel, BorderLayout.SOUTH);
		return full;
	}
	
	public static JPanel topPanel() {
		JPanel fullTop = new JPanel(new BorderLayout());
		
		JPanel top = new JPanel(/*new GridLayout(2, 1)*/);
		JLabel title = new JLabel("Breakthrough - Team 11");
		title.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		JButton undo = new JButton("Undo");
		JButton startOver = new JButton("Start Over");
		top.add(title);
		top.add(undo);
		top.add(startOver);
		
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
	
	public static JButton defaultLayout(int row, int col, int white){//0=black, 1=white, 2=empty
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
		for(int row = 0; row < 2; row++) {
			for(int col = 0; col < 8; col++) {
				//buttons[row][col] = new JButton(xIcon);
				//buttons[row][col].setPreferredSize();
				
				center.add(defaultLayout(row, col, 0));
			}
		}
		for(int row = 2; row < 6; row++) {
			for(int col = 0; col < 8; col++) { 
				center.add(defaultLayout(row, col, 2));
			}
		}
		for(int row = 6; row < 8; row++) {
			for(int col = 0; col < 8; col++) { 
				center.add(defaultLayout(row, col, 1));
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
		JFrame frame = new JFrame("Breakthrough - Team 11");
		
		frame.setLayout(new BorderLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
		frame.add(fullPanel(topPanel(),centerPanel()));
		frame.add(bottomPanel(), BorderLayout.SOUTH);
		frame.setVisible(true);
		frame.setSize(500,600);
		
		
	}
}
		