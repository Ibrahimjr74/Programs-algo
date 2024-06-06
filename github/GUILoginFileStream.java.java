

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;

public class GUILogin extends JFrame {

    private JLabel l1 = new JLabel("Enter your Email");
    private JTextField t1 = new JTextField("Someone@gmail.com");
    private JLabel l2 = new JLabel("Enter your Password");
    private JTextField t2 = new JTextField("pass123");
    JCheckBox checkBox1 = new JCheckBox("Stay Signed in");
    private JButton b1 = new JButton("Login");

    public GUILogin() {
        setLayout(new FlowLayout());
        add(l1);
        add(t1);
        add(l2);
        add(t2);
        add(checkBox1);
        add(b1);
       
        HandleEvent h = new HandleEvent();
        b1.addActionListener(h);
        
    }


    class HandleEvent implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            String email = t1.getText();
            String password = t2.getText();
            String Checkedin = checkBox1.getText();
            try {
                File file = new File("E:\\Documents\\NetBeansProjects\\mydata.txt");
                RandomAccessFile raf = new RandomAccessFile(file, "rw");

                // Write email and password to the file
                raf.seek(raf.length());
                raf.writeUTF(email);
                raf.writeUTF(password);
               checkBox1(true);
                
  
            } catch (IOException ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(null, "Error opening file");
            }
        }

        private void checkBox1(boolean b) {
            throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
        }
    }

    public static void main(String[] args) {
        GUILogin gui = new GUILogin();
        JPanel panel = new JPanel();
        gui.setSize(600, 400);
        gui.getContentPane();
        gui.add(panel);
        gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gui.pack();
       gui.setVisible(true);
       
    }
}
