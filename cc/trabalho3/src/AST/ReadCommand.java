/* ReadCommand.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;

public class ReadCommand extends Command {

    public ReadCommand( Character var ) {
        this.variable = var;
    }
    
    public void genC() {
        System.out.print("printf(\"What is the value of variable? \");\n");
        System.out.print("    scanf(\"%d\", &" + variable + ");\n");
    }
    
    private Character variable;
}
