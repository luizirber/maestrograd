package trabalho3;
/* Main.java
 *
 * Based on Compiler 06.
 *
 * Author: Luiz Carlos Irber J??nior
 * Criation date: 04-18-2007
 */
 
import AST.*;
import java.io.*;

public class Main {
    public static void main( String []args ) {
        
        File file;
        FileReader stream;
        InputStream input;
        
        if ( args.length != 1 ) 
            System.out.println("Missing parameter");
        else {
           file = new File(args[0]);
           if ( ! file.exists() || ! file.canRead() ) {
             System.out.println("Either the file " + args[0] + " does not exist or it cannot be read");
             throw new RuntimeException();
           }
           try { 
             stream = new FileReader(file);
            } catch ( FileNotFoundException e ) {
                System.out.println("Something wrong: file does not exist anymore");
                throw new RuntimeException();
            }
            try {
              stream.close();
            } catch ( IOException e ) {
                System.out.println("Error in handling the file " + args[0]);
                throw new RuntimeException();
            }
            try {
                input = new FileInputStream(file);
            }
            catch (IOException e) {
                System.out.println("Error in handling the file " + args[0]);
                throw new RuntimeException();
            }
           
            Lexer lexer = new Lexer(input);
            parser our_parser = new parser(lexer);
            Program programa = null;
            try {
                programa = (Program)our_parser.parse().value;
            }
            catch (Exception e) {
                System.out.println(e.getMessage());
            }
            if (programa != null) {
               programa.genC();
            }
        }
    }
}

