/* CompositeCommand.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype.AST;

import java.util.*;

public class CompositeCommand extends Command {

    public CompositeCommand( Vector<Command> com ) {
        this.arrayCommand = com;
    }
    
    public void genC() {
        Enumeration<Command> e = arrayCommand.elements();
        System.out.print("    {\n");
        while ( e.hasMoreElements() ) {
            System.out.print("        ");        
            e.nextElement().genC();
        }
        System.out.print("    }\n");    }
    
    private Vector<Command> arrayCommand;}
