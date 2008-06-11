/* WhileCommand.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */
 
package AST;

import java.util.*;
import AST.*;

public class WhileCommand extends Command {

    public WhileCommand( Value val, Command com ) {
        this.value = val;
        this.command = com;
    }
    
    public void genC() {
        System.out.print("while (" + value.value + " != 0 )\n");
        command.genC();
    }
    
    private Value value;
    private Command command;
}
