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
	
	public static JPanel topPanel() {
		JPanel top = new JPanel(new GridLayout(1, 2));
		JLabel title = new JLabel("Breakthrough - Team 11");
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
		return center;
	}
	
    public static void main(String[] args) {
		JFrame frame = new JFrame("Breakthrough - Team 11");
		frame.setVisible(true);
		frame.setSize(500,500);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JLabel jLabel1 = new javax.swing.JLabel();
		jLabel1.setFont(new java.awt.Font("Times New Roman", 0, 18));
		jLabel1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
		jLabel1.setText("BreakThrough  -  Team 11");
		frame.add(jLabel1);
		
		frame.add(centerPanel());
		
		
	}
}
		