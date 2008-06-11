/* IfCommand.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;

public class IfCommand extends Command {

    public IfCommand( Value val, Command com ) {
        this.value = val;
        this.command = com;
    }
    
    public void genC() {
        System.out.print("if (" + value.value + " != 0)\n");
        command.genC();
    }
    
    private Value value;
    private Command command;
}
