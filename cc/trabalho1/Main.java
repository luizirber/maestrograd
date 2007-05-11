/* Main.java
 *
 * Based on Compiler 06.
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */
 
import trab1.btype.AST.*;
import java.io.*;
import trab1.atype.CompilerA;
import trab1.btype.CompilerB;

public class Main {
    public static void main( String []args ) {
        
        File file;
        FileReader stream;
        int numChRead;
        
        if ( args.length != 2 ) 
            System.out.println("Missing parameter");
        else {
           file = new File(args[1]);
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
                // one more character for '\0' at the end that will be added by the
                // compiler
            char []input = new char[ (int ) file.length() + 1 ];
            
            try {
              numChRead = stream.read( input, 0, (int ) file.length() );
            } catch ( IOException e ) {
                System.out.println("Error reading file " + args[0]);
                throw new RuntimeException();
            }
                
            if ( numChRead != file.length() ) {
                System.out.println("Read error");
                throw new RuntimeException();
            }
            try {
              stream.close();
            } catch ( IOException e ) {
                System.out.println("Error in handling the file " + args[0]);
                throw new RuntimeException();
            }
            
            switch (args[0].charAt(0)) {
                case 'a': CompilerA compilera = new CompilerA();
                          compilera.compile(input);
                          break;
                case 'b': CompilerB compilerb = new CompilerB();
                          Program program  = compilerb.compile(input);
                          program.genC();
                          break;
                default: System.out.println("Compiler type must be 'a' or 'b'");
                         throw new RuntimeException();
            }
        }
    }
}

