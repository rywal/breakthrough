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
		JPanel top = new JPanel(/*new GridLayout(2, 1)*/);
		JLabel title = new JLabel("Breakthrough - Team 11");
		title.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		JButton undo = new JButton("Undo");
		top.add(title);
		top.add(undo);
		return top;
	}
	
	public static JPanel centerPanel() {
		JPanel center = new JPanel(new GridLayout(8, 8));
		ImageIcon xIcon = new ImageIcon("x.png");
		ImageIcon oIcon = new ImageIcon("o.png");
		ImageIcon emptyIcon = new ImageIcon("empty.png");
		
		//Create the 2D array by using two for loops
		for(int row = 0; row < 2; row++) {
			for(int col = 0; col < 8; col++) { 
				buttons[row][col] = new JButton(xIcon);
				buttons[row][col].setPreferredSize(new Dimension(1,1));
				center.add(buttons[row][col]);
			}
		}
		for(int row = 2; row < 6; row++) {
			for(int col = 0; col < 8; col++) { 
				buttons[row][col] = new JButton(emptyIcon);
				center.add(buttons[row][col]);
			}
		}
		for(int row = 6; row < 8; row++) {
			for(int col = 0; col < 8; col++) { 
				buttons[row][col] = new JButton(oIcon);
				center.add(buttons[row][col]);
			}
		}
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
		frame.setVisible(true);
		frame.setSize(500,500);
		frame.setLayout(new BorderLayout());
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
		frame.add(fullPanel(topPanel(),centerPanel()));
		frame.add(bottomPanel(), BorderLayout.SOUTH);
		
		
	}
}
		