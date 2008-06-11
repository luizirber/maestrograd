/* Program.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;
import AST.Command;

public class Program {
    public Program( Vector<Command> array ) {
        this.arrayCommand = array;
    }
    
    public void genC() {
        System.out.println("#include <stdio.h>\n");
        System.out.println("int main( void ) {");

        System.out.print("    int a = 0, ");       
        for (char ch='b'; ch < 'z'; ch++)
            System.out.print( ch + " = 0, ");
        System.out.print("z = 0;\n");
        
        Enumeration<Command> e = arrayCommand.elements();
        while ( e.hasMoreElements() ) {
            System.out.print("    ");
            e.nextElement().genC();
        }
        System.out.println("\n    return 0;\n}\n");
    }                             
        
    private Vector<Command> arrayCommand;
}
